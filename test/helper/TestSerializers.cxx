#include "TestSerializers.hxx"

#include "CommonSerializer.hxx"

namespace Helper
{
    XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::BaseElement & base)
    {
        using FileParse::Child;
        using FileParse::operator>>;
        using FileParse::deserializeVariant;

        xmlNode >> Child{"SampleText", base.text};
        xmlNode >> Child{"Integer", base.integer_number};
        xmlNode >> Child{"Double", base.double_number};
        xmlNode >> Child{"OptionalText", base.optional_text};
        xmlNode >> Child{"OptionalInteger", base.optional_int};
        xmlNode >> Child{"OptionalDouble", base.optional_double};
        deserializeVariant(xmlNode, {"VariantDouble", "VariantString"}, base.variant_field);
        // xmlNode >> Child{{"Double", "String"}, base.variant_field};

        return xmlNode;
    }

    XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::BaseElement & base)
    {
        using FileParse::Child;
        using FileParse::operator<<;
        using FileParse::serializeVariant;

        xmlNode << Child{"SampleText", base.text};
        xmlNode << Child{"Integer", base.integer_number};
        xmlNode << Child{"Double", base.double_number};
        xmlNode << Child{"OptionalText", base.optional_text};
        xmlNode << Child{"OptionalInteger", base.optional_int};
        xmlNode << Child{"OptionalDouble", base.optional_double};
        serializeVariant(xmlNode, {"VariantDouble", "VariantString"}, base.variant_field);
        // xmlNode << Child{{"Double", "String"}, base.variant_field};

        return xmlNode;
    }

    XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::VectorElement & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        xmlNode >> Child{{"Table", "Value"}, element.values};

        return xmlNode;
    }

    XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::VectorElement & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        xmlNode << Child{{"Table", "Value"}, element.values};

        return xmlNode;
    }

    XMLNodeAdapter operator>>(const XMLNodeAdapter &xmlNode, OptionalVectorElement &element) {
        using FileParse::Child;
        using FileParse::operator>>;

        xmlNode >> Child{{"Table", "Value"}, element.values};

        return xmlNode;
    }

    XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const OptionalVectorElement &element) {
        using FileParse::Child;
        using FileParse::operator<<;

        xmlNode << Child{{"Table", "Value"}, element.values};

        return xmlNode;
    }

    BaseElement loadBaseElement(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        BaseElement base;
        xmlNode >> Child{"BaseElement", base};

        return base;
    }

    void saveBaseElement(const BaseElement& base, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"BaseElement", base};

        xmlNode.writeToFile(fileName);
    }

    VectorElement loadVectorElement(std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        VectorElement element;
        xmlNode >> Child{"VectorElement", element};

        return element;
    }

    void saveVectorElement(const VectorElement & element, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"VectorElement", element};

        xmlNode.writeToFile(fileName);
    }

    OptionalVectorElement loadOptionalVectorElement(std::string_view fileName) {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        OptionalVectorElement element;
        xmlNode >> Child{"OptionalVectorElement", element};

        return element;
    }

    void saveOptionalVectorElement(const OptionalVectorElement &element, std::string_view fileName) {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"OptionalVectorElement", element};

        xmlNode.writeToFile(fileName);
    }
}   // namespace Helper