#include "MapElementXML.hxx"

#include "test/helper/structures/StructureMap.hxx"
#include "../serializers/SerializersMap.hxx"
#include "test/helper/structures/CMAStringOptions.hxx"
#include "../serializers/SerializerCMAStringOptions.hxx"

#include "include/fileParse/XMLNodeAdapter.hxx"

namespace Helper
{

    std::string testMapElementStringDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += mapElementString();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string mapElementString()
    {
        return "\t<OrderedMap>\n"
               "\t\t<Key1>Value1</Key1>\n"
               "\t\t<Key2>Value2</Key2>\n"
               "\t\t<Key3>Value3</Key3>\n"
               "\t</OrderedMap>\n"
               "\t<UnorderedMap>\n"
               "\t\t<K1>V1</K1>\n"
               "\t\t<K2>V2</K2>\n"
               "\t\t<K3>V3</K3>\n"
               "\t</UnorderedMap>\n";
    }

    std::string testMapElementDoubleDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += mapElementDouble();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string mapElementDouble()
    {
        return "\t<DoubleMap>\n"
               "\t\t<Key1>37.582914</Key1>\n"
               "\t\t<Key2>92.143057</Key2>\n"
               "\t\t<Key3>15.907634</Key3>\n"
               "\t</DoubleMap>\n";
    }

    std::string testMapElementOptionalStringDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += mapElementOptionalString();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string mapElementOptionalString()
    {
        return "\t<OptionalStringMap>\n"
               "\t\t<Key1>Optional1</Key1>\n"
               "\t\t<Key2>Optional2</Key2>\n"
               "\t\t<Key3>Optional3</Key3>\n"
               "\t</OptionalStringMap>\n";
    }

    std::string testMapElementEmptyStringDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += mapElementEmptyString();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string mapElementEmptyString()
    {
        return "\t<OptionalStringMap>\n"
               "\t</OptionalStringMap>\n";
    }

    std::string testMapElementDayStringDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += mapElementDayString();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string mapElementDayString()
    {
        return "\t<EnumMap>\n"
               "\t\t<Friday>Happy</Friday>\n"
               "\t\t<Saturday>Relax</Saturday>\n"
               "\t\t<Monday>Back to Work</Monday>\n"
               "\t</EnumMap>\n";
    }

    std::string testMapElementDayDoubleDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += mapElementDayDouble();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string mapElementDayDouble()
    {
        return "\t<EnumDoubleMap>\n"
               "\t\t<Monday>47.8621</Monday>\n"
               "\t\t<Thursday>83.2934</Thursday>\n"
               "\t\t<Saturday>12.7845</Saturday>\n"
               "\t</EnumDoubleMap>\n";
    }

    std::string testCMAElementDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += cmaElement1();
        fileContent += cmaElement2();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string cmaElement1()
    {
        return "\t<Element>\n"
               "\t\t<Glazing>Low</Glazing>\n"
               "\t\t<Spacer>Low</Spacer>\n"
               "\t\t<Conductivity>12.34</Conductivity>\n"
               "\t\t<FilmCoefficient>2.98</FilmCoefficient>\n"
               "\t</Element>\n";
    }

    std::string cmaElement2()
    {
        return "\t<Element>\n"
               "\t\t<Glazing>High</Glazing>\n"
               "\t\t<Spacer>High</Spacer>\n"
               "\t\t<Conductivity>1.731</Conductivity>\n"
               "\t\t<FilmCoefficient>7.39</FilmCoefficient>\n"
               "\t</Element>\n";
    }

    MapElementString loadMapElementString(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNodeFromFile(fileName, "Test")};

        MapElementString element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> element;
        }

        return element;
    }

    int saveMapElementDouble(const MapElementString & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << element;
        return xmlNode.writeToFile(fileName);
    }

    MapElementOptionalString loadMapElementOptionalString(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNodeFromFile(fileName, "Test")};

        MapElementOptionalString element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> Child{"OptionalStringMap", element};
        }

        return element;
    }

    int saveMapElementOptionalDouble(const MapElementOptionalString & element,
                                     std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};
        xmlNode << Child{"OptionalStringMap", element};

        return xmlNode.writeToFile(fileName);
    }

    MapElementEnum loadMapElementEnum(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNodeFromFile(fileName, "Test")};

        MapElementEnum element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> Child{"EnumMap", element};
        }

        return element;
    }

    int saveMapElementEnum(const MapElementEnum & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << Child{"EnumMap", element};
        return xmlNode.writeToFile(fileName);
    }

    MapElementDouble loadMapElementDouble(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNodeFromFile(fileName, "Test")};

        MapElementDouble element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> element;
        }

        return element;
    }

    int saveMapElementDouble(const MapElementDouble & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << element;

        return xmlNode.writeToFile(fileName);
    }

    MapElementEnumDouble loadMapElementEnumDouble(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNodeFromFile(fileName, "Test")};

        MapElementEnumDouble element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> Child{"EnumDoubleMap", element};
        }

        return element;
    }

    int saveMapElementEnumDouble(const MapElementEnumDouble & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << Child{"EnumDoubleMap", element};

        return xmlNode.writeToFile(fileName);
    }

    CMAElement loadCMAElement(std::string_view fileName)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        auto xmlNode{getTopNodeFromFile(fileName, "Test")};

        CMAElement element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> element;
        }

        return element;
    }

    int saveCMAElement(const CMAElement & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << element;

        return xmlNode.writeToFile(fileName);
    }
}   // namespace Helper
