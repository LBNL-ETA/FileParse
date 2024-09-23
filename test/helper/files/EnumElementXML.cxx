#include "EnumElementXML.hxx"

#include "test/helper/structures/StructureEnum.hxx"
#include "helper/serializers/SerializersEnum.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    std::optional<EnumElement> loadEnumElement(std::string_view fileName)
    {
        return Common::loadFromXMLFile<EnumElement>(fileName, "EnumElement");
    }

    int saveEnumElement(const EnumElement & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "EnumElement");
    }

}   // namespace Helper
