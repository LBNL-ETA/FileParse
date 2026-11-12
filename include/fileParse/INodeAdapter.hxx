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

    /// Optional capability: the file format has value types other than text (JSON does, XML
    /// does not). An adapter that offers these methods receives numbers and booleans through
    /// them; every other adapter keeps receiving them through addText, unchanged.
    ///
    /// addNumber takes the number already formatted as text, so the configured precision
    /// applies to every format in the same way.
    template<typename AdapterType>
    concept TypedValueAdapter =
      requires(AdapterType & adapter, std::string_view text, bool flag)
    {
        { adapter.addNumber(text) } -> std::same_as<void>;
        { adapter.addBoolean(flag) } -> std::same_as<void>;
    };

    /// Optional capability: the file format tells a list from a single child (JSON does: an
    /// array against an object; XML does not: both are repeated elements). An adapter that
    /// offers addListChild receives every item of a list through it, so a list with one item
    /// is still written as a list. Every other adapter keeps receiving items through addChild.
    template<typename AdapterType>
    concept ListChildAdapter = requires(AdapterType & adapter, std::string_view name)
    {
        { adapter.addListChild(name) } -> std::same_as<AdapterType>;
    };

    /// Writes a number that is already formatted as text.
    template<typename NodeAdapter>
    inline void addNumberText(NodeAdapter & node, std::string_view text)
    {
        if constexpr(TypedValueAdapter<NodeAdapter>)
        {
            node.addNumber(text);
        }
        else
        {
            node.addText(text);
        }
    }

    /// Writes a boolean value.
    template<typename NodeAdapter>
    inline void addBooleanValue(NodeAdapter & node, bool value)
    {
        if constexpr(TypedValueAdapter<NodeAdapter>)
        {
            node.addBoolean(value);
        }
        else
        {
            node.addText(value ? "true" : "false");
        }
    }

    /// Adds a child that is one item of a list of children with the same name.
    template<typename NodeAdapter>
    [[nodiscard]] inline NodeAdapter addListChild(NodeAdapter & node, std::string_view name)
    {
        if constexpr(ListChildAdapter<NodeAdapter>)
        {
            return node.addListChild(name);
        }
        else
        {
            return node.addChild(name);
        }
    }
}   // namespace FileParse
