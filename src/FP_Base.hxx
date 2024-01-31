/// File: FP_Base.hxx
/// @brief Provides a set of functions and templates for parsing and manipulating XML-like data
/// structures.

#pragma once

#include <string>
#include <optional>
#include <map>
#include <unordered_map>

namespace FileParse
{
    /// Inserts all child nodes as specified by nodeNames into the given node.
    /// @param node The node to insert child nodes into.
    /// @param nodeNames A vector of strings representing the names of the child nodes to be
    /// inserted.
    /// @return The last inserted child node.
    template<typename NodeAdapter>
    NodeAdapter insertAllChilds(NodeAdapter & node, const std::vector<std::string> & nodeNames)
    {
        NodeAdapter lastNode = node;
        for(const auto & nodeName : nodeNames)
        {
            lastNode = lastNode.addChild(nodeName);
        }

        return lastNode;
    }

    /// Inserts all but the last child node specified by nodeNames into the given node.
    /// @param node The node to insert child nodes into.
    /// @param nodeNames A vector of strings representing the names of the child nodes to be
    /// inserted, except the last one.
    /// @return The second to last inserted child node.
    template<typename NodeAdapter>
    NodeAdapter insertAllButLastChild(NodeAdapter & node,
                                      const std::vector<std::string> & nodeNames)
    {
        NodeAdapter secondToLastNode = node;
        for(size_t i = 0; i < nodeNames.size() - 1; ++i)
        {
            secondToLastNode = secondToLastNode.addChild(nodeNames[i]);
        }

        return secondToLastNode;
    }

    /// Finds the last tag in a sequence of nested tags specified by nodeNames.
    /// @param node The root node to start the search from.
    /// @param nodeNames A vector of strings representing the nested tag names to search for.
    /// @return An optional containing the last node if found, or std::nullopt otherwise.
    template<typename NodeAdapter>
    std::optional<NodeAdapter> findLastTag(NodeAdapter & node,
                                           const std::vector<std::string> & nodeNames)
    {
        NodeAdapter currentNode = node;

        for(const auto & nodeName : nodeNames)
        {
            currentNode = currentNode.getChildNode(nodeName);
            if(currentNode.isEmpty())
            {
                return std::nullopt;
            }
        }

        return currentNode;
    }

    /// Finds the parent node of the last tag in a sequence of nested tags specified by nodeNames.
    /// @param node The root node to start the search from.
    /// @param nodeNames A vector of strings representing the nested tag names to search for.
    /// @return An optional containing the parent of the last node if found, or std::nullopt
    /// otherwise.
    template<typename NodeAdapter>
    std::optional<NodeAdapter> findParentOfLastTag(NodeAdapter node,
                                                   const std::vector<std::string> & nodeNames)
    {
        NodeAdapter currentNode = node;

        for(size_t i = 0; i < nodeNames.size() - 1; ++i)
        {
            currentNode = currentNode.getChildNode(nodeNames[i], 0);
            if(currentNode.isEmpty())
            {
                return std::nullopt;
            }
        }

        return currentNode;
    }

    /// Counts the number of child nodes under the last tag in a sequence specified by nodeNames.
    /// @param node The root node to start the search from.
    /// @param nodeNames A vector of strings representing the nested tag names to count the children
    /// of.
    /// @return The number of child nodes under the last tag.
    template<typename NodeAdapter>
    int numberOfChilds(NodeAdapter & node, const std::vector<std::string> & nodeNames)
    {
        auto currentNode{findParentOfLastTag(node, nodeNames)};

        if(!currentNode.has_value())
        {
            return 0;
        }

        return currentNode.value().nChilds(nodeNames.size());
    }

