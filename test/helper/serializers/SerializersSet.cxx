#include "SerializersSet.hxx"

#include "Common.hxx"
#include "Set.hxx"

#include "xmlParser.h"

namespace Helper
{
    XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, SetElementDouble & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        xmlNode >> Child{{"Table", "Value"}, element.values};

        return xmlNode;
    }

    XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const SetElementDouble & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        xmlNode << Child{{"Table", "Value"}, element.values};

        return xmlNode;
    }

    XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, SetElementOptionalDouble & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        xmlNode >> Child{{"Table", "Value"}, element.values};

        return xmlNode;
    }

    XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const SetElementOptionalDouble & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        xmlNode << Child{{"Table", "Value"}, element.values};

        return xmlNode;
    }

    XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, SetElementEnum & element)
    {
        FileParse::deserializeEnumSet<XMLNodeAdapter, Helper::Day>(xmlNode, {"Table", "Value"}, element.days, toDay);

        return xmlNode;
    }

    XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const SetElementEnum & element)
    {
        FileParse::serializeEnumSet<XMLNodeAdapter, Helper::Day>(
          xmlNode, {"Table", "Value"}, element.days, toDayString);

        return xmlNode;
    }

    SetElementDouble loadSetElementDouble(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        SetElementDouble element;
        xmlNode >> Child{"SetElementDouble", element};

        return element;
    }

    void saveSetElementDouble(const SetElementDouble & element, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"SetElementDouble", element};

        xmlNode.writeToFile(fileName);
    }

    SetElementOptionalDouble loadSetElementOptionalDouble(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        SetElementOptionalDouble element;
        xmlNode >> Child{"SetElementOptionalDouble", element};

        return element;
    }

    void saveSetElementOptionalDouble(const SetElementOptionalDouble & element, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"SetElementOptionalDouble", element};

        xmlNode.writeToFile(fileName);
    }

    SetElementEnum loadSetElementEnum(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        SetElementEnum element;
        xmlNode >> Child{"SetElementEnum", element};

        return element;
    }

    void saveSetElementEnum(const SetElementEnum & element, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"SetElementEnum", element};

        xmlNode.writeToFile(fileName);
    }
}   // namespace Helper