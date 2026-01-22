#include "BaseElementJSON.hxx"

#include "helper/structures/StructureBase.hxx"
#include "helper/serializers/SerializersBaseElement.hxx"

#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    std::optional<BaseElement> loadBaseElementJSON(std::string_view fileName)
    {
        return Common::loadFromJSONFile<BaseElement>(fileName, "BaseElement");
    }

    int saveBaseElementJSON(const BaseElement & base, std::string_view fileName)
    {
        return Common::saveToJSONFile(base, fileName, "BaseElement");
    }
}   // namespace Helper
