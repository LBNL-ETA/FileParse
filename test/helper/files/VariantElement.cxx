#include "VariantElement.hxx"

#include "test/helper/structures/StructureVariant.hxx"
#include "../serializers/SerializersVariant.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    // XML functions
    std::optional<VariantsAll> loadVariantAllXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<VariantsAll>(fileName, "Test");
    }

    int saveVariantAllXML(const VariantsAll & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "Test");
    }

    // JSON functions
    std::optional<VariantsAll> loadVariantAllJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<VariantsAll>(fileName, "Test");
    }

    int saveVariantAllJSON(const VariantsAll & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "Test");
    }
}   // namespace Helper
