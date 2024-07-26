/// File: FP_XMLNodeAdapter.hxx
/// @brief Provides a node adapter for XML parsing and serialization
///        using an internal implementation of XMLNode.

#pragma once

#include <memory>

#include "INodeAdapter.hxx"

namespace XMLParser
{
    struct XMLNode;
}

/// Class XMLNodeAdapter
/// Adapts XMLNode for use with FileParse functionalities.
class XMLNodeAdapter : public INodeAdapter<XMLNodeAdapter>
{
public:
    /// Constructor for XMLNodeAdapter.
    /// @param xmlNode An XMLNode to be adapted.
    explicit XMLNodeAdapter(XMLParser::XMLNode xmlNode);

    /// Checks if the node is empty.
    /// @return True if the node is empty, false otherwise.
    [[nodiscard]] bool isEmpty() const override;

    /// Gets the current tag of the node.
    /// @return The current tag as a string.
    [[nodiscard]] std::string getCurrentTag() const override;

    /// Gets the text content of the node.
    /// @return The text content as a string.
    [[nodiscard]] std::string getText() const override;

    /// Retrieves all child nodes.
    /// @return A vector of child node adapters.
    [[nodiscard]] std::vector<XMLNodeAdapter> getChildNodes() const override;

    /// Retrieves the first child node with a specified name.
    /// @param name The name of the child node to retrieve.
    /// @return An optional containing the child node adapter if successful, std::nullopt otherwise.
    [[nodiscard]] std::optional<XMLNodeAdapter>
      getFirstChildByName(std::string_view name) const override;

    /// Retrieves all child nodes with a specified name.
    /// @param name The name of the child nodes to retrieve.
    /// @return A vector of child node adapters with the specified name.
    [[nodiscard]] std::vector<XMLNodeAdapter>
      getChildNodesByName(std::string_view name) const override;

    /// Counts the number of child nodes with a specified name.
    /// @param name The name of the child nodes to count.
    /// @return The number of child nodes with the specified name.
    [[nodiscard]] int nChildNode(std::string_view name) const override;

    /// Checks if the node has a child with a specified name.
    /// @param name The name of the child node to check.
    /// @return True if a child node with the specified name exists, false otherwise.
    [[nodiscard]] bool hasChildNode(std::string_view name) const override;

    /// Adds a new child node with a specified name.
    /// @param name The name of the new child node.
    /// @return The newly added child node adapter.
    [[nodiscard]] XMLNodeAdapter addChild(std::string_view name) override;

    /// Adds text content to the node.
    /// @param text The text to add to the node.
    void addText(std::string_view text) override;

    /// Writes the node's content to a file.
    /// @param outString The name of the file to write the content to.
    /// @return The number of characters written.
    [[nodiscard]] int writeToFile(std::string_view outString) const;

private:
    struct Impl;
    std::shared_ptr<Impl> pimpl_;   ///< Pointer to the implementation details.
};

/// Creates a top-level XML node with a specified name.
/// @param topNodeName The name of the top node.
/// @return The top node adapter.
[[nodiscard]] XMLNodeAdapter createTopNode(std::string_view topNodeName);

/// Retrieves the top-level XML node from a file.
/// @param fileName The name of the file containing the XML data.
/// @param topNodeName The name of the top node to retrieve.
/// @return An optional containing the top node adapter if successful, std::nullopt otherwise.
[[nodiscard]] std::optional<XMLNodeAdapter> getTopNodeFromFile(std::string_view fileName,
                                                       std::string_view topNodeName);

[[nodiscard]] std::optional<XMLNodeAdapter> getTopNodeFromString(std::string_view xml,
                                                       std::string_view topNodeName);