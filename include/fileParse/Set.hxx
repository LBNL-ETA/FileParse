/// File: Set.hxx
/// @brief Provides serialization and deserialization functionalities for sets and enum sets
///        in the FileParse namespace.

#pragma once

#include <set>
#include <functional>
#include <stdexcept>

#include "Common.hxx"

namespace FileParse
{
    /// Serializes a set as child nodes of a given node.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of elements in the set.
    /// @param node The node to serialize the set into.
    /// @param value The Child object containing the set and node hierarchy information.
    /// @return Reference to the updated node.
    template<typename NodeAdapter, typename T>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Child<const std::set<T>> & value)
    {
        if(value.nodeNames.empty() || value.data.empty())
            return node;

        auto secondToLastNode{insertAllButLastChild(node, value.nodeNames)};

        for(const auto & item : value.data)
        {
            NodeAdapter lastNode = secondToLastNode.addChild(value.nodeNames.back());
            lastNode << item;
        }

        return node;
    }

    /// Deserializes child nodes of a given node into a set.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of elements in the set.
    /// @param node The node to deserialize the set from.
    /// @param vec The Child object where the deserialized set will be stored.
    /// @return Const reference to the node.
    template<typename NodeAdapter, typename T>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, const Child<std::set<T>> & vec)
    {
        vec.data.clear();

        if(!node.hasChildNode(vec.nodeNames.front()))
            return node;

        if(auto currentNode{findParentOfLastTag(node, vec.nodeNames)}; currentNode.has_value())
        {
            const auto childNodes{currentNode.value().getChildNodesByName(vec.nodeNames.back())};
            for(const auto & childNode : childNodes)
            {
                T item;
                childNode >> item;
                vec.data.insert(item);
            }
        }

        return node;
    }

    /// Deserializes child nodes into an optional set.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of elements in the set.
    /// @param node The node to deserialize the set from.
    /// @param opt_vec The Child object where the deserialized optional set will be stored.
    /// @return Const reference to the node.
    template<typename NodeAdapter, typename T>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          const Child<std::optional<std::set<T>>> & opt_vec)
    {
        if(auto childNode{findParentOfLastTag(node, opt_vec.nodeNames)};
           !childNode.has_value() || childNode.value().nChildNode(opt_vec.nodeNames.back()) == 0)
        {
            return node;
        }

        opt_vec.data = std::set<T>();
        node >> Child{opt_vec.nodeNames, opt_vec.data.value()};

        return node;
    }

    /// Serializes an optional set as child nodes of a given node.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of elements in the set.
    /// @param node The node to serialize the optional set into.
    /// @param opt_vec The Child object containing the optional set and node hierarchy information.
    /// @return Reference to the updated node.
    template<typename NodeAdapter, typename T>
    inline NodeAdapter & operator<<(NodeAdapter & node,
                                    const Child<const std::optional<std::set<T>>> & opt_vec)
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

    /// Serializes a set of enum values as child nodes, converting the enums to strings.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam EnumType The enumeration type of the set's elements.
    /// @param node The node to serialize the set into.
    /// @param tags A vector of strings specifying the node hierarchy.
    /// @param vec The set of enum values to be serialized.
    /// @param converter A function that converts the enum values to strings.
    /// @return Reference to the updated node.
    template<typename NodeAdapter, typename EnumType>
    NodeAdapter & serializeEnumSet(NodeAdapter & node,
                                   const std::vector<std::string> & tags,
                                   const std::set<EnumType> & vec,
                                   std::function<std::string(EnumType)> converter)
    {
        if(tags.empty())
        {
            throw std::invalid_argument("Tag set is empty");
        }

        auto currentNode{insertAllButLastChild(node, tags)};

        for(const auto & value : vec)
        {
            NodeAdapter childNode = currentNode.addChild(tags.back());
            childNode.addText(converter(value));
        }

        return node;
    }

    /// Deserializes child nodes into a set of enum values, converting the strings back to enums.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam EnumType The enumeration type of the set's elements.
    /// @param node The node to deserialize the set from.
    /// @param tags A vector of strings specifying the node hierarchy.
    /// @param vec The set where the deserialized enum values will be stored.
    /// @param converter A function that converts strings to enum values.
    /// @return Const reference to the node.
    template<typename NodeAdapter, typename EnumType>
    const NodeAdapter & deserializeEnumSet(const NodeAdapter & node,
                                           const std::vector<std::string> & tags,
                                           std::set<EnumType> & vec,
                                           std::function<EnumType(std::string_view)> converter)
    {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        vec.clear();

        if(tags.empty())
        {
            throw std::invalid_argument("Tag set is empty");
        }

        if(auto currentNode{findParentOfLastTag(node, tags)}; currentNode.has_value())
        {
            const auto childNodes{currentNode.value().getChildNodesByName(tags.back())};
            for(const auto & childNode : childNodes)
            {
                const auto text = childNode.getText();
                vec.insert(converter(text));
            }
        }

        return node;
    }
}   // namespace FileParse