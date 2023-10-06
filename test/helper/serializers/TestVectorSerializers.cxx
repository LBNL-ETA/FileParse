#include "TestVectorSerializers.hxx"

#include "CommonSerializer.hxx"
#include "xmlParser.h"

namespace Helper
{
    XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::VectorElement & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        xmlNode >> Child{{"Table", "Value"}, element.values};

        return xmlNode;
    }

    XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::VectorElement & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        xmlNode << Child{{"Table", "Value"}, element.values};

        return xmlNode;
    }

    XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, OptionalVectorElement & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        xmlNode >> Child{{"Table", "Value"}, element.values};

        return xmlNode;
    }

    XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const OptionalVectorElement & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        xmlNode << Child{{"Table", "Value"}, element.values};

        return xmlNode;
    }

    VectorElement loadVectorElement(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        VectorElement element;
        xmlNode >> Child{"VectorElement", element};

        return element;
    }

    void saveVectorElement(const VectorElement & element, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"VectorElement", element};

        xmlNode.writeToFile(fileName);
    }

    OptionalVectorElement loadOptionalVectorElement(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        OptionalVectorElement element;
        xmlNode >> Child{"OptionalVectorElement", element};

        return element;
    }

    void saveOptionalVectorElement(const OptionalVectorElement & element, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"OptionalVectorElement", element};

        xmlNode.writeToFile(fileName);
    }
}   // namespace Helper