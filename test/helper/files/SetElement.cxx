#include "SetElement.hxx"

#include "test/helper/structures/StructureSet.hxx"
#include "../serializers/SerializersSet.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    // XML functions
    std::optional<SetElementDouble> loadSetElementDoubleXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<SetElementDouble>(fileName, "SetElementDouble");
    }

    int saveSetElementDoubleXML(const SetElementDouble & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "SetElementDouble");
    }

    std::optional<SetElementOptionalDouble> loadSetElementOptionalDoubleXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<SetElementOptionalDouble>(fileName,
                                                                 "SetElementOptionalDouble");
    }

    int saveSetElementOptionalDoubleXML(const SetElementOptionalDouble & element,
                                        std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "SetElementOptionalDouble");
    }

    std::optional<SetElementEnum> loadSetElementEnumXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<SetElementEnum>(fileName, "SetElementEnum");
    }

    int saveSetElementEnumXML(const SetElementEnum & element, std::string_view fileName)
    {
        return Common::saveToXMLFile(element, fileName, "SetElementEnum");
    }

    // JSON functions
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
