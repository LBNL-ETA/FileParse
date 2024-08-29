#include "AttributesXML.hxx"

#include "test/helper/structures/Attributes.hxx"
#include "../serializers/SerializerAttributes.hxx"

#include "fileParse/Common.hxx"
#include "fileParse/XMLNodeAdapter.hxx"

namespace Helper
{
    std::string testAttributesDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += attributesElement();
        fileContent += "\n</" + rootTag + ">";
        return fileContent;
    }

    std::string attributesElement()
    {
        return "\t<AttributesTest Name=\"Text\" Age=\"23\" Height=\"1.93\" Day=\"Tuesday\" "
               "OptionalAge=\"18\" Nickname=\"Charlie\" />";
    }

    AttributesTest loadAttributesElement(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNodeFromFile(fileName, "Test")};

        AttributesTest base;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> Child{"AttributesTest", base};
        }

        return base;
    }

    int saveAttributesElement(const AttributesTest & object, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << Child{"AttributesTest", object};

        return xmlNode.writeToFile(fileName);
    }
}   // namespace Helper