/// File: RenamedChild.hxx
/// @brief A child node whose tag was renamed: files keep reading under every name the tag has
///        had, and are written under the current one.

#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "Common.hxx"

namespace FileParse
{
    /// Use it only where a tag was renamed; every other node stays a plain Child.
    ///
    ///     node >> FileParse::RenamedChild{.current = "ModelInfo",
    ///                                     .legacy = {"ModelDetails", "ModelExposure"},
    ///                                     .data = info};
    ///
    /// Every name is one tag at the same level, so a path such as {"Hobbies", "Hobby"} is not a
    /// name here. Reading and writing hand over to a plain Child of one name, so every type
    /// behaves as it does under Child, an absent tag included.
    /// @tparam T The type of the data; const when writing, as under Child.
    template<typename T>
    struct RenamedChild
    {
        /// The name the node is written under and read under first.
        std::string current;

        /// The names older files carry, tried in this order when the current name is absent.
        std::vector<std::string> legacy;

        /// Reference to the data associated with the node.
        T & data;
    };

    /// Deduces the type from a positional call on compilers without class template argument
    /// deduction for aggregates. Designated initializers need that deduction, which arrived in
    /// Clang 17; code built on older compilers spells the type: RenamedChild<Info>{.current = ...}.
    template<typename T>
    RenamedChild(std::string, std::vector<std::string>, T &) -> RenamedChild<T>;

    /// The name a node should be read under: the current one when the file has it or when it
    /// has none of the names, else the first legacy name it carries.
    template<typename NodeAdapter, typename T>
    [[nodiscard]] inline std::string nameInFile(const NodeAdapter & node, const RenamedChild<T> & child)
    {
        if(node.hasChildNode(child.current))
        {
            return child.current;
        }
        const auto found{std::ranges::find_if(
          child.legacy, [&node](const std::string & name) { return node.hasChildNode(name); })};
        return found != child.legacy.end() ? *found : child.current;
    }

    /// Reads the data from the first name the file carries.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of the data to be read.
    /// @param node The node holding the child.
    /// @param child The names and the data.
    /// @return Reference to the node.
    template<typename NodeAdapter, typename T>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, const RenamedChild<T> & child)
    {
        node >> Child{nameInFile(node, child), child.data};
        return node;
    }

    /// Writes the data under the current name. Legacy names are never written.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of the data to be written.
    /// @param node The node to write into.
    /// @param child The names and the data.
    /// @return Reference to the node.
    template<typename NodeAdapter, typename T>
    inline NodeAdapter & operator<<(NodeAdapter & node, const RenamedChild<T> & child)
    {
        node << Child{child.current, child.data};
        return node;
    }
}   // namespace FileParse
