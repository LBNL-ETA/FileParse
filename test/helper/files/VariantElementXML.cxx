#include "VariantElementXML.hxx"

#include "test/helper/structures/StructureVariant.hxx"
#include "../serializers/SerializersVariant.hxx"

#include "XMLNodeAdapter.hxx"

namespace Helper
{

    std::string testVariantParent()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += variantParentTemperature();
        fileContent += variantParentHumidity();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string variantParentTemperature()
    {
        return "\t<VariantParentTemperature>\n"
               "\t\t<Name>\n"
               "\t\t\tParent Temperature\n"
               "\t\t</Name>\n"
               "\t\t<Temperature>\n"
               "\t\t\t23.15\n"
               "\t\t</Temperature>\n"
               "\t\t<OptionalString>\n"
               "\t\t\ttest optional\n"
               "\t\t</OptionalString>\n"
               "\t</VariantParentTemperature>\n";
    }

    std::string variantParentHumidity()
    {
        return "\t<VariantParentHumidity>\n"
               "\t\t<Name>\n"
               "\t\t\tParent Humidity\n"
               "\t\t</Name>\n"
               "\t\t<Humidity>\n"
               "\t\t\t9.493743\n"
               "\t\t</Humidity>\n"
               "\t</VariantParentHumidity>\n";
    }

    VariantsAll loadVariantAll(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNode(fileName, "Test")};

        VariantsAll element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> element;
        }

        return element;
    }

    void saveVariantAll(const VariantsAll & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << element;

        xmlNode.writeToFile(fileName);
    }
}