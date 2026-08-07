/// File: INodeAdapter.hxx
/// @brief Defines the NodeAdapter concept, the contract every node adapter must
///        satisfy so the generic parser can traverse it.

#pragma once

#include <concepts>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace FileParse
{
    /// The generic serializer templates take adapters by concrete type, so the contract is
    /// checked at compile time rather than dispatched through a vtable. Adapters are created
    /// once per visited node, which makes a vptr and an indirect call per operation a cost
    /// paid on every node of every document.
    ///
    /// Attributes are only supported by XML. For JSON these behave as a child node whose tag
    /// is the attribute name and whose value goes into the value field.
    template<typename AdapterType>
    concept NodeAdapterLike = requires(AdapterType & adapter,
                                   const AdapterType & constAdapter,
                                   std::string_view name,
                                   std::string_view text)
    {
        /// Checks if the current node is empty.
        { constAdapter.isEmpty() } -> std::same_as<bool>;

        /// Gets the tag of the current node.
        { constAdapter.getCurrentTag() } -> std::same_as<std::string>;

        /// Gets the text content of the current node.
        { constAdapter.getText() } -> std::same_as<std::string>;

        /// Gets all child nodes of the current node.
        { constAdapter.getChildNodes() } -> std::same_as<std::vector<AdapterType>>;

        /// Returns the first child node with the given name, if one exists.
        { constAdapter.getFirstChildByName(name) } -> std::same_as<std::optional<AdapterType>>;

        /// Gets the child nodes with the specified name.
        { constAdapter.getChildNodesByName(name) } -> std::same_as<std::vector<AdapterType>>;

        /// Counts the number of child nodes with the specified name.
        { constAdapter.nChildNode(name) } -> std::same_as<int>;

        /// Checks if the current node has a child node with the specified name.
        { constAdapter.hasChildNode(name) } -> std::same_as<bool>;

        /// Adds a child node with the specified name to the current node.
        { adapter.addChild(name) } -> std::same_as<AdapterType>;

        /// Adds text content to the current node.
        { adapter.addText(text) } -> std::same_as<void>;

        /// The entire node structure as it will appear in the file.
        { constAdapter.getContent() } -> std::same_as<std::string>;

        { adapter.addAttribute(name, text) } -> std::same_as<void>;
        { constAdapter.getAttribute(name) } -> std::same_as<std::optional<std::string>>;
    };
}   // namespace FileParse
