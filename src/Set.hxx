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

        auto secondToLastNode{insertAllButLastChild(node, value.nodeNames)};

        for(const auto & item : value.data)
        {
            NodeAdapter lastNode = secondToLastNode.addChild(value.nodeNames.back());
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

        auto currentNode{findParentOfLastTag(node, vec.nodeNames)};

        if(currentNode.has_value())
        {
            for(int i = 0; i < currentNode.value().nChildNode(vec.nodeNames.back()); ++i)
            {
                NodeAdapter activeNode = currentNode.value().getChildNode(vec.nodeNames.back(), i);
                T item;
                activeNode >> item;
                vec.data.insert(item);
            }
        }

        return node;
    }
}   // namespace FileParse