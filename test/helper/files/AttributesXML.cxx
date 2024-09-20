#include "AttributesXML.hxx"

#include "helper/structures/Attributes.hxx"
#include "../serializers/SerializerAttributes.hxx"

#include "fileParse/Common.hxx"
#include "fileParse/XMLNodeAdapter.hxx"
#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    std::optional<AttributesTest> loadAttributesElement(std::string_view fileName)
    {
        return Common::loadFromXMLFile<AttributesTest>(fileName, "Test").value();
    }

    int saveAttributesElement(const AttributesTest & object, std::string_view fileName)
    {
        return Common::saveToXMLFile(object, fileName, "Test");
    }
}   // namespace Helper