#pragma once

#include <map>

#include "Common.hxx"

namespace FileParse
{
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