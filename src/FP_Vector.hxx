/// File: FP_Vector.hxx
/// @brief Provides functionality to serialize and deserialize std::vector and
///        std::optional<std::vector> types in the FileParse namespace.

#pragma once

#include <vector>
#include <optional>
#include <functional>
#include <stdexcept>

#include "FP_Common.hxx"

namespace FileParse
{
    /// Serializes a vector as child nodes of a given node.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of elements in the vector.
    /// @param node The node to serialize the vector into.
    /// @param vec The Child object containing the vector and node hierarchy information.
    /// @return Reference to the updated node.
    template<typename NodeAdapter, typename T>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Child<const std::vector<T>> & vec)
    {
        if(vec.nodeNames.empty() || vec.data.empty())
            return node;

        auto secondToLastNode{insertAllButLastChild(node, vec.nodeNames)};

        const auto & lastNodeName = vec.nodeNames.back();

        for(const auto & item : vec.data)
        {
            NodeAdapter lastNode = secondToLastNode.addChild(lastNodeName);
            lastNode << item;
        }

        return node;
    }

    /// Deserializes child nodes of a given node into a vector.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of elements in the vector.
    /// @param node The node to deserialize the vector from.
    /// @param vec The Child object where the deserialized vector will be stored.
    /// @return Const reference to the node.
    template<typename NodeAdapter, typename T>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          const Child<std::vector<T>> & vec)
    {
        vec.data.clear();

        if(!node.hasChildNode(vec.nodeNames.front()))
            return node;

        if(auto currentNode{findParentOfLastTag(node, vec.nodeNames)}; currentNode.has_value())
        {
            const auto childNodes{currentNode.value().getChildNodesByName(vec.nodeNames.back())};
            vec.data.reserve(childNodes.size());
            for(const auto & childNode : childNodes)
            {
                T item;
                childNode >> item;
                vec.data.push_back(item);
            }
        }

        return node;
    }

    /// Deserializes child nodes into an optional vector.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of elements in the vector.
    /// @param node The node to deserialize the optional vector from.
    /// @param opt_vec The Child object where the deserialized optional vector will be stored.
    /// @return Const reference to the node.
    template<typename NodeAdapter, typename T>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          const Child<std::optional<std::vector<T>>> & opt_vec)
    {
        if(auto childNode{findParentOfLastTag(node, opt_vec.nodeNames)};
           !childNode.has_value() || childNode.value().nChildNode(opt_vec.nodeNames.back()) == 0)
        {
            return node;
        }

        opt_vec.data = std::vector<T>();
        node >> Child{opt_vec.nodeNames, opt_vec.data.value()};

        return node;
    }

    /// Serializes an optional vector as child nodes of a given node.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of elements in the vector.
    /// @param node The node to serialize the optional vector into.
    /// @param opt_vec The Child object containing the optional vector and node hierarchy
    /// information.
    /// @return Reference to the updated node.
    template<typename NodeAdapter, typename T>
    inline NodeAdapter & operator<<(NodeAdapter & node,
                                    const Child<const std::optional<std::vector<T>>> & opt_vec)
    {
        if(opt_vec.data.has_value())
        {
            auto currentNode{insertAllButLastChild(node, opt_vec.nodeNames)};

            for(const auto & item : opt_vec.data.value())
            {
                auto tableNode = currentNode.addChild(opt_vec.nodeNames.back());
                tableNode << item;
            }
        }

        return node;
    }

    /// Serializes a vector of enum values as child nodes, converting the enums to strings.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam EnumType The enumeration type of the vector's elements.
    /// @param node The node to serialize the vector into.
    /// @param tags A vector of strings specifying the node hierarchy.
    /// @param vec The vector of enum values to be serialized.
    /// @param converter A function that converts the enum values to strings.
    /// @return Reference to the updated node.
    template<typename NodeAdapter, typename EnumType>
    NodeAdapter & serializeEnumVector(NodeAdapter & node,
                                      const std::vector<std::string> & tags,
                                      const std::vector<EnumType> & vec,
                                      std::function<std::string(EnumType)> converter)
    {
        if(tags.empty())
        {
            throw std::invalid_argument("Tag vector is empty");
        }

        auto currentNode{insertAllButLastChild(node, tags)};

        for(const auto & value : vec)
        {
            NodeAdapter childNode = currentNode.addChild(tags.back());
            childNode.addText(converter(value));
        }

        return node;
    }

    /// Deserializes child nodes into a vector of enum values, converting the strings back to enums.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam EnumType The enumeration type of the vector's elements.
    /// @param node The node to deserialize the vector from.
    /// @param tags A vector of strings specifying the node hierarchy.
    /// @param vec The vector where the deserialized enum values will be stored.
    /// @param converter A function that converts strings to enum values.
    /// @return Const reference to the node.
    template<typename NodeAdapter, typename EnumType>
    const NodeAdapter & deserializeEnumVector(const NodeAdapter & node,
                                              const std::vector<std::string> & tags,
                                              std::vector<EnumType> & vec,
                                              std::function<EnumType(std::string_view)> converter)
    {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        vec.clear();

        if(tags.empty())
        {
            throw std::invalid_argument("Tag vector is empty");
        }

        if(auto currentNode{findParentOfLastTag(node, tags)}; currentNode.has_value())
        {
            const auto childNodes{currentNode.value().getChildNodesByName(tags.back())};
            vec.reserve(childNodes.size());
            for(const auto & childNode : childNodes)
            {
                const auto text = childNode.getText();
                vec.emplace_back(converter(text));
            }
        }

        return node;
    }

}   // namespace FileParse