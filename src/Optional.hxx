#pragma once

#include <optional>

#include "Common.hxx"

namespace FileParse
{
    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const std::optional<T> & opt)
    {
        if(opt.has_value())
        {
            node << opt.value();
        }
        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter & node, std::optional<T> & opt)
    {
        if(!node.isEmpty())
        {
            T value;
            node >> value;
            opt = value;
        }
        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<const std::optional<T>> & child)
    {
        if(child.data.has_value())
        {
            for(const auto & nodeName : child.nodeNames)
            {
                node = node.addChild(nodeName);
            }
            node << child.data;
        }
        return node;
    }
}   // namespace FileParse