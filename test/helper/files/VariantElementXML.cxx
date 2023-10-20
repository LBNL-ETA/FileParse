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
        fileContent += variantParentString();
        fileContent += variantParentDouble();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string variantParentString()
    {
        return "\t<VariantParentString>\n"
               "\t\t<Name>\n"
               "\t\t\tString Parent\n"
               "\t\t</Name>\n"
               "\t\t<StringValue>\n"
               "\t\t\tThis is a test\n"
               "\t\t</StringValue>\n"
               "\t</VariantParentString>\n";
    }

    std::string variantParentDouble()
    {
        return "\t<VariantParentDouble>\n"
               "\t\t<Name>\n"
               "\t\t\tDouble Parent\n"
               "\t\t</Name>\n"
               "\t\t<DoubleValue>\n"
               "\t\t\t9.493743\n"
               "\t\t</DoubleValue>\n"
               "\t</VariantParentDouble>\n";
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