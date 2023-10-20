#include "MapElementXML.hxx"

#include "test/helper/structures/StructureMap.hxx"
#include "../serializers/SerializersMap.hxx"

#include "XMLNodeAdapter.hxx"

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

    MapElementString loadMapElementString(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNode(fileName, "Test")};

        MapElementString element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> element;
        }

        return element;
    }

    void saveMapElementDouble(const MapElementString & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << element;
        xmlNode.writeToFile(fileName);
    }

    MapElementOptionalString loadMapElementOptionalString(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNode(fileName, "Test")};

        MapElementOptionalString element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> Child{"OptionalStringMap", element};
        }

        return element;
    }

    void saveMapElementOptionalDouble(const MapElementOptionalString & element,
                                      std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};
        xmlNode << Child{"OptionalStringMap", element};

        xmlNode.writeToFile(fileName);
    }

    MapElementEnum loadMapElementEnum(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNode(fileName, "Test")};

        MapElementEnum element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> Child{"EnumMap", element};
        }

        return element;
    }

    void saveMapElementEnum(const MapElementEnum & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << Child{"EnumMap", element};
        xmlNode.writeToFile(fileName);
    }

    MapElementDouble loadMapElementDouble(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNode(fileName, "Test")};

        MapElementDouble element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> Child{"DoubleMap", element};
        }

        return element;
    }

    void saveMapElementDouble(const MapElementDouble & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << Child{"DoubleMap", element};
        xmlNode.writeToFile(fileName);
    }

    MapElementEnumDouble loadMapElementEnumDouble(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNode(fileName, "Test")};

        MapElementEnumDouble element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> Child{"EnumDoubleMap", element};
        }

        return element;
    }

    void saveMapElementEnumDouble(const MapElementEnumDouble & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << Child{"EnumDoubleMap", element};

        xmlNode.writeToFile(fileName);
    }
}   // namespace Helper
