#pragma once

#include <set>

#include "Common.hxx"

namespace FileParse
{
    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<const std::set<T>> & value)
    {
        if(value.nodeNames.empty() || value.data.empty())
            return node;

        // Navigate to the second-to-last node
        NodeAdapter secondToLastNode = node;
        for(size_t i = 0; i < value.nodeNames.size() - 1; ++i)
        {
            secondToLastNode = secondToLastNode.addChild(value.nodeNames[i]);
        }

        // Name of the last node where items should be attached
        const auto & lastNodeName = value.nodeNames.back();

        // For each item in vec.data, add the last node and serialize the item to it.
        for(const auto & item : value.data)
        {
            NodeAdapter lastNode = secondToLastNode.addChild(lastNodeName);
            lastNode << item;
        }

        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter & node, const Child<std::set<T>> & vec)
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
        for(int i = 0; i < childCount; ++i)
        {
            NodeAdapter activeNode = currentNode.getChildNode(targetNodeName, i);
            T item;
            activeNode >> item;
            vec.data.insert(item);
        }

        return node;
    }
}