#include "SerializersVector.hxx"

#include "xmlParser.h"
#include "XMLNodeAdapter.hxx"

namespace Helper
{
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

    EnumVectorElement loadEnumVectorElement(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        EnumVectorElement element;
        xmlNode >> Child{"EnumVectorElement", element};

        return element;
    }

    void saveEnumVectorElement(const EnumVectorElement & element, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"EnumVectorElement", element};

        xmlNode.writeToFile(fileName);
    }
}   // namespace Helper