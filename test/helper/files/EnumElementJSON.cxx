#include "EnumElementJSON.hxx"

#include "test/helper/structures/StructureEnum.hxx"
#include "helper/serializers/SerializersEnum.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    std::optional<EnumElement> loadEnumElementJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<EnumElement>(fileName, "EnumElement");
    }

    int saveEnumElementJSON(const EnumElement & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "EnumElement");
    }

}   // namespace Helper
