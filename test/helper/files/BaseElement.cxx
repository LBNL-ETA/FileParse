#include "BaseElement.hxx"

#include "helper/structures/StructureBase.hxx"
#include "helper/serializers/SerializersBaseElement.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    // XML functions
    std::optional<BaseElement> loadBaseElementXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<BaseElement>(fileName, "BaseElement");
    }

    int saveBaseElementXML(const BaseElement & base, std::string_view fileName)
    {
        return Common::saveToXMLFile(base, fileName, "BaseElement");
    }

    // JSON functions
    std::optional<BaseElement> loadBaseElementJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<BaseElement>(fileName, "BaseElement");
    }

    int saveBaseElementJSON(const BaseElement & base, std::string_view fileName)
    {
        return Common::saveToJSONFile(base, fileName, "BaseElement");
    }
}   // namespace Helper
