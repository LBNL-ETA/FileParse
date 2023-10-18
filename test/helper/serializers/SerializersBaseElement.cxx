#include "SerializersBaseElement.hxx"

#include "XMLNodeAdapter.hxx"
#include "xmlParser.h"

namespace Helper
{
    BaseElement loadBaseElement(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        BaseElement base;
        xmlNode >> Child{"BaseElement", base};

        return base;
    }

    void saveBaseElement(const BaseElement & base, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"BaseElement", base};

        xmlNode.writeToFile(fileName);
    }
}   // namespace Helper