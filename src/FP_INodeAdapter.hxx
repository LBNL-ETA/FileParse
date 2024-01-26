#pragma once

#include <string>

// Simple interface for Node functions used by general parser
template<typename AdapterType>
class INodeAdapter {
public:
    virtual ~INodeAdapter() = default;

    [[nodiscard]] virtual bool isEmpty() const = 0;
    [[nodiscard]] virtual std::string getCurrentTag() const = 0;
    [[nodiscard]] virtual bool isCurrentTag(std::string_view name) const = 0;
    [[nodiscard]] virtual std::string getText() const = 0;
    [[nodiscard]] virtual int nChildNode() const = 0;
    [[nodiscard]] virtual AdapterType getChildNode(int i) const = 0;
    [[nodiscard]] virtual AdapterType getChildNode(std::string_view name, int i) const = 0;
    [[nodiscard]] virtual int nChildNode(std::string_view name) const = 0;
    [[nodiscard]] virtual bool hasChildNode(std::string_view name) const = 0;
    [[nodiscard]] virtual AdapterType addChild(std::string_view name) const = 0;
    virtual void addText(std::string_view text) const = 0;
};
