/// File: JSONNodeAdapter.hxx
/// @brief Provides a node adapter for JSON parsing and serialization
///        using nlohmann/json library.

#pragma once

#include <memory>

#include "INodeAdapter.hxx"
#include <nlohmann/json_fwd.hpp>

/// Class JSONNodeAdapter
/// Adapts nlohmann::json for use with FileParse functionalities.
class JSONNodeAdapter : public INodeAdapter<JSONNodeAdapter>
{
public:
    /// Constructor for JSONNodeAdapter.
    /// @param jsonPtr A pointer to nlohmann::json to be adapted.
    /// @param key The key name for this node (empty for root values).
    explicit JSONNodeAdapter(nlohmann::json * jsonPtr, std::string key = "");

    /// Checks if the node is empty.
    /// @return True if the node is empty, false otherwise.
    [[nodiscard]] bool isEmpty() const override;

    /// Gets the current tag (key) of the node.
    /// @return The current tag as a string.
    [[nodiscard]] std::string getCurrentTag() const override;

    /// Gets the text content of the node.
    /// @return The text content as a string.
    [[nodiscard]] std::string getText() const override;

    /// Retrieves all child nodes.
    /// @return A vector of child node adapters.
    [[nodiscard]] std::vector<JSONNodeAdapter> getChildNodes() const override;

    /// Retrieves the first child node with a specified name.
    /// @param name The name of the child node to retrieve.
    /// @return An optional containing the child node adapter if successful, std::nullopt otherwise.
    [[nodiscard]] std::optional<JSONNodeAdapter>
      getFirstChildByName(std::string_view name) const override;

    /// Retrieves all child nodes with a specified name.
    /// @param name The name of the child nodes to retrieve.
    /// @return A vector of child node adapters with the specified name.
    [[nodiscard]] std::vector<JSONNodeAdapter>
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
    /// If a child with the same name exists, it will be converted to an array.
    /// @param name The name of the new child node.
    /// @return The newly added child node adapter.
    [[nodiscard]] JSONNodeAdapter addChild(std::string_view name) override;

    /// Adds text content to the node.
    /// @param text The text to add to the node.
    void addText(std::string_view text) override;

    /// Writes the node's content to a file.
    /// @param fileName The name of the file to write the content to.
    /// @return 0 on success, non-zero on failure.
    [[nodiscard]] int writeToFile(std::string_view fileName) const;

    /// Gets the content of the entire node structure as a JSON string.
    /// @return The JSON content as a string.
    [[nodiscard]] std::string getContent() const override;

    /// Adds an attribute to the node (stored as a regular property in JSON).
    /// @param name The name of the attribute.
    /// @param value The value of the attribute.
    void addAttribute(std::string_view name, std::string_view value) override;

    /// Gets an attribute value from the node.
    /// @param name The name of the attribute to retrieve.
    /// @return An optional containing the attribute value if found, std::nullopt otherwise.
    [[nodiscard]] std::optional<std::string> getAttribute(std::string_view name) const override;

private:
    struct Impl;
    std::shared_ptr<Impl> pimpl_;   ///< Pointer to the implementation details.

    // Private constructor for factory functions
    explicit JSONNodeAdapter(std::shared_ptr<Impl> impl);

    friend JSONNodeAdapter createJSONTopNode(std::string_view topNodeName);
    friend std::optional<JSONNodeAdapter> getJSONTopNodeFromFile(std::string_view fileName,
                                                                  std::string_view topNodeName);
    friend std::optional<JSONNodeAdapter> getJSONTopNodeFromString(std::string_view json,
                                                                    std::string_view topNodeName);
};

/// Creates a top-level JSON node with a specified name.
/// @param topNodeName The name of the top node.
/// @return The top node adapter.
[[nodiscard]] JSONNodeAdapter createJSONTopNode(std::string_view topNodeName);

/// Retrieves the top-level JSON node from a file.
/// @param fileName The name of the file containing the JSON data.
/// @param topNodeName The name of the top node to retrieve.
/// @return An optional containing the top node adapter if successful, std::nullopt otherwise.
[[nodiscard]] std::optional<JSONNodeAdapter> getJSONTopNodeFromFile(std::string_view fileName,
                                                                     std::string_view topNodeName);

/// Retrieves the top-level JSON node from a string.
/// @param json The JSON string to parse.
/// @param topNodeName The name of the top node to retrieve.
/// @return An optional containing the top node adapter if successful, std::nullopt otherwise.
[[nodiscard]] std::optional<JSONNodeAdapter> getJSONTopNodeFromString(std::string_view json,
                                                                       std::string_view topNodeName);
