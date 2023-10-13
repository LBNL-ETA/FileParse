#include "SerializersMap.hxx"

#include "Common.hxx"
#include "Map.hxx"

#include "xmlParser.h"

XMLNodeAdapter Helper::operator>>(const XMLNodeAdapter & xmlNode, Helper::MapElementString & element)
{
    using FileParse::Child;
    using FileParse::operator>>;

    xmlNode >> Child{"OrderedMap", element.ordered};
    xmlNode >> Child{"UnorderedMap", element.unordered};

    return xmlNode;
}

XMLNodeAdapter Helper::operator<<(XMLNodeAdapter xmlNode, const Helper::MapElementString & element)
{
    using FileParse::Child;
    using FileParse::operator<<;

    xmlNode << Child{"OrderedMap", element.ordered};
    xmlNode << Child{"UnorderedMap", element.unordered};

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

XMLNodeAdapter Helper::operator>>(const XMLNodeAdapter & xmlNode, Helper::MapElementEnumDouble & element)
{
    FileParse::deserializeEnumMap<XMLNodeAdapter, Helper::Day>(xmlNode, element.days, Helper::toDay);

    return xmlNode;
}

XMLNodeAdapter Helper::operator<<(XMLNodeAdapter xmlNode, const Helper::MapElementEnumDouble & element)
{
    FileParse::serializeEnumMap<XMLNodeAdapter, Helper::Day>(xmlNode, element.days, Helper::toDayString);

    return xmlNode;
}

Helper::MapElementString Helper::loadMapElementString(std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

    MapElementString element;
    xmlNode >> element;

    return element;
}

void Helper::saveMapElementDouble(const MapElementString &element, std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

    xmlNode << element;
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

void Helper::saveMapElementOptionalDouble(const MapElementOptionalString &element, std::string_view fileName)
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

void Helper::saveMapElementEnum(const MapElementEnum &element, std::string_view fileName)
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

void Helper::saveMapElementDouble(const MapElementDouble &element, std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

    xmlNode << Child{"DoubleMap", element};
    xmlNode.writeToFile(fileName);
}

Helper::MapElementEnumDouble Helper::loadMapElementEnumDouble(std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

    MapElementEnumDouble element;
    xmlNode >> Child{"EnumDoubleMap", element};

    return element;
}

void Helper::saveMapElementEnumDouble(const MapElementEnumDouble &element, std::string_view fileName)
{
    using FileParse::Child;

    XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

    xmlNode << Child{"EnumDoubleMap", element};

    xmlNode.writeToFile(fileName);
}
