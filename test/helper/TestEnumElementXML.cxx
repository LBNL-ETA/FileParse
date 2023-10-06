#include "TestEnumElementXML.hxx"

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


}   // namespace Helper
