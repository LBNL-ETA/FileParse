#pragma once

#include "FP_StringConversion.hxx"

#include "FP_Common.hxx"
#include "FP_Map.hxx"

#include "test/helper/serializers/SerializerCMAValues.hxx"
#include "test/helper/structures/CMAStringOptions.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, Helper::CMAStringOptions & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        node >> Child{"Glazing", element.glazingOption};
        node >> Child{"Spacer", element.spacerOption};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::CMAStringOptions & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        node << Child{"Glazing", element.glazingOption};
        node << Child{"Spacer", element.spacerOption};

        return node;
    }

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, Helper::CMAElement & element)
    {
        using FileParse::Child;

        FileParse::deserializeMapAsChilds(node, "Element", element.options);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::CMAElement & element)
    {
        using FileParse::Child;

        FileParse::serializeMapAsChilds(node, "Element", element.options);

        return node;
    }
}