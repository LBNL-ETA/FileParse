#include "XMLNodeAdapter.hxx"

#include "xmlParser/xmlParser.h"

struct XMLNodeAdapter::Impl {
  Impl(XMLParser::XMLNode xmlNode) : node_(xmlNode) {}
  XMLParser::XMLNode node_;
};

XMLNodeAdapter::XMLNodeAdapter(XMLParser::XMLNode xmlNode)
    : pimpl_(std::make_shared<Impl>(xmlNode)) {}

bool XMLNodeAdapter::isEmpty() const { return pimpl_->node_.isEmpty(); }

std::string XMLNodeAdapter::getText() const { return pimpl_->node_.getText(); }

int XMLNodeAdapter::nChildNode() const { return pimpl_->node_.nChildNode(); }

XMLNodeAdapter XMLNodeAdapter::getChildNode(int i) const {
  return XMLNodeAdapter(pimpl_->node_.getChildNode(i));
}

XMLNodeAdapter XMLNodeAdapter::getChildNode(std::string_view name,
                                            int i) const {
  return XMLNodeAdapter(pimpl_->node_.getChildNode(name.data(), i));
}

int XMLNodeAdapter::nChildNode(std::string_view name) const {
  return pimpl_->node_.nChildNode(name.data());
}

XMLNodeAdapter XMLNodeAdapter::addChild(std::string_view name) {
  return XMLNodeAdapter(pimpl_->node_.addChild(name.data()));
}

void XMLNodeAdapter::addText(std::string_view text) {
  pimpl_->node_.addText(text.data());
}

XMLNodeAdapter XMLNodeAdapter::addChild(XMLNodeAdapter &node) {
  return XMLNodeAdapter(pimpl_->node_.addChild(node.pimpl_->node_));
}

int XMLNodeAdapter::writeToUTF8(std::string_view outString) {
  return static_cast<int>(pimpl_->node_.writeToUTF8(outString.data()));
}

int XMLNodeAdapter::writeToFile(std::string_view outString)
{
  return pimpl_->node_.writeToFile(outString.data());
}

bool XMLNodeAdapter::hasChildNode(std::string_view name) const {
  return pimpl_->node_.nChildNode(name.data()) > 0;
}

std::string XMLNodeAdapter::getCurrentTag() const {
  return pimpl_->node_.getName();
}

bool XMLNodeAdapter::isCurrentTag(std::string_view name) const {
  return name == getCurrentTag();
}
