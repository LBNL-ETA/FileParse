#include "TestSerializers.hxx"

XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::BaseElement & base)
{
    xmlNode >> Child{"SampleText", base.text};
    xmlNode >> Child{"Integer", base.integer_number};
    xmlNode >> Child{"Double", base.double_number};
    xmlNode >> Child{"OptionalText", base.optional_text};
    xmlNode >> Child{"OptionalInteger", base.optional_int};
    xmlNode >> Child{"OptionalDouble", base.optional_double};
    deserializeVariant(xmlNode, {"VariantDouble", "VariantString"}, base.variant_field);
    //xmlNode >> Child{{"Double", "String"}, base.variant_field};

    return xmlNode;
}

XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::BaseElement & base)
{
    xmlNode << Child{"SampleText", base.text};
    xmlNode << Child{"Integer", base.integer_number};
    xmlNode << Child{"Double", base.double_number};
    xmlNode << Child{"OptionalText", base.optional_text};
    xmlNode << Child{"OptionalInteger", base.optional_int};
    xmlNode << Child{"OptionalDouble", base.optional_double};
    serializeVariant(xmlNode, {"VariantDouble", "VariantString"}, base.variant_field);
    //xmlNode << Child{{"Double", "String"}, base.variant_field};

    return xmlNode;
}

namespace Helper
{
    BaseElement loadBaseElement(std::string_view fileName)
    {
        XMLNodeAdapter xmlNode{XMLParser::XMLNode::openFileHelper(fileName.data(), "Test")};

        BaseElement base;
        xmlNode >> Child{"BaseElement", base};

        return base;
    }

    void saveBaseElement(const BaseElement& base, std::string_view fileName)
    {
        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"BaseElement", base};

        xmlNode.writeToFile(fileName);
    }
}   // namespace Helper