#pragma once

#include "Common.hxx"
#include "Variant.hxx"
#include "Optional.hxx"

#include "test/helper/structures/StructureBase.hxx"

namespace Helper
{
    template <typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::BaseElement & base)
    {
        using FileParse::Child;
        using FileParse::operator>>;
        using FileParse::deserializeVariant;

        node >> Child{"SampleText", base.text};
        node >> Child{"Integer", base.integer_number};
        node >> Child{"Double", base.double_number};
        node >> Child{"Boolean", base.boolean_field};
        node >> Child{"Size_t", base.size_t_field};

        node >> Child{"OptionalText", base.optional_text};
        node >> Child{"OptionalInteger", base.optional_int};
        node >> Child{"OptionalDouble", base.optional_double};
        node >> Child{"OptionalBoolean", base.boolean_optional};
        deserializeVariant(node, {"VariantDouble", "VariantString"}, base.variant_field);

        return node;
    }

    template <typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::BaseElement & base)
    {
        using FileParse::Child;
        using FileParse::operator<<;
        using FileParse::serializeVariant;

        node << Child{"SampleText", base.text};
        node << Child{"Integer", base.integer_number};
        node << Child{"Double", base.double_number};
        node << Child{"Boolean", base.boolean_field};
        node << Child{"Size_t", base.size_t_field};

        node << Child{"OptionalText", base.optional_text};
        node << Child{"OptionalInteger", base.optional_int};
        node << Child{"OptionalDouble", base.optional_double};
        node << Child{"OptionalBoolean", base.boolean_optional};
        serializeVariant(node, {"VariantDouble", "VariantString"}, base.variant_field);

        return node;
    }

    BaseElement loadBaseElement(std::string_view fileName);
    void saveBaseElement(const BaseElement & base, std::string_view fileName);
}   // namespace Helper