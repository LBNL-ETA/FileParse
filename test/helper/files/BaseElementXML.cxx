#include "BaseElementXML.hxx"

#include "helper/structures/StructureBase.hxx"
#include "helper/serializers/SerializersBaseElement.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    std::optional<BaseElement> loadBaseElement(std::string_view fileName)
    {
        return Common::loadFromXMLFile<BaseElement>(fileName, "BaseElement");
    }

    int saveBaseElement(const BaseElement & base, std::string_view fileName)
    {
        return Common::saveToXMLFile(base, fileName, "BaseElement");
    }
}   // namespace Helper
