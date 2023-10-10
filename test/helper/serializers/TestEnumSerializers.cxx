#include "TestEnumSerializers.hxx"

#include "Common.hxx"
#include "Enum.hxx"
#include "xmlParser.h"

namespace Helper
{

    XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, EnumElement & element)
    {
        FileParse::deserializeEnum<XMLNodeAdapter, Helper::Day>(xmlNode, "Day", element.day, Helper::toDay);
        FileParse::deserializeEnum<XMLNodeAdapter, Helper::Color>(xmlNode, "Color", element.color, Helper::toColor);

        return xmlNode;
    }

    XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const EnumElement & element)
    {
        FileParse::serializeEnum<XMLNodeAdapter, Helper::Day>(xmlNode, "Day", element.day, Helper::toDayString);
        FileParse::serializeEnum<XMLNodeAdapter, Helper::Color>(xmlNode, "Color", element.color, Helper::toString);

        return xmlNode;
    }

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