#include "EnumElement.hxx"

#include "test/helper/structures/StructureEnum.hxx"
#include "helper/serializers/SerializersEnum.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    // XML functions
    std::optional<EnumElement> loadEnumElementXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<EnumElement>(fileName, "EnumElement");
    }

    int saveEnumElementXML(const EnumElement & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "EnumElement");
    }

    // JSON functions
    std::optional<EnumElement> loadEnumElementJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<EnumElement>(fileName, "EnumElement");
    }

    int saveEnumElementJSON(const EnumElement & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "EnumElement");
    }

}   // namespace Helper
