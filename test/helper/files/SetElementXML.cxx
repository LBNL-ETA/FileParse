#include "SetElementXML.hxx"

namespace Helper
{
    std::string testSetElementDoubleDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += setElementDouble();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string setElementDouble()
    {
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

    std::string testSetElementEmptyDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += setElementEmpty();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string setElementEmpty()
    {
        return "\t<SetElementDouble>\n"
               "\t\t<Table>\n"
               "\t\t</Table>\n"
               "\t</SetElementDouble>";
    }

    std::string testSetElementOptionalDoubleDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += setElementOptionalDouble();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string setElementOptionalDouble()
    {
        return "\t<SetElementOptionalDouble>\n"
               "\t\t<Table>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t43.215483\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t76.842907\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t12.689342\n"
               "\t\t\t</Value>\n"
               "\t\t</Table>\n"
               "\t</SetElementOptionalDouble>";
    }

}   // namespace Helper
