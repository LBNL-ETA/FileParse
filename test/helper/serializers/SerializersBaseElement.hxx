#pragma once

#include "FP_Common.hxx"
#include "FP_Variant.hxx"
#include "FP_Optional.hxx"

#include "test/helper/structures/StructureBase.hxx"

namespace Helper
{
    ////////////////////////////////////////////////////
    ///  SampleText
    ////////////////////////////////////////////////////

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, TextElement & element)
    {
        using FileParse::Child;
        node >> Child{"SampleText", element.text};
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const TextElement & element)
    {
        using FileParse::Child;
        node << Child{"SampleText", element.text};
        return node;
    }

    ////////////////////////////////////////////////////
    ///  IntegerNumberElement
    ////////////////////////////////////////////////////

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, IntegerNumberElement & element)
    {
        using FileParse::Child;
        node >> Child{"Integer", element.integer_number};
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const IntegerNumberElement & element)
    {
        using FileParse::Child;
        node << Child{"Integer", element.integer_number};
        return node;
    }

    ////////////////////////////////////////////////////
    ///  OptionalIntegerElement
    ////////////////////////////////////////////////////

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          OptionalIntegerElement & element)
    {
        using FileParse::Child;
        node >> Child{"OptionalInteger", element.optional_int};
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const OptionalIntegerElement & element)
    {
        using FileParse::Child;
        node << Child{"OptionalInteger", element.optional_int};
        return node;
    }

    ////////////////////////////////////////////////////
    ///  DoubleNumberElement
    ////////////////////////////////////////////////////

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, DoubleNumberElement & element)
    {
        using FileParse::Child;
        node >> Child{"Double", element.double_number};
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const DoubleNumberElement & element)
    {
        using FileParse::Child;
        node << Child{"Double", element.double_number};
        return node;
    }

    ////////////////////////////////////////////////////
    ///  OptionalDoubleElement
    ////////////////////////////////////////////////////

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, OptionalDoubleElement & element)
    {
        using FileParse::Child;
        node >> Child{"OptionalDouble", element.optional_double};
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const OptionalDoubleElement & element)
    {
        using FileParse::Child;
        node << Child{"OptionalDouble", element.optional_double};
        return node;
    }

    ////////////////////////////////////////////////////
    ///  BooleanFieldElement
    ////////////////////////////////////////////////////

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, BooleanFieldElement & element)
    {
        using FileParse::Child;
        node >> Child{"Boolean", element.boolean_field};
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const BooleanFieldElement & element)
    {
        using FileParse::Child;
        node << Child{"Boolean", element.boolean_field};
        return node;
    }

    ////////////////////////////////////////////////////
    ///  OptionalBooleanElement
    ////////////////////////////////////////////////////

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          OptionalBooleanElement & element)
    {
        using FileParse::Child;
        node >> Child{"OptionalBoolean", element.optional_boolean};
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const OptionalBooleanElement & element)
    {
        using FileParse::Child;
        node << Child{"OptionalBoolean", element.optional_boolean};
        return node;
    }

    ////////////////////////////////////////////////////
    ///  SizeTFieldElement
    ////////////////////////////////////////////////////

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, SizeTFieldElement & element)
    {
        using FileParse::Child;
        node >> Child{"Size_t", element.size_t_field};
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const SizeTFieldElement & element)
    {
        using FileParse::Child;
        node << Child{"Size_t", element.size_t_field};
        return node;
    }

    ////////////////////////////////////////////////////
    ///  OptionalSizeTFieldElement
    ////////////////////////////////////////////////////

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, OptionalSizeTFieldElement & element)
    {
        using FileParse::Child;
        node >> Child{"OptionalSize_t", element.optional_size_t_field};
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const OptionalSizeTFieldElement & element)
    {
        using FileParse::Child;
        node << Child{"OptionalSize_t", element.optional_size_t_field};
        return node;
    }

    ////////////////////////////////////////////////////
    ///  VariantFieldElement
    ////////////////////////////////////////////////////

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, VariantFieldElement & element)
    {
        using FileParse::Child;
        using FileParse::deserializeVariant;

        deserializeVariant(node, {"Double", "String"}, element.variant_field);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const VariantFieldElement & element)
    {
        using FileParse::Child;
        using FileParse::serializeVariant;

        serializeVariant(node, {"Double", "String"}, element.variant_field);

        return node;
    }

    ////////////////////////////////////////////////////
    ///  OptionalVariantElement
    ////////////////////////////////////////////////////

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          OptionalVariantElement & element)
    {
        using FileParse::Child;
        using FileParse::deserializeOptionalVariant;

        deserializeOptionalVariant(node, {"VariantString", "VariantInt"}, element.optional_variant);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const OptionalVariantElement & element)
    {
        using FileParse::Child;
        using FileParse::serializeOptionalVariant;

        serializeOptionalVariant(node, {"VariantString", "VariantInt"}, element.optional_variant);

        return node;
    }

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, Helper::BaseElement & base)
    {
        using FileParse::Child;
        using FileParse::operator>>;
        using FileParse::deserializeVariant;
        using FileParse::deserializeOptionalVariant;

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
        deserializeOptionalVariant(node, {"VariantString1", "VariantInt"}, base.optional_variant);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::BaseElement & base)
    {
        using FileParse::Child;
        using FileParse::operator<<;
        using FileParse::serializeVariant;
        using FileParse::serializeOptionalVariant;

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
        serializeOptionalVariant(node, {"VariantString1", "VariantInt"}, base.optional_variant);

        return node;
    }
}   // namespace Helper