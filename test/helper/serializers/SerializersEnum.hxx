#pragma once

#include "FP_Common.hxx"
#include "FP_Enum.hxx"
#include "FP_Optional.hxx"

#include "test/helper/structures/StructureEnum.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, Helper::Day & day)
    {
        FileParse::deserializeEnum<NodeAdapter, Helper::Day>(node, day, Helper::toDay);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::Day & day)
    {
        FileParse::serializeEnum<NodeAdapter, Helper::Day>(node, day, Helper::toDayString);

        return node;
    }

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, Helper::Color & color)
    {
        FileParse::deserializeEnum<NodeAdapter, Helper::Color>(node, color, Helper::toColor);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::Color & color)
    {
        FileParse::serializeEnum<NodeAdapter, Helper::Color>(node, color, Helper::toColorString);

        return node;
    }

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, Helper::Option & option)
    {
        FileParse::deserializeEnum<NodeAdapter, Helper::Option>(node, option, Helper::toOption);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::Option & option)
    {
        FileParse::serializeEnum<NodeAdapter, Helper::Option>(node, option, Helper::toOptionString);

        return node;
    }

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, Helper::EnumElement & element)
    {
        node >> FileParse::Child{"Day", element.day};
        node >> FileParse::Child{"Color", element.color};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::EnumElement & element)
    {
        node << FileParse::Child{"Day", element.day};
        node << FileParse::Child{"Color", element.color};

        return node;
    }
}   // namespace Helper