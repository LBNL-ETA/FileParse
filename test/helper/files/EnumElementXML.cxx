#include "EnumElementXML.hxx"

#include "test/helper/structures/StructureEnum.hxx"
#include "../serializers/SerializersEnum.hxx"

#include "FP_XMLNodeAdapter.hxx"

namespace Helper
{
    std::string testEnumDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += enumElement();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string enumElement()
    {
        return "\t<EnumElement>\n"
               "\t\t<Day>\n"
               "\t\t\tMonday\n"
               "\t\t</Day>\n"
               "\t\t<Color>\n"
               "\t\t\tBlue\n"
               "\t\t</Color>\n"
               "\t</EnumElement>\n";
    }

    std::string testEnumDatabaseOptionalMissing() {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += enumElementOptionalMissing();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string enumElementOptionalMissing() {
        return "\t<EnumElement>\n"
               "\t\t<Day>\n"
               "\t\t\tMonday\n"
               "\t\t</Day>\n"
               "\t</EnumElement>\n";
    }

    EnumElement loadEnumElement(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNode(fileName, "Test")};

        EnumElement enumEl;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> Child{"EnumElement", enumEl};
        }

        return enumEl;
    }

    void saveEnumElement(const EnumElement & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << Child{"EnumElement", element};

        xmlNode.writeToFile(fileName);
    }

}   // namespace Helper
