#include "VectorElementXML.hxx"

#include "test/helper/structures/StructureVector.hxx"
#include "../serializers/SerializersVector.hxx"

#include "include/fileParse/XMLNodeAdapter.hxx"

namespace Helper
{

    std::string testVectorElementDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += vectorElement();
        fileContent += optionalVectorElement();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string testVectorElementEmptyOptionalDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += vectorElement();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string testEmptyVectorElementDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += emptyVectorElement();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string testDayVectorElementDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += enumVectorElement();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string vectorElement()
    {
        return "\t<VectorElement>\n"
               "\t\t<Table>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t23.41\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t18.13\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t5.0756\n"
               "\t\t\t</Value>\n"
               "\t\t</Table>\n"
               "\t</VectorElement>";
    }

    std::string optionalVectorElement()
    {
        return "\t<OptionalVectorElement>\n"
               "\t\t<Table>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t33.41\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t28.13\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t6.0756\n"
               "\t\t\t</Value>\n"
               "\t\t</Table>\n"
               "\t</OptionalVectorElement>";
    }

    std::string emptyVectorElement()
    {
        return "\t<OptionalVectorElement>\n"
               "\t\t<Table>\n"
               "\t\t</Table>\n"
               "\t</OptionalVectorElement>";
    }

    std::string enumVectorElement() {
        return "\t<EnumVectorElement>\n"
               "\t\t<Table>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\tFriday\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\tSaturday\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\tSunday\n"
               "\t\t\t</Value>\n"
               "\t\t</Table>\n"
               "\t</EnumVectorElement>";
    }

    VectorElement loadVectorElement(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNodeFromFile(fileName, "Test")};

        VectorElement element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> Child{"VectorElement", element};
        }

        return element;
    }

    int saveVectorElement(const VectorElement & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << Child{"VectorElement", element};

        return xmlNode.writeToFile(fileName);
    }

    OptionalVectorElement loadOptionalVectorElement(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNodeFromFile(fileName, "Test")};

        OptionalVectorElement element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> Child{"OptionalVectorElement", element};
        }

        return element;
    }

    int saveOptionalVectorElement(const OptionalVectorElement & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << Child{"OptionalVectorElement", element};

        return xmlNode.writeToFile(fileName);
    }

    EnumVectorElement loadEnumVectorElement(std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{getTopNodeFromFile(fileName, "Test")};

        EnumVectorElement element;
        if(xmlNode.has_value())
        {
            xmlNode.value() >> Child{"EnumVectorElement", element};
        }

        return element;
    }

    int saveEnumVectorElement(const EnumVectorElement & element, std::string_view fileName)
    {
        using FileParse::Child;

        auto xmlNode{createTopNode("Test")};

        xmlNode << Child{"EnumVectorElement", element};

        return xmlNode.writeToFile(fileName);
    }
}   // namespace Helper
