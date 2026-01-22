#include "VectorElementJSON.hxx"

#include "test/helper/structures/StructureVector.hxx"
#include "../serializers/SerializersVector.hxx"

#include "fileParse/FileDataHandler.hxx"
#include "include/fileParse/JSONNodeAdapter.hxx"

namespace Helper
{
    std::optional<VectorElement> loadVectorElementJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<VectorElement>(fileName, "VectorElement");
    }

    int saveVectorElementJSON(const VectorElement & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "VectorElement");
    }

    std::optional<OptionalVectorElement> loadOptionalVectorElementJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<OptionalVectorElement>(fileName, "OptionalVectorElement");
    }

    int saveOptionalVectorElementJSON(const OptionalVectorElement & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "OptionalVectorElement");
    }

    std::optional<EnumVectorElement> loadEnumVectorElementJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<EnumVectorElement>(fileName, "EnumVectorElement");
    }

    int saveEnumVectorElementJSON(const EnumVectorElement & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "EnumVectorElement");
    }
}   // namespace Helper
