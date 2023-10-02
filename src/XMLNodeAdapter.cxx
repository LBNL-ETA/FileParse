#include "XMLNodeAdapter.hxx"

XMLNodeAdapter::XMLNodeAdapter(XMLParser::XMLNode xmlNode) : node_(std::move(xmlNode)) {}

bool XMLNodeAdapter::isEmpty() const {
    return node_.isEmpty();
}

std::string XMLNodeAdapter::getText() const {
    return node_.getText();
}

int XMLNodeAdapter::nChildNode() const {
    return node_.nChildNode();
}

XMLNodeAdapter XMLNodeAdapter::getChildNode(int i) const {
    return XMLNodeAdapter(node_.getChildNode(i));
}

XMLNodeAdapter XMLNodeAdapter::getChildNode(std::string_view name, int i) const {
    return XMLNodeAdapter(node_.getChildNode(name.data(), i));
}

int XMLNodeAdapter::nChildNode(std::string_view name) const {
    return node_.nChildNode(name.data());
}

XMLNodeAdapter XMLNodeAdapter::addChild(std::string_view name) {
    return XMLNodeAdapter(node_.addChild(name.data()));
}

void XMLNodeAdapter::addText(std::string_view text) {
    node_.addText(text.data());
}

XMLNodeAdapter XMLNodeAdapter::addChild(XMLNodeAdapter &node) {
    return XMLNodeAdapter(node_.addChild(node.node_));
}

XMLParser::XMLError XMLNodeAdapter::writeToUTF8(std::string_view outString) {
    return node_.writeToUTF8(outString.data());
}

bool XMLNodeAdapter::hasChildNode(std::string_view name) const {
    return node_.nChildNode(name.data()) > 0;
}

std::string XMLNodeAdapter::getCurrentTag() const {
    return node_.getName();
}

bool XMLNodeAdapter::isCurrentTag(std::string_view name) const {
    return name == getCurrentTag();
}
