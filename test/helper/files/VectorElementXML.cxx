#include "VectorElementXML.hxx"

#include "test/helper/structures/StructureVector.hxx"
#include "../serializers/SerializersVector.hxx"

#include "fileParse/FileDataHandler.hxx"
#include "include/fileParse/XMLNodeAdapter.hxx"

namespace Helper
{
    std::optional<VectorElement> loadVectorElement(std::string_view fileName)
    {
        return Common::loadFromXMLFile<VectorElement>(fileName, "VectorElement");
    }

    int saveVectorElement(const VectorElement & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "VectorElement");
    }

    std::optional<OptionalVectorElement> loadOptionalVectorElement(std::string_view fileName)
    {
        return Common::loadFromXMLFile<OptionalVectorElement>(fileName, "OptionalVectorElement");
    }

    int saveOptionalVectorElement(const OptionalVectorElement & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "OptionalVectorElement");
    }

    std::optional<EnumVectorElement> loadEnumVectorElement(std::string_view fileName)
    {
        return Common::loadFromXMLFile<EnumVectorElement>(fileName, "EnumVectorElement");
    }

    int saveEnumVectorElement(const EnumVectorElement & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "EnumVectorElement");
    }
}   // namespace Helper
