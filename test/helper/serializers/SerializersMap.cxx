#include "SerializersMap.hxx"

#include "Common.hxx"
#include "Map.hxx"

#include "xmlParser.h"

XMLNodeAdapter Helper::operator>>(const XMLNodeAdapter & xmlNode, Helper::MapElementString & element)
{
    using FileParse::operator>>;

    xmlNode >> element.values;

    return xmlNode;
}

XMLNodeAdapter Helper::operator<<(XMLNodeAdapter xmlNode, const Helper::MapElementString & element)
{
    using FileParse::operator<<;

    xmlNode << element.values;

    return xmlNode;
}

XMLNodeAdapter Helper::operator>>(const XMLNodeAdapter & xmlNode, Helper::MapElementOptionalString & element)
{
    using FileParse::operator>>;

    xmlNode >> element.values;

    return xmlNode;
}

XMLNodeAdapter Helper::operator<<(XMLNodeAdapter xmlNode, const Helper::MapElementOptionalString & element)
{
    using FileParse::operator<<;

    xmlNode << element.values;

    return xmlNode;
}

XMLNodeAdapter Helper::operator>>(const XMLNodeAdapter & xmlNode, Helper::MapElementEnum & element)
{
    FileParse::deserializeEnumMap<XMLNodeAdapter, Helper::Day>(xmlNode, element.days, Helper::toDay);

    return xmlNode;
}

XMLNodeAdapter Helper::operator<<(XMLNodeAdapter xmlNode, const Helper::MapElementEnum & element)
{
    FileParse::serializeEnumMap<XMLNodeAdapter, Helper::Day>(xmlNode, element.days, Helper::toDayString);

    return xmlNode;
}

XMLNodeAdapter Helper::operator>>(const XMLNodeAdapter & xmlNode, Helper::MapElementDouble & element)
{
    using FileParse::operator>>;

    xmlNode >> element.values;

    return xmlNode;
}

XMLNodeAdapter Helper::operator<<(XMLNodeAdapter xmlNode, const Helper::MapElementDouble & element)
{
    using FileParse::operator<<;

    xmlNode << element.values;

    return xmlNode;
}

Helper::MapElementString Helper::loadMapElementString(std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

    MapElementString element;
    xmlNode >> Child{"StringMap", element};

    return element;
}

void Helper::saveSetElementDouble(const Helper::MapElementString & element, std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

    xmlNode << Child{"StringMap", element};
    xmlNode.writeToFile(fileName);
}

Helper::MapElementOptionalString Helper::loadMapElementOptionalString(std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

    MapElementOptionalString element;
    xmlNode >> Child{"OptionalStringMap", element};

    return element;
}

void Helper::saveSetElementOptionalDouble(const Helper::MapElementOptionalString & element, std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};
    xmlNode << Child{"OptionalStringMap", element};

    xmlNode.writeToFile(fileName);
}

Helper::MapElementEnum Helper::loadMapElementEnum(std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

    MapElementEnum element;
    xmlNode >> Child{"EnumMap", element};

    return element;
}

void Helper::saveSetElementEnum(const Helper::MapElementEnum & element, std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

    xmlNode << Child{"EnumMap", element};
    xmlNode.writeToFile(fileName);
}

Helper::MapElementDouble Helper::loadMapElementDouble(std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

    MapElementDouble element;
    xmlNode >> Child{"DoubleMap", element};

    return element;
}

void Helper::saveSetElementDouble(const Helper::MapElementDouble & element, std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

    xmlNode << Child{"DoubleMap", element};
    xmlNode.writeToFile(fileName);
}
