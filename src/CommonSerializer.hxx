#pragma once

#include <vector>
#include <string>
#include <optional>
#include <variant>
#include <functional>
#include <stdexcept>

namespace FileParse
{

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const std::string & text)
    {
        node.addText(text);
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, std::string & text)
    {
        text = node.getText();
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, bool value)
    {
        node.addText(value ? "true" : "false");
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, bool & value)
    {
        const auto text{node.getText()};
        value = (text == "true");
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, int value)
    {
        node.addText(std::to_string(value));
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, int & value)
    {
        const auto text{node.getText()};
        value = std::stoi(text);
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, double value)
    {
        node.addText(std::to_string(value));
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, double & value)
    {
        const auto text{node.getText()};
        value = std::stod(text);
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, size_t value)
    {
        node.addText(std::to_string(value));
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, size_t & value)
    {
        const auto text{node.getText()};
        value = std::stoul(text);
        return node;
    }

    template<typename NodeAdapter, typename T>
    inline XMLNodeAdapter operator<<(NodeAdapter node, const std::optional<T> & opt)
    {
        if(opt.has_value())
        {
            node << opt.value();
        }
        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter & node, std::optional<T> & opt)
    {
        if(!node.isEmpty())
        {
            T value;
            node >> value;
            opt = value;
        }
        return node;
    }

    template<typename NodeAdapter, typename T>
    std::optional<T> TryOptionalReadFromCurrentNode(const NodeAdapter & node, std::string nodeName)
    {
        std::optional<T> result;
        if(node.isCurrentTag(nodeName))
        {
            T value;
            node >> value;
            result = value;
        }
        return result;
    }

    template<typename T>
    struct Child
    {
        std::vector<std::string> nodeNames;
        T & data;
        size_t index{0u};

        Child(const std::string & nodeName, T & data, size_t index = 0u) :
            nodeNames({nodeName}), data(data), index(index)
        {}

        Child(std::initializer_list<std::string> nodeNames, T & data, size_t index = 0u) :
            nodeNames(nodeNames), data(data), index(index)
        {}
    };

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<T> & child)
    {
        auto childNode = node;
        for(const auto & nodeName : child.nodeNames)
        {
            childNode = childNode.addChild(nodeName);
        }
        childNode << child.data;
        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter & node, const Child<T> & child)
    {
        for(const auto & nodeName : child.nodeNames)
        {
            auto childNode = node.getChildNode(nodeName);
            if(!childNode.isEmpty())
            {
                childNode >> child.data;
            }
        }
        return node;
    }

    // ------ variant

    template<typename NodeAdapter, typename... Ts>
    void serializeVariant(NodeAdapter & node,
                          const std::vector<std::string> & nodeNames,
                          const std::variant<Ts...> & variantValue)
    {
        if(variantValue.index() < nodeNames.size())
        {
            std::visit([&](const auto & val) { node << Child{nodeNames[variantValue.index()], val}; }, variantValue);
        }
    }

    template<typename NodeAdapter, typename... Ts>
    void deserializeVariant(const NodeAdapter & node,
                            const std::vector<std::string> & nodeNames,
                            std::variant<Ts...> & variantValue)
    {
        bool deserialized = false;
        int index = 0;

        auto try_deserialize_variant = [&](auto && dummyType) {
            using Type = std::decay_t<decltype(dummyType)>;
            if(!deserialized && index < nodeNames.size())
            {
                Type value;
                if(node.nChildNode(nodeNames[index]) > 0)
                {
                    node >> Child{nodeNames[index], value};
                    variantValue = value;
                    deserialized = true;
                }
            }
            index++;
        };

        (try_deserialize_variant(Ts{}), ...);
    }

    // ------ optional

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<const std::optional<T>> & child)
    {
        if(child.data.has_value())
        {
            for(const auto & nodeName : child.nodeNames)
            {
                node = node.addChild(nodeName);
            }
            node << child.data.value();
        }
        return node;
    }

    // ------ vector

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<const std::vector<T>> & vec)
    {
        if(vec.nodeNames.empty() || vec.data.empty())
            return node;

        // Navigate to the second-to-last node
        NodeAdapter secondToLastNode = node;
        for(size_t i = 0; i < vec.nodeNames.size() - 1; ++i)
        {
            secondToLastNode = secondToLastNode.addChild(vec.nodeNames[i]);
        }

        // Name of the last node where items should be attached
        const auto & lastNodeName = vec.nodeNames.back();

        // For each item in vec.data, add the last node and serialize the item to it.
        for(const auto & item : vec.data)
        {
            NodeAdapter lastNode = secondToLastNode.addChild(lastNodeName);
            lastNode << item;
        }

        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter & node, const Child<std::vector<T>> & vec)
    {
        vec.data.clear();

        if(node.nChildNode(vec.nodeNames.front()) <= 0)
            return node;

        // Dive into the nested structure until the second-to-last node
        NodeAdapter currentNode = node;
        for(size_t j = 0; j < vec.nodeNames.size() - 1; ++j)
        {
            currentNode = currentNode.getChildNode(vec.nodeNames[j]);
        }

        const auto & targetNodeName = vec.nodeNames.back();
        int childCount = currentNode.nChildNode(targetNodeName);
        vec.data.reserve(childCount);
        for(int i = 0; i < childCount; ++i)
        {
            NodeAdapter activeNode = currentNode.getChildNode(targetNodeName, i);
            T item;
            activeNode >> item;
            vec.data.push_back(item);
        }

        return node;
    }

    // ------ optional<vector

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter & node, const Child<std::optional<std::vector<T>>> & opt_vec)
    {
        if(node.nChildNode(opt_vec.nodeNames.front()) == 0)
        {
            return node;
        }

        NodeAdapter childNode = node;
        for(size_t i = 0u; i < opt_vec.nodeNames.size() - 1u; ++i)
        {
            childNode = childNode.getChildNode(opt_vec.nodeNames[i]);
            if(childNode.isEmpty() || childNode.nChildNode() == 0)
            {
                return node;
            }
        }

        opt_vec.data = std::vector<T>();
        for(int i = 0; i < childNode.nChildNode(opt_vec.nodeNames.back()); ++i)
        {
            auto tableNode = childNode.getChildNode(opt_vec.nodeNames.back(), i);
            T item;
            tableNode >> item;
            opt_vec.data->push_back(item);
        }
        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<const std::optional<std::vector<T>>> & opt_vec)
    {
        if(opt_vec.data.has_value())
        {
            NodeAdapter currentNode = node;
            for(size_t i = 0u; i < opt_vec.nodeNames.size() - 1; ++i)
            {
                currentNode = currentNode.addChild(opt_vec.nodeNames[i]);
            }

            for(const auto & item : opt_vec.data.value())
            {
                auto tableNode = currentNode.addChild(opt_vec.nodeNames.back());
                tableNode << item;
            }
        }

        return node;
    }

    // ------ enum class

    template<typename NodeAdapter, typename EnumType>
    NodeAdapter serializeEnum(NodeAdapter node,
                              const std::string & tag,
                              const EnumType & e,
                              std::function<std::string(EnumType)> converter)
    {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        NodeAdapter childNode = node.addChild(tag);
        std::string value = converter(e);
        childNode.addText(value);

        return node;
    }

    template<typename NodeAdapter, typename EnumType>
    NodeAdapter deserializeEnum(const NodeAdapter & node,
                                const std::string & tag,
                                EnumType & e,
                                std::function<EnumType(std::string_view)> converter)
    {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        NodeAdapter childNode = node.getChildNode(tag);
        if(!childNode.isEmpty())
        {
            const auto text = childNode.getText();
            e = converter(text);
        }

        return node;
    }


    template<typename NodeAdapter, typename EnumType>
    NodeAdapter serializeEnum(NodeAdapter node,
                              const std::string & tag,
                              const std::optional<EnumType> & opt,
                              std::function<std::string(EnumType)> converter)
    {
        if(opt.has_value())
            serializeEnum(node, tag, opt.value(), converter);

        return node;
    }

    template<typename NodeAdapter, typename EnumType>
    NodeAdapter deserializeEnum(const NodeAdapter & node,
                                const std::string & tag,
                                std::optional<EnumType> & e_opt,
                                std::function<EnumType(std::string_view)> converter)
    {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        NodeAdapter childNode = node.getChildNode(tag);
        if(!childNode.isEmpty())
        {
            const auto text = childNode.getText();
            e_opt = converter(text);
        }

        return node;
    }

}   // namespace FileParse