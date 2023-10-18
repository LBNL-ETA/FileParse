#include "SetElementXML.hxx"

#include "test/helper/structures/StructureSet.hxx"
#include "../serializers/SerializersSet.hxx"

#include "XMLNodeAdapter.hxx"
#include "xmlParser.h"

namespace Helper
{
    std::string testSetElementDoubleDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += setElementDouble();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string setElementDouble()
    {
        return "\t<SetElementDouble>\n"
               "\t\t<Table>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t932.32\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t20.31\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t9.392\n"
               "\t\t\t</Value>\n"
               "\t\t</Table>\n"
               "\t</SetElementDouble>";
    }

    std::string testSetElementEmptyDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += setElementEmpty();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string setElementEmpty()
    {
        return "\t<SetElementDouble>\n"
               "\t\t<Table>\n"
               "\t\t</Table>\n"
               "\t</SetElementDouble>";
    }

    std::string testSetElementOptionalDoubleDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += setElementOptionalDouble();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string setElementOptionalDouble()
    {
        return "\t<SetElementOptionalDouble>\n"
               "\t\t<Table>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t43.215483\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t76.842907\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\t12.689342\n"
               "\t\t\t</Value>\n"
               "\t\t</Table>\n"
               "\t</SetElementOptionalDouble>";
    }

    std::string testSetElementEnumDatabase()
    {
        static const std::string rootTag{"Test"};
        std::string fileContent{"<" + rootTag + ">\n"};
        fileContent += setElementEnum();
        fileContent += "</" + rootTag + ">";
        return fileContent;
    }

    std::string setElementEnum()
    {
        return "\t<SetElementEnum>\n"
               "\t\t<Table>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\tWednesday\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\tFriday\n"
               "\t\t\t</Value>\n"
               "\t\t\t<Value>\n"
               "\t\t\t\tSunday\n"
               "\t\t\t</Value>\n"
               "\t\t</Table>\n"
               "\t</SetElementEnum>";
    }

    SetElementDouble loadSetElementDouble(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        SetElementDouble element;
        xmlNode >> Child{"SetElementDouble", element};

        return element;
    }

    void saveSetElementDouble(const SetElementDouble & element, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"SetElementDouble", element};

        xmlNode.writeToFile(fileName);
    }

    SetElementOptionalDouble loadSetElementOptionalDouble(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        SetElementOptionalDouble element;
        xmlNode >> Child{"SetElementOptionalDouble", element};

        return element;
    }

    void saveSetElementOptionalDouble(const SetElementOptionalDouble & element,
                                      std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"SetElementOptionalDouble", element};

        xmlNode.writeToFile(fileName);
    }

    SetElementEnum loadSetElementEnum(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        SetElementEnum element;
        xmlNode >> Child{"SetElementEnum", element};

        return element;
    }

    void saveSetElementEnum(const SetElementEnum & element, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"SetElementEnum", element};

        xmlNode.writeToFile(fileName);
    }

}   // namespace Helper
