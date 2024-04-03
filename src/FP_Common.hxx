/// File: FP_Common.hxx
/// @brief Provides a set of functions and templates for parsing and manipulating XML-like data
/// structures.

#pragma once

#include <string>
#include <vector>

#include "FP_Base.hxx"

namespace FileParse
{
    /// Represents a child node for parsing or serialization, along with associated data.
    /// @tparam T The type of the data associated with the child node.
    template<typename T>
    struct Child
    {
        /// Names of the nodes in the hierarchy leading to the child.
        std::vector<std::string> nodeNames;

        /// Reference to the data associated with the child node.
        T & data;

        /// Index of the child node among siblings (default 0).
        size_t index{0u};


        /// Constructs a Child object with a single node name.
        /// @param nodeName The name of the child node.
        /// @param data Reference to the data associated with the node.
        /// @param index Optional index of the child node (default 0).
        Child(const std::string & nodeName, T & data, size_t index = 0u) :
            nodeNames({nodeName}), data(data), index(index)
        {}

        /// Constructs a Child object with an initializer list of node names.
        /// @param nodeNames Initializer list of strings representing node names.
        /// @param data Reference to the data associated with the node.
        /// @param index Optional index of the child node (default 0).
        Child(std::initializer_list<std::string> nodeNames, T & data, size_t index = 0u) :
            nodeNames(nodeNames), data(data), index(index)
        {}

        /// Constructs a Child object with a vector of node names.
        /// @param nodeNames Vector of strings representing node names.
        /// @param data Reference to the data associated with the node.
        /// @param index Optional index of the child node (default 0).
        Child(const std::vector<std::string> & nodeNames, T & data, size_t index = 0u) :
            nodeNames(nodeNames), data(data), index(index)
        {}
    };

    /// Inserts data associated with a Child object into the corresponding node hierarchy.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of the data to be inserted.
    /// @param node The node into which the data is to be inserted.
    /// @param child The Child object containing the data and node hierarchy information.
    /// @return Reference to the updated node.
    template<typename NodeAdapter, typename T>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Child<T> & child)
    {
        auto childNode = node;
        for(const auto & nodeName : child.nodeNames)
        {
            childNode = childNode.addChild(nodeName);
        }
        childNode << child.data;
        return node;
    }

    /// Extracts data from a node hierarchy into the data field of a Child object.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of the data to be extracted.
    /// @param node The node from which the data is to be extracted.
    /// @param child The Child object that will hold the extracted data and provides node hierarchy
    /// information.
    /// @return Const reference to the node.
    template<typename NodeAdapter, typename T>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, const Child<T> & child)
    {
        for(const auto & nodeName : child.nodeNames)
        {
            auto childNode{node.getFirstChildByName(nodeName)};
            if(childNode.has_value())
            {
                childNode.value() >> child.data;
            }
        }
        return node;
    }
}   // namespace FileParse