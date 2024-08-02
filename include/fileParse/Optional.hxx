/// File: Optional.hxx
/// @brief Provides functionality to serialize optional data types
///        in the FileParse namespace.

#pragma once

#include <optional>

#include "Common.hxx"

namespace FileParse
{
    /// Serializes an optional data type. If the optional contains a value, it is serialized; otherwise, nothing is serialized.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of the data contained in the optional.
    /// @param node The node to serialize the data into.
    /// @param child The Child object containing the optional data and node hierarchy information.
    /// @return Reference to the updated node.
    template<typename NodeAdapter, typename T>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Child<const std::optional<T>> & child)
    {
        if(child.data.has_value())
        {
            node << Child{child.nodeNames, child.data.value()};
        }
        return node;
    }
}   // namespace FileParse