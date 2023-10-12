#pragma once

#include <map>

#include "Common.hxx"

namespace FileParse
{
    template<typename NodeAdapter, typename Value>
    inline NodeAdapter operator<<(NodeAdapter node, const std::map<std::string, Value> & map)
    {
        for(const auto & [key, val] : map)
        {
            NodeAdapter lastNode = node.addChild(key);
            lastNode << val;
        }

        return node;
    }

    template<typename NodeAdapter, typename Value>
    inline NodeAdapter operator>>(NodeAdapter node, std::map<std::string, Value> & map)
    {
        for(int i = 0; i < node.nChildNode(); ++i)
        {
            auto childNode{node.getChildNode(i)};
            std::string key = childNode.getCurrentTag();

            Value val;
            childNode >> val;
            map[key] = val;
        }

        return node;
    }

    template<typename NodeAdapter, typename Value>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<const std::map<std::string, Value>> & value)
    {
        if(value.nodeNames.empty() || value.data.empty())
            return node;

        auto secondToLastNode{insertAllChilds(node, value.nodeNames)};

        secondToLastNode << value.data;

        return node;
    }

    template<typename NodeAdapter, typename Value>
    inline NodeAdapter operator>>(NodeAdapter node, Child<const std::map<std::string, Value>> & value)
    {
        if(value.nodeNames.empty())
        {
            return node;
        }

        NodeAdapter parentNode = node;
        for(const auto & nodeName : value.nodeNames)
        {
            parentNode = parentNode.getChildByName(nodeName);
            if(!parentNode.isValid())
            {
                return node;
            }
        }

        parentNode >> value.data;

        return node;
    }

}   // namespace FileParse