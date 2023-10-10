#pragma once

#include <vector>
#include <optional>
#include <functional>
#include <stdexcept>

#include "Common.hxx"

namespace FileParse
{
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

        if(!node.hasChildNode(vec.nodeNames.front()))
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

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter & node, const Child<std::optional<std::vector<T>>> & opt_vec)
    {
        if(!node.hasChildNode(opt_vec.nodeNames.front()))
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

    template<typename NodeAdapter, typename EnumType>
    NodeAdapter serializeEnumVector(NodeAdapter node,
                                    const std::vector<std::string> & tags,
                                    const std::vector<EnumType> & vec,
                                    std::function<std::string(EnumType)> converter)
    {
        if(tags.empty())
        {
            throw std::invalid_argument("Tag vector is empty");
        }

        NodeAdapter currentNode = node;

        for(size_t i = 0; i < tags.size() - 1; ++i)
        {
            currentNode = currentNode.addChild(tags[i]);
        }

        for(const auto & value : vec)
        {
            NodeAdapter childNode = currentNode.addChild(tags.back());
            childNode.addText(converter(value));
        }

        return node;
    }


    template<typename NodeAdapter, typename EnumType>
    NodeAdapter deserializeEnumVector(const NodeAdapter & node,
                                      const std::vector<std::string> & tags,
                                      std::vector<EnumType> & vec,
                                      std::function<EnumType(std::string_view)> converter)
    {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        if(tags.empty())
        {
            throw std::invalid_argument("Tag vector is empty");
        }

        NodeAdapter currentNode = node;

        for(size_t i = 0; i < tags.size() - 1; ++i)
        {
            currentNode = currentNode.getChildNode(tags[i]);
            if(currentNode.isEmpty())
            {
                throw std::runtime_error("Failed to navigate XML using provided tags");
            }
        }

        vec.clear();
        int totalNodes = currentNode.nChildNode(tags.back());
        for(int i = 0; i < totalNodes; ++i)
        {
            NodeAdapter childNode = currentNode.getChildNode(tags.back(), i);
            if(!childNode.isEmpty())
            {
                const auto text = childNode.getText();
                vec.emplace_back(converter(text));
            }
        }

        return node;
    }

}   // namespace FileParse