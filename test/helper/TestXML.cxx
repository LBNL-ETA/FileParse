#include "TestXML.hxx"

namespace Helper
{
    std::string testDatabase()
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
               "\t</BaseElement>";
    }

}   // namespace Helper