    /// Inserts a string into the node as text.
    /// @param node The node to insert text into.
    /// @param text The string text to be inserted.
    /// @return Reference to the updated node.
    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const std::string & text)
    {
        node.addText(text);
        return node;
    }

    /// Extracts text from the node and stores it in a string.
    /// @param node The node to extract text from.
    /// @param text String variable where the extracted text will be stored.
    /// @return Const reference to the node.
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, std::string & text)
    {
        text = node.getText();
        return node;
    }

    /// Inserts a boolean value into the node as text ("true" or "false").
    /// @param node The node to insert the boolean text into.
    /// @param value The boolean value to be inserted.
    /// @return Reference to the updated node.
    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, bool value)
    {
        node.addText(value ? "true" : "false");
        return node;
    }

    /// Extracts text from the node and converts it to a boolean value.
    /// @param node The node to extract text from.
    /// @param value Boolean variable where the extracted value will be stored.
    /// @return Const reference to the node.
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, bool & value)
    {
        const auto text{node.getText()};
        value = (text == "true");
        return node;
    }

    /// Inserts an integer value into the node as text.
    /// @param node The node to insert the integer into.
    /// @param value The integer value to be inserted.
    /// @return Reference to the updated node.
    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, int value)
    {
        node.addText(std::to_string(value));
        return node;
    }

    /// Extracts text from the node and converts it to an integer value.
    /// @param node The node to extract text from.
    /// @param value Integer variable where the extracted value will be stored.
    /// @return Const reference to the node.
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, int & value)
    {
        const auto text{node.getText()};
        value = std::stoi(text);
        return node;
    }

    /// Inserts a double value into the node as text.
    /// @param node The node to insert the double into.
    /// @param value The double value to be inserted.
    /// @return Reference to the updated node.
    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, double value)
    {
        node.addText(std::to_string(value));
        return node;
    }

    /// Extracts text from the node and converts it to a double value.
    /// @param node The node to extract text from.
    /// @param value Double variable where the extracted value will be stored.
    /// @return Const reference to the node.
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, double & value)
    {
        const auto text{node.getText()};
        value = std::stod(text);
        return node;
    }

    /// Inserts a size_t (unsigned integer) value into the node as text.
    /// @param node The node to insert the size_t value into.
    /// @param value The size_t value to be inserted.
    /// @return Reference to the updated node.
    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, size_t value)
    {
        node.addText(std::to_string(value));
        return node;
    }

    /// Extracts text from the node and converts it to a size_t (unsigned integer) value.
    /// @param node The node to extract text from.
    /// @param value size_t variable where the extracted value will be stored.
    /// @return Const reference to the node.
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, size_t & value)
    {
        const auto text{node.getText()};
        value = std::stoul(text);
        return node;
    }

    /// Checks if a given type is a valid map type.
    /// @tparam T The type to be checked.
    template<typename T>
    struct is_valid_map : std::false_type
    {};

    /// Specialization of is_valid_map for std::map.
    /// @tparam K The key type of the map.
    /// @tparam V The value type of the map.
    template<typename K, typename V>
    struct is_valid_map<std::map<K, V>> : std::true_type
    {};

    /// Specialization of is_valid_map for std::unordered_map.
    /// @tparam K The key type of the map.
    /// @tparam V The value type of the map.
    template<typename K, typename V>
    struct is_valid_map<std::unordered_map<K, V>> : std::true_type
    {};

    /// Inserts a map into the node by iterating over its key-value pairs.
    /// @param node The node to insert the map into.
    /// @param map The map to be inserted.
    /// @return Reference to the updated node.
    template<typename NodeAdapter, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, NodeAdapter &>
      operator<<(NodeAdapter & node, const MapType & map)
    {
        for(const auto & [key, val] : map)
        {
            NodeAdapter lastNode = node.addChild(key);
            lastNode << val;
        }

        return node;
    }

    /// Extracts a map from the node by iterating over its child nodes and constructing the map.
    /// @param node The node to extract the map from.
    /// @param map The map to store the extracted values.
    /// @return Const reference to the node.
    template<typename NodeAdapter, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, const NodeAdapter &>
      operator>>(const NodeAdapter & node, MapType & map)
    {
        for(int i = 0; i < node.nChildNode(); ++i)
        {
            auto childNode = node.getChildNode(i);
            std::string key = childNode.getCurrentTag();

            typename MapType::mapped_type val;
            childNode >> val;
            map[key] = val;
        }

        return node;
    }

    /// Inserts an optional value into the node. If the optional is not empty, the value is
    /// inserted; otherwise, nothing is inserted.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of the value contained in the optional.
    /// @param node The node into which the value is to be inserted.
    /// @param opt The optional value to be inserted.
    /// @return Reference to the updated node.
    template<typename NodeAdapter, typename T>
    inline NodeAdapter & operator<<(NodeAdapter & node, const std::optional<T> & opt)
    {
        if(opt.has_value())
        {
            node << opt.value();
        }
        return node;
    }

    /// Extracts a value from the node and stores it in an optional. If the node is not empty, the
    /// value is extracted and stored in the optional.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of the value to be extracted into the optional.
    /// @param node The node from which the value is to be extracted.
    /// @param opt The optional variable where the extracted value will be stored.
    /// @return Const reference to the node.
    template<typename NodeAdapter, typename T>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, std::optional<T> & opt)
    {
        if(!node.isEmpty())
        {
            T value;
            node >> value;
            opt = value;
        }
        return node;
    }
}   // namespace FileParse