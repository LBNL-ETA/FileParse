/// File: Array.hxx
/// @brief Provides functionality to serialize and deserialize std::array and
///        std::optional<std::array> types in the FileParse namespace.

#pragma once

#include <array>
#include <optional>
#include <functional>
#include <stdexcept>

#include "Common.hxx"

namespace FileParse
{
    /// Serializes a std::array as child nodes of a given node.
    /// @tparam NodeAdapter The type of the node adapter (e.g., XMLNodeAdapter, JSONNodeAdapter).
    /// @tparam T The type of elements in the array.
    /// @tparam N The size of the array.
    /// @param node The parent node to serialize the array into.
    /// @param arr The Child wrapper containing the array data and node path hierarchy.
    /// @return Reference to the node (for chaining).
    template<typename NodeAdapter, typename T, size_t N>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Child<std::array<T, N>> & arr)
    {
        if(arr.data.empty())
            return node;

        auto currentNode{insertAllButLastChild(node, arr.nodeNames)};

        for(const auto & item : arr.data)
        {
            auto tableNode = currentNode.addChild(arr.nodeNames.back());
            tableNode << item;
        }

        return node;
    }

    /// Deserializes child nodes into a std::array.
    /// @tparam NodeAdapter The type of the node adapter (e.g., XMLNodeAdapter, JSONNodeAdapter).
    /// @tparam T The type of elements in the array.
    /// @tparam N The size of the array.
    /// @param node The parent node to deserialize from.
    /// @param arr The Child wrapper where deserialized array data will be stored.
    /// @return Const reference to the node (for chaining).
    template<typename NodeAdapter, typename T, size_t N>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          const Child<std::array<T, N>> & arr)
    {
        if(!node.hasChildNode(arr.nodeNames.front()))
            return node;

        if(auto currentNode{findParentOfLastTag(node, arr.nodeNames)}; currentNode.has_value())
        {
            const auto childNodes{currentNode.value().getChildNodesByName(arr.nodeNames.back())};

            // std::array is fixed and cannot be resized, so we need to limit the number of elements
            auto minimum{std::min(arr.data.size(), childNodes.size())};
            for(int i = 0; i < minimum; ++i)
            {
                T item;
                childNodes[i] >> item;
                arr.data[i] = item;
            }
        }

        return node;
    }

    /// Deserializes child nodes into a std::optional<std::array>.
    /// If the node path does not exist or has no children, the optional remains empty.
    /// @tparam NodeAdapter The type of the node adapter (e.g., XMLNodeAdapter, JSONNodeAdapter).
    /// @tparam T The type of elements in the array.
    /// @tparam N The size of the array.
    /// @param node The parent node to deserialize from.
    /// @param opt_vec The Child wrapper where deserialized optional array will be stored.
    /// @return Const reference to the node (for chaining).
    template<typename NodeAdapter, typename T, size_t N>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          const Child<std::optional<std::array<T, N>>> & opt_vec)
    {
        if(auto childNode{findParentOfLastTag(node, opt_vec.nodeNames)};
           !childNode.has_value() || childNode.value().nChildNode(opt_vec.nodeNames.back()) == 0)
        {
            return node;
        }

        opt_vec.data = std::array<T, N>();
        node >> Child{opt_vec.nodeNames, opt_vec.data.value()};

        return node;
    }

    /// Serializes a std::optional<std::array> as child nodes.
    /// If the optional is empty, nothing is written.
    /// @tparam NodeAdapter The type of the node adapter (e.g., XMLNodeAdapter, JSONNodeAdapter).
    /// @tparam T The type of elements in the array.
    /// @tparam N The size of the array.
    /// @param node The parent node to serialize into.
    /// @param opt_vec The Child wrapper containing the optional array and node path hierarchy.
    /// @return Reference to the node (for chaining).
    template<typename NodeAdapter, typename T, size_t N>
    inline NodeAdapter & operator<<(NodeAdapter & node,
                                    const Child<const std::optional<std::array<T, N>>> & opt_vec)
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

    /// Serializes an array of enum values as child nodes, converting enums to strings.
    /// @tparam NodeAdapter The type of the node adapter (e.g., XMLNodeAdapter, JSONNodeAdapter).
    /// @tparam EnumType The enumeration type of the array elements.
    /// @tparam N The size of the array.
    /// @param node The parent node to serialize into.
    /// @param tags Array of tag names specifying the node path hierarchy.
    /// @param vec The array of enum values to serialize.
    /// @param converter Function that converts enum values to their string representation.
    /// @return Reference to the node (for chaining).
    template<typename NodeAdapter, typename EnumType, size_t N>
    NodeAdapter & serializeEnumVector(NodeAdapter & node,
                                      const std::array<std::string, N> & tags,
                                      const std::array<EnumType, N> & vec,
                                      std::function<std::string(EnumType)> converter)
    {
        if(tags.empty())
        {
            throw std::invalid_argument("Tag array is empty");
        }

        auto currentNode{insertAllButLastChild(node, tags)};

        for(const auto & value : vec)
        {
            NodeAdapter childNode = currentNode.addChild(tags.back());
            childNode.addText(converter(value));
        }

        return node;
    }

    /// Deserializes child nodes into an array of enum values, converting strings to enums.
    /// @tparam NodeAdapter The type of the node adapter (e.g., XMLNodeAdapter, JSONNodeAdapter).
    /// @tparam EnumType The enumeration type of the array elements.
    /// @tparam N The size of the array.
    /// @param node The parent node to deserialize from.
    /// @param tags Array of tag names specifying the node path hierarchy.
    /// @param vec The array where deserialized enum values will be stored.
    /// @param converter Function that converts string representation to enum values.
    /// @return Const reference to the node (for chaining).
    template<typename NodeAdapter, typename EnumType, size_t N>
    const NodeAdapter & deserializeEnumVector(const NodeAdapter & node,
                                              const std::array<std::string, N> & tags,
                                              std::array<EnumType, N> & vec,
                                              std::function<EnumType(std::string_view)> converter)
    {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        if(tags.empty())
        {
            throw std::invalid_argument("Tag array is empty");
        }

        if(auto currentNode{findParentOfLastTag(node, tags)}; currentNode.has_value())
        {
            int totalNodes = currentNode.value().nChildNode(tags.back());
            for(int i = 0; i < totalNodes; ++i)
            {
                NodeAdapter childNode = currentNode.value().getChildNode(tags.back(), i);
                if(!childNode.isEmpty())
                {
                    const auto text = childNode.getText();
                    vec.emplace_back(converter(text));
                }
            }
        }

        return node;
    }

}   // namespace FileParse