#pragma once

#include "Common.hxx"
#include "Vector.hxx"
#include "Variant.hxx"

#include "test/helper/structures/StructureVariant.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::VariantParent & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;
        using FileParse::deserializeVariant;

        node >> Child{"Name", element.name};
        deserializeVariant(node, {"StringValue", "DoubleValue"}, element.value);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::VariantParent & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;
        using FileParse::serializeVariant;

        node << Child{"Table", element.name};
        serializeVariant(node, {"StringValue", "DoubleValue"}, element.value);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::VariantsAll & element)
    {
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::VariantsAll & element)
    {
        return node;
    }
}