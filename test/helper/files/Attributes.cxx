#include "Attributes.hxx"

#include "helper/structures/Attributes.hxx"
#include "helper/serializers/SerializerAttributes.hxx"

#include "fileParse/Common.hxx"
#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    std::optional<AttributesTest> loadAttributesElementXML(std::string_view fileName)
    {
        return Common::loadFromXMLFile<AttributesTest>(fileName, "Test").value();
    }

    int saveAttributesElementXML(const AttributesTest & object, std::string_view fileName)
    {
        return Common::saveToXMLFile(object, fileName, "Test");
    }
}   // namespace Helper
