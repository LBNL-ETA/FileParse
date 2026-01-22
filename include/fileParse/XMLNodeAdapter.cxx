#include <algorithm>
#include <iterator>

#include "XMLNodeAdapter.hxx"

#include "xmlParser/xmlParser.h"

struct XMLNodeAdapter::Impl
{
    explicit Impl(XMLParser::XMLNode xmlNode) : node_(xmlNode)
    {}
    XMLParser::XMLNode node_;
};

XMLNodeAdapter::XMLNodeAdapter(XMLParser::XMLNode xmlNode) : pimpl_(std::make_shared<Impl>(xmlNode))
{}

bool XMLNodeAdapter::isEmpty() const
{
    return pimpl_->node_.isEmpty();
}

std::string XMLNodeAdapter::getText() const
{
    // getText will return nullptr if the text is empty string. This will cause a crash in the
    // calling code. So, we need to check for nullptr and return empty string in that case.
    if(pimpl_->node_.getText())
    {
        return pimpl_->node_.getText();
    }
    return {};
}

std::vector<XMLNodeAdapter> XMLNodeAdapter::getChildNodes() const
{
    std::vector<XMLNodeAdapter> children;
    children.reserve(pimpl_->node_.nChildNode());

    for(int i = 0; i < pimpl_->node_.nChildNode(); ++i)
    {
        children.emplace_back(pimpl_->node_.getChildNode(i));
    }

    return children;
}

std::optional<XMLNodeAdapter> XMLNodeAdapter::getFirstChildByName(std::string_view name) const
{
    for(int i = 0; i < pimpl_->node_.nChildNode(); ++i)
    {
        if(auto childNode{pimpl_->node_.getChildNode(i)}; childNode.getName() == name)
        {
            return XMLNodeAdapter(childNode);
        }
    }
    return std::nullopt;
}

std::vector<XMLNodeAdapter> XMLNodeAdapter::getChildNodesByName(std::string_view name) const
{
    std::vector<XMLNodeAdapter> filteredChildren;
    filteredChildren.reserve(pimpl_->node_.nChildNode());

    for(int i = 0; i < pimpl_->node_.nChildNode(); ++i)
    {
        auto childNode = pimpl_->node_.getChildNode(i);
        if(childNode.getName() == name)
        {
            filteredChildren.emplace_back(childNode);
        }
    }

    filteredChildren.shrink_to_fit();

    return filteredChildren;
}

int XMLNodeAdapter::nChildNode(std::string_view name) const
{
    return pimpl_->node_.nChildNode(name.data());
}

XMLNodeAdapter XMLNodeAdapter::addChild(std::string_view name)
{
    return XMLNodeAdapter(pimpl_->node_.addChild(name.data()));
}

void XMLNodeAdapter::addText(std::string_view text)
{
    pimpl_->node_.addText(text.data());
}

int XMLNodeAdapter::writeToFile(std::string_view outString) const
{
    return pimpl_->node_.writeToFile(outString.data());
}

bool XMLNodeAdapter::hasChildNode(std::string_view name) const
{
    return pimpl_->node_.nChildNode(name.data()) > 0;
}

std::string XMLNodeAdapter::getCurrentTag() const
{
    return pimpl_->node_.getName();
}

std::string XMLNodeAdapter::getContent() const
{
    return pimpl_->node_.createXMLString();
}

void XMLNodeAdapter::addAttribute(std::string_view name, std::string_view value)
{
    pimpl_->node_.addAttribute(name.data(), value.data());
}

std::optional<std::string> XMLNodeAdapter::getAttribute(std::string_view name) const
{
    if(const char * attribute{pimpl_->node_.getAttribute(name.data())}; attribute != nullptr)
    {
        return std::string(attribute);
    }
    return std::nullopt;
}

XMLNodeAdapter createXMLTopNode(std::string_view topNodeName)
{
    return XMLNodeAdapter(XMLParser::XMLNode::createXMLTopNode(topNodeName.data()));
}

std::optional<XMLNodeAdapter> getXMLTopNodeFromFile(std::string_view fileName,
                                                    std::string_view topNodeName)
{
    try
    {
        auto node = XMLParser::XMLNode::openFileHelperThrows(fileName.data(), topNodeName.data());
        if(!node.isEmpty())
        {
            return XMLNodeAdapter(node);
        }
    }
    catch(const std::exception &)
    {
        // No need to log message for now. Empty optional will be returned indicating failure.
    }
    // Return empty optional if node is empty or an exception occurred
    return std::nullopt;
}

std::optional<XMLNodeAdapter> getXMLTopNodeFromString(std::string_view xml,
                                                      std::string_view topNodeName)
{
    if(auto node{XMLParser::XMLNode::parseString(xml.data(), topNodeName.data())}; !node.isEmpty())
    {
        return XMLNodeAdapter(node);
    }
    return std::nullopt;
}
