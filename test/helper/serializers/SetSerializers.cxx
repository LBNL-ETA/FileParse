#include "SetSerializers.hxx"

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
}   // namespace Helper