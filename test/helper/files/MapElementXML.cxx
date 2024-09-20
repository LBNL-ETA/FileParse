#include "MapElementXML.hxx"

#include "test/helper/structures/StructureMap.hxx"
#include "../serializers/SerializersMap.hxx"
#include "test/helper/structures/CMAStringOptions.hxx"
#include "../serializers/SerializerCMAStringOptions.hxx"

#include "fileParse/XMLNodeAdapter.hxx"
#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
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

    std::optional<CMAElement> loadCMAElement(std::string_view fileName)
    {
        return Common::loadFromXMLFile<CMAElement>(fileName, "Test");
    }

    int saveCMAElement(const CMAElement & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "Test");
    }
}   // namespace Helper
