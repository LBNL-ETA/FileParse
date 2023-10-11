#pragma once

#include <optional>

#include "Common.hxx"

namespace FileParse
{
    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<const std::optional<T>> & child)
    {
        if(child.data.has_value())
        {
            node << Child{child.nodeNames, child.data.value()};
        }
        return node;
    }
}   // namespace FileParse