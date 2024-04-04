/// File: FP_INodeAdapter.hxx
/// @brief Defines the INodeAdapter interface which provides a set of functions
///        for node manipulation and data extraction, used by a general parser.

#pragma once

#include <string>
#include <vector>
#include <optional>

/// Interface INodeAdapter provides a set of virtual functions for node manipulation
/// and data extraction in a tree-like structure.
/// @tparam AdapterType The specific adapter type that implements the interface.
template<typename AdapterType>
class INodeAdapter
{
public:
    virtual ~INodeAdapter() = default;

    /// Checks if the current node is empty.
    [[nodiscard]] virtual bool isEmpty() const = 0;

    /// Gets the tag of the current node.
    [[nodiscard]] virtual std::string getCurrentTag() const = 0;

    /// Gets the text content of the current node.
    [[nodiscard]] virtual std::string getText() const = 0;

    // Gets all child nodes of the current node.
    [[nodiscard]] virtual std::vector<AdapterType> getChildNodes() const = 0;

    /// If child with given name exists, it will return the first child node with the given name.
    [[nodiscard]] virtual std::optional<AdapterType>
      getFirstChildByName(std::string_view name) const = 0;

    /// Gets the child nodes with the specified name.
    [[nodiscard]] virtual std::vector<AdapterType> getChildNodesByName(std::string_view name) const
      = 0;

    /// Counts the number of child nodes with the specified name.
    [[nodiscard]] virtual int nChildNode(std::string_view name) const = 0;

    /// Checks if the current node has a child node with the specified name.
    [[nodiscard]] virtual bool hasChildNode(std::string_view name) const = 0;

    /// Adds a child node with the specified name to the current node.
    [[nodiscard]] virtual AdapterType addChild(std::string_view name) = 0;

    /// Adds text content to the current node.
    virtual void addText(std::string_view text) = 0;
};
