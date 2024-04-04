#pragma once

#include "include/fileParse/Common.hxx"
#include "include/fileParse/Map.hxx"

#include "test/helper/serializers/SerializerCMAEnumOptions.hxx"
#include "test/helper/structures/CMAValues.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, Helper::CMAValues & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        node >> Child{"Conductivity", element.conductivity};
        node >> Child{"FilmCoefficient", element.filmCoefficient};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::CMAValues & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        node << Child{"Conductivity", element.conductivity};
        node << Child{"FilmCoefficient", element.filmCoefficient};

        return node;
    }
}