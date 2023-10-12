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

std::string Helper::testMapElementDoubleDatabase()
{
    static const std::string rootTag{"Test"};
    std::string fileContent{"<" + rootTag + ">\n"};
    fileContent += mapElementDouble();
    fileContent += "</" + rootTag + ">";
    return fileContent;
}

std::string Helper::mapElementDouble()
{
    return "\t<DoubleMap>\n"
           "\t\t<Key1>37.582914</Key1>\n"
           "\t\t<Key2>92.143057</Key2>\n"
           "\t\t<Key3>15.907634</Key3>\n"
           "\t</DoubleMap>\n";
}

std::string Helper::testMapElementOptionalStringDatabase()
{
    static const std::string rootTag{"Test"};
    std::string fileContent{"<" + rootTag + ">\n"};
    fileContent += mapElementOptionalString();
    fileContent += "</" + rootTag + ">";
    return fileContent;
}

std::string Helper::mapElementOptionalString()
{
    return "\t<OptionalStringMap>\n"
           "\t\t<Key1>Optional1</Key1>\n"
           "\t\t<Key2>Optional2</Key2>\n"
           "\t\t<Key3>Optional3</Key3>\n"
           "\t</OptionalStringMap>\n";
}

std::string Helper::testMapElementEmptyStringDatabase()
{
    static const std::string rootTag{"Test"};
    std::string fileContent{"<" + rootTag + ">\n"};
    fileContent += mapElementEmptyString();
    fileContent += "</" + rootTag + ">";
    return fileContent;
}

std::string Helper::mapElementEmptyString()
{
    return "\t<OptionalStringMap>\n"
           "\t</OptionalStringMap>\n";
}

std::string Helper::testMapElementDayAsKeyDatabase()
{
    static const std::string rootTag{"Test"};
    std::string fileContent{"<" + rootTag + ">\n"};
    fileContent += mapElementDayAsKey();
    fileContent += "</" + rootTag + ">";
    return fileContent;
}

std::string Helper::mapElementDayAsKey()
{
    return "\t<EnumMap>\n"
           "\t\t<Friday>Happy</Friday>\n"
           "\t\t<Saturday>Relax</Saturday>\n"
           "\t\t<Monday>Back to Work</Monday>\n"
           "\t</EnumMap>\n";
}
