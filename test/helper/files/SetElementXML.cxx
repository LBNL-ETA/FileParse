#include "SetElementXML.hxx"

#include "test/helper/structures/StructureSet.hxx"
#include "../serializers/SerializersSet.hxx"

#include "include/fileParse/XMLNodeAdapter.hxx"
#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    std::optional<SetElementDouble> loadSetElementDouble(std::string_view fileName)
    {
        return Common::loadFromXMLFile<SetElementDouble>(fileName, "SetElementDouble");
    }

    int saveSetElementDouble(const SetElementDouble & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "SetElementDouble");
    }

    std::optional<SetElementOptionalDouble> loadSetElementOptionalDouble(std::string_view fileName)
    {
        return Common::loadFromXMLFile<SetElementOptionalDouble>(fileName,
                                                                 "SetElementOptionalDouble");
    }

    int saveSetElementOptionalDouble(const SetElementOptionalDouble & element,
                                     std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "SetElementOptionalDouble");
    }

    std::optional<SetElementEnum> loadSetElementEnum(std::string_view fileName)
    {
        return Common::loadFromXMLFile<SetElementEnum>(fileName, "SetElementEnum");
    }

    int saveSetElementEnum(const SetElementEnum & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "SetElementEnum");
    }

}   // namespace Helper
