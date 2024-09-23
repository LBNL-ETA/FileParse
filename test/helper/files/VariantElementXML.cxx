#include "VariantElementXML.hxx"

#include "test/helper/structures/StructureVariant.hxx"
#include "../serializers/SerializersVariant.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    std::optional<VariantsAll> loadVariantAll(std::string_view fileName)
    {
        return Common::loadFromXMLFile<VariantsAll>(fileName, "Test");
    }

    int saveVariantAll(const VariantsAll & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "Test");
    }
}