#include "VectorElementXML.hxx"

namespace Helper
{

    std::string testVectorElementDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += vectorElement();
        fileContent += optionalVectorElement();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string testVectorElementEmptyOptionalDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += vectorElement();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string testEmptyVectorElementDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += emptyVectorElement();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string vectorElement()
    {
        return "\t<VectorElement>\n"
               "\t\t<Table>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t23.41\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t18.13\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t5.0756\n"
               "\t\t\t</Value>\n"
               "\t\t</Table>\n"
               "\t</VectorElement>";
    }

    std::string optionalVectorElement()
    {
        return "\t<OptionalVectorElement>\n"
               "\t\t<Table>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t33.41\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t28.13\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t6.0756\n"
               "\t\t\t</Value>\n"
               "\t\t</Table>\n"
               "\t</OptionalVectorElement>";
    }

    std::string emptyVectorElement()
    {
        return "\t<OptionalVectorElement>\n"
               "\t\t<Table>\n"
               "\t\t</Table>\n"
               "\t</OptionalVectorElement>";
    }
}   // namespace Helper
