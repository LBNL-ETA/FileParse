#include "SerializersSet.hxx"

#include "XMLNodeAdapter.hxx"
#include "xmlParser.h"

namespace Helper
{
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