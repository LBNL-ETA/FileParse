#pragma once

#include <string>

#include "xmlParser/xmlParser.h"

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
    XMLNodeAdapter addChild(std::string_view name);
    XMLNodeAdapter addChild(XMLNodeAdapter & node);
    void addText(std::string_view text);
    XMLParser::XMLError writeToUTF8(std::string_view outString);

private:
    XMLParser::XMLNode node_;
};