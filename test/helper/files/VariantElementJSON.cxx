#include "VariantElementJSON.hxx"

#include "test/helper/structures/StructureVariant.hxx"
#include "../serializers/SerializersVariant.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    std::optional<VariantsAll> loadVariantAllJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<VariantsAll>(fileName, "Test");
    }

    int saveVariantAllJSON(const VariantsAll & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "Test");
    }
}
