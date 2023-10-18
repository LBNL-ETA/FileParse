#include "SerializersEnum.hxx"

#include "xmlParser.h"
#include "XMLNodeAdapter.hxx"

namespace Helper
{
    EnumElement loadEnumElement(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        EnumElement enumEl;
        xmlNode >> Child{"EnumElement", enumEl};

        return enumEl;
    }

    void saveEnumElement(const EnumElement & element, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};
        xmlNode << Child{"EnumElement", element};

        xmlNode.writeToFile(fileName);
    }
}   // namespace Helper