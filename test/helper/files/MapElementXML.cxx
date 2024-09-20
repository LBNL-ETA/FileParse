#include "MapElementXML.hxx"

#include "test/helper/structures/StructureMap.hxx"
#include "../serializers/SerializersMap.hxx"
#include "test/helper/structures/CMAStringOptions.hxx"
#include "../serializers/SerializerCMAStringOptions.hxx"

#include "fileParse/XMLNodeAdapter.hxx"
#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
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

    std::optional<MapElementString> loadMapElementString(std::string_view fileName)
    {
        return Common::loadFromXMLFile<MapElementString>(fileName, "MapString");
    }

    int saveMapElementDouble(const MapElementString & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "MapString");
    }

    std::optional<MapElementOptionalString> loadMapElementOptionalString(std::string_view fileName)
    {
        return Common::loadFromXMLFile<MapElementOptionalString>(fileName, "OptionalStringMap");
    }

    int saveMapElementOptionalString(const MapElementOptionalString & element,
                                     std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "OptionalStringMap");
    }

    std::optional<MapElementEnum> loadMapElementEnum(std::string_view fileName)
    {
        return Common::loadFromXMLFile<MapElementEnum>(fileName, "EnumMap");
    }

    int saveMapElementEnum(const MapElementEnum & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "EnumMap");
    }

    std::optional<MapElementDouble> loadMapElementDouble(std::string_view fileName)
    {
        return Common::loadFromXMLFile<MapElementDouble>(fileName, "Test");
    }

    int saveMapElementDouble(const MapElementDouble & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "Test");
    }

    std::optional<MapElementEnumDouble> loadMapElementEnumDouble(std::string_view fileName)
    {
        return Common::loadFromXMLFile<MapElementEnumDouble>(fileName, "EnumDoubleMap");
    }

    int saveMapElementEnumDouble(const MapElementEnumDouble & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "EnumDoubleMap");
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
