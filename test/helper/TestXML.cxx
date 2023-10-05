#include "TestXML.hxx"

namespace Helper
{
    std::string testBaseElementDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += baseElement();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string baseElement()
    {
        return "\t<BaseElement>"
               "\t\t<SampleText>TestText</SampleText>"
               "\t\t<OptionalText>OptionalText</OptionalText>"
               "\t\t<Integer>13</Integer>"
               "\t\t<OptionalInteger>23</OptionalInteger>"
               "\t\t<Double>3.1415926</Double>"
               "\t\t<OptionalDouble>4.1415926</OptionalDouble>"
               "\t\t<VariantString>VariantText</VariantString>"
               "\t</BaseElement>";
    }

    std::string testVectorElementDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += vectorElement();
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

}   // namespace Helper
