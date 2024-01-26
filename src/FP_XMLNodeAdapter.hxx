#pragma once

#include <memory>
#include <optional>

#include "FP_INodeAdapter.hxx"

namespace XMLParser
{
    struct XMLNode;
}

class XMLNodeAdapter : public INodeAdapter<XMLNodeAdapter>
{
public:
    explicit XMLNodeAdapter(XMLParser::XMLNode xmlNode);

    [[nodiscard]] bool isEmpty() const override;
    [[nodiscard]] std::string getCurrentTag() const override;
    [[nodiscard]] bool isCurrentTag(std::string_view name) const override;
    [[nodiscard]] std::string getText() const override;
    [[nodiscard]] int nChildNode() const override;
    [[nodiscard]] XMLNodeAdapter getChildNode(int i) const override;
    [[nodiscard]] XMLNodeAdapter getChildNode(std::string_view name, int i) const override;
    [[nodiscard]] int nChildNode(std::string_view name) const override;
    [[nodiscard]] bool hasChildNode(std::string_view name) const override;
    [[nodiscard]] XMLNodeAdapter addChild(std::string_view name) const override;
    void addText(std::string_view text) const override;

    [[nodiscard]] int writeToUTF8(std::string_view outString) const;
    [[nodiscard]] int writeToFile(std::string_view outString) const;

private:
    struct Impl;
    std::shared_ptr<Impl> pimpl_;
};

[[nodiscard]] XMLNodeAdapter createTopNode(std::string_view topNodeName);
[[nodiscard]] std::optional<XMLNodeAdapter> getTopNode(std::string_view fileName,
                                                       std::string_view topNodeName);