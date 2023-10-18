#include "SerializersMap.hxx"

#include "XMLNodeAdapter.hxx"
#include "xmlParser.h"

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
