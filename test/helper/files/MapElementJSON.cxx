#include "MapElementJSON.hxx"

#include "test/helper/structures/StructureMap.hxx"
#include "../serializers/SerializersMap.hxx"
#include "test/helper/structures/CMAStringOptions.hxx"
#include "../serializers/SerializerCMAStringOptions.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    std::optional<MapElementString> loadMapElementStringJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<MapElementString>(fileName, "MapString");
    }

    int saveMapElementDoubleJSON(const MapElementString & element, std::string_view fileName)
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
