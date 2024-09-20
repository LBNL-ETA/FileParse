#include "AttributesXML.hxx"

#include "test/helper/structures/Attributes.hxx"
#include "../serializers/SerializerAttributes.hxx"

#include "fileParse/Common.hxx"
#include "fileParse/XMLNodeAdapter.hxx"
#include "fileParse/FileDataHandler.hxx"

namespace Helper
{
    AttributesTest loadAttributesElement(std::string_view fileName)
    {
        return Common::loadFromXMLFile<AttributesTest>(fileName, "Test").value();
    }

    int saveAttributesElement(const AttributesTest & object, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << Child{"AttributesTest", object};

        return xmlNode.writeToFile(fileName);
    }
}   // namespace Helper