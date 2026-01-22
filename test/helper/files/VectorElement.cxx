#include "VectorElement.hxx"

#include "test/helper/structures/StructureVector.hxx"
#include "../serializers/SerializersVector.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    // XML functions
    std::optional<VectorElement> loadVectorElementXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<VectorElement>(fileName, "VectorElement");
    }

    int saveVectorElementXML(const VectorElement & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "VectorElement");
    }

    std::optional<OptionalVectorElement> loadOptionalVectorElementXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<OptionalVectorElement>(fileName, "OptionalVectorElement");
    }

    int saveOptionalVectorElementXML(const OptionalVectorElement & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "OptionalVectorElement");
    }

    std::optional<EnumVectorElement> loadEnumVectorElementXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<EnumVectorElement>(fileName, "EnumVectorElement");
    }

    int saveEnumVectorElementXML(const EnumVectorElement & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "EnumVectorElement");
    }

    // JSON functions
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
