#pragma once

#include "test/helper/serializers/SerializerCMAValues.hxx"
#include "test/helper/serializers/SerializersEnum.hxx"
#include "test/helper/structures/CMAEnumOptions.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          Helper::CMAEnumOptions & element)
    {
        using FileParse::Child;

        node >> Child{"Glazing", element.glazingOption};
        node >> Child{"Spacer", element.spacerOption};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::CMAEnumOptions & element)
    {
        using FileParse::Child;

        node << Child{"Glazing", element.glazingOption};
        node << Child{"Spacer", element.spacerOption};

        return node;
    }
}