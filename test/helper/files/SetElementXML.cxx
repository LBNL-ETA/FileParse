#include "SetElementXML.hxx"

namespace Helper
{
    std::string testSetElementDoubleDatabase() {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += setElementDouble();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string setElementDouble() {
        return "\t<SetElementDouble>\n"
               "\t\t<Table>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t932.32\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t20.31\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t9.392\n"
               "\t\t\t</Value>\n"
               "\t\t</Table>\n"
               "\t</SetElementDouble>";
    }
}
