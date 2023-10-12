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
