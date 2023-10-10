#include "BaseElementSerializers.hxx"

#include "Common.hxx"
#include "Variant.hxx"
#include "Optional.hxx"

#include "xmlParser.h"

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
        xmlNode >> Child{"Boolean", base.boolean_field};
        xmlNode >> Child{"Size_t", base.size_t_field};

        xmlNode >> Child{"OptionalText", base.optional_text};
        xmlNode >> Child{"OptionalInteger", base.optional_int};
        xmlNode >> Child{"OptionalDouble", base.optional_double};
        xmlNode >> Child{"OptionalBoolean", base.boolean_optional};
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
        xmlNode << Child{"Boolean", base.boolean_field};
        xmlNode << Child{"Size_t", base.size_t_field};

        xmlNode << Child{"OptionalText", base.optional_text};
        xmlNode << Child{"OptionalInteger", base.optional_int};
        xmlNode << Child{"OptionalDouble", base.optional_double};
        xmlNode << Child{"OptionalBoolean", base.boolean_optional};
        serializeVariant(xmlNode, {"VariantDouble", "VariantString"}, base.variant_field);
        // xmlNode << Child{{"Double", "String"}, base.variant_field};

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

    void saveBaseElement(const BaseElement & base, std::string_view fileName)
    {
        using FileParse::Child;

        XMLNodeAdapter xmlNode{XMLParser::XMLNode::createXMLTopNode("Test")};

        xmlNode << Child{"BaseElement", base};

        xmlNode.writeToFile(fileName);
    }
}   // namespace Helper