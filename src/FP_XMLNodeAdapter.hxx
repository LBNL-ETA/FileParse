#pragma once

#include <memory>
#include <string>
#include <optional>

namespace XMLParser
{
    struct XMLNode;
}

class XMLNodeAdapter
{
public:
    explicit XMLNodeAdapter(XMLParser::XMLNode xmlNode);

    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] std::string getCurrentTag() const;
    [[nodiscard]] bool isCurrentTag(std::string_view name) const;
    [[nodiscard]] std::string getText() const;
    [[nodiscard]] int nChildNode() const;
    [[nodiscard]] XMLNodeAdapter getChildNode(int i = 0) const;
    [[nodiscard]] XMLNodeAdapter getChildNode(std::string_view name, int i = 0) const;
    [[nodiscard]] int nChildNode(std::string_view name) const;
    [[nodiscard]] bool hasChildNode(std::string_view name) const;
    [[nodiscard]] XMLNodeAdapter addChild(std::string_view name) const;
    void addText(std::string_view text) const;
    [[nodiscard]] int writeToUTF8(std::string_view outString) const;
    [[nodiscard]] int writeToFile(std::string_view outString) const;

private:
    struct Impl;
    std::shared_ptr<Impl> pimpl_;
};

XMLNodeAdapter createTopNode(std::string_view topNodeName);
std::optional<XMLNodeAdapter> getTopNode(std::string_view fileName, std::string_view topNodeName);