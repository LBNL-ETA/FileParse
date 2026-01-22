#include "SetElementJSON.hxx"

#include "test/helper/structures/StructureSet.hxx"
#include "../serializers/SerializersSet.hxx"

#include "include/fileParse/JSONNodeAdapter.hxx"
#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    std::optional<SetElementDouble> loadSetElementDoubleJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<SetElementDouble>(fileName, "SetElementDouble");
    }

    int saveSetElementDoubleJSON(const SetElementDouble & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "SetElementDouble");
    }

    std::optional<SetElementOptionalDouble> loadSetElementOptionalDoubleJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<SetElementOptionalDouble>(fileName,
                                                                  "SetElementOptionalDouble");
    }

    int saveSetElementOptionalDoubleJSON(const SetElementOptionalDouble & element,
                                         std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "SetElementOptionalDouble");
    }

    std::optional<SetElementEnum> loadSetElementEnumJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<SetElementEnum>(fileName, "SetElementEnum");
    }

    int saveSetElementEnumJSON(const SetElementEnum & element, std::string_view fileName)
    {
        return Common::saveToJSONFile(element, fileName, "SetElementEnum");
    }

}   // namespace Helper
