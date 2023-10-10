#include "BaseElementXML.hxx"

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
               "\t\t<Size_t>18</Size_t>"
               "\t\t<Boolean>true</Boolean>"
               "\t\t<OptionalDouble>4.1415926</OptionalDouble>"
               "\t\t<OptionalBoolean>false</OptionalBoolean>"
               "\t\t<VariantString>VariantText</VariantString>"
               "\t</BaseElement>";
    }
}   // namespace Helper
