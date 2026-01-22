#include "MapElement.hxx"

#include "test/helper/structures/StructureMap.hxx"
#include "../serializers/SerializersMap.hxx"
#include "test/helper/structures/CMAStringOptions.hxx"
#include "../serializers/SerializerCMAStringOptions.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    // XML functions
    std::optional<MapElementString> loadMapElementStringXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<MapElementString>(fileName, "MapString");
    }

    int saveMapElementStringXML(const MapElementString & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "MapString");
    }

    std::optional<MapElementOptionalString> loadMapElementOptionalStringXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<MapElementOptionalString>(fileName, "OptionalStringMap");
    }

    int saveMapElementOptionalStringXML(const MapElementOptionalString & element,
                                        std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "OptionalStringMap");
    }

    std::optional<MapElementEnum> loadMapElementEnumXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<MapElementEnum>(fileName, "EnumMap");
    }

    int saveMapElementEnumXML(const MapElementEnum & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "EnumMap");
    }

    std::optional<MapElementDouble> loadMapElementDoubleXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<MapElementDouble>(fileName, "Test");
    }

    int saveMapElementDoubleXML(const MapElementDouble & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "Test");
    }

    std::optional<MapElementEnumDouble> loadMapElementEnumDoubleXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<MapElementEnumDouble>(fileName, "EnumDoubleMap");
    }

    int saveMapElementEnumDoubleXML(const MapElementEnumDouble & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "EnumDoubleMap");
    }

    std::optional<CMAElement> loadCMAElementXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<CMAElement>(fileName, "Test");
    }

    int saveCMAElementXML(const CMAElement & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "Test");
    }

    // JSON functions
    std::optional<MapElementString> loadMapElementStringJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<MapElementString>(fileName, "MapString");
    }

    int saveMapElementStringJSON(const MapElementString & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "MapString");
    }

    std::optional<MapElementOptionalString> loadMapElementOptionalStringJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<MapElementOptionalString>(fileName, "OptionalStringMap");
    }

    int saveMapElementOptionalStringJSON(const MapElementOptionalString & element,
                                         std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "OptionalStringMap");
    }

    std::optional<MapElementEnum> loadMapElementEnumJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<MapElementEnum>(fileName, "EnumMap");
    }

    int saveMapElementEnumJSON(const MapElementEnum & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "EnumMap");
    }

    std::optional<MapElementDouble> loadMapElementDoubleJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<MapElementDouble>(fileName, "Test");
    }

    int saveMapElementDoubleJSON(const MapElementDouble & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "Test");
    }

    std::optional<MapElementEnumDouble> loadMapElementEnumDoubleJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<MapElementEnumDouble>(fileName, "EnumDoubleMap");
    }

    int saveMapElementEnumDoubleJSON(const MapElementEnumDouble & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "EnumDoubleMap");
    }

    std::optional<CMAElement> loadCMAElementJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<CMAElement>(fileName, "Test");
    }

    int saveCMAElementJSON(const CMAElement & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "Test");
    }
}   // namespace Helper
