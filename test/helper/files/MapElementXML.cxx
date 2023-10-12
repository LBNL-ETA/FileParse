#include "MapElementXML.hxx"

std::string Helper::testMapElementStringDatabase()
{
    static const std::string rootTag{"Test"};
    std::string fileContent{"<" + rootTag + ">\n"};
    fileContent += mapElementString();
    fileContent += "</" + rootTag + ">";
    return fileContent;
}

std::string Helper::mapElementString()
{
    return "\t<StringMap>\n"
           "\t\t<Key1>Value1</Key1>\n"
           "\t\t<Key2>Value2</Key2>\n"
           "\t\t<Key3>Value3</Key3>\n"
           "\t</StringMap>\n";
}
