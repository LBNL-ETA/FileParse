#pragma once

#include "FP_Common.hxx"
#include "FP_Set.hxx"

#include "test/helper/structures/StructureSet.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::SetElementDouble & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        node >> Child{{"Table", "Value"}, element.values};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::SetElementDouble & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        node << Child{{"Table", "Value"}, element.values};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node,
                                  Helper::SetElementOptionalDouble & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        node >> Child{{"Table", "Value"}, element.values};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node,
                                  const Helper::SetElementOptionalDouble & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        node << Child{{"Table", "Value"}, element.values};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::SetElementEnum & element)
    {
        FileParse::deserializeEnumSet<NodeAdapter, Helper::Day>(
          node, {"Table", "Value"}, element.days, toDay);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::SetElementEnum & element)
    {
        FileParse::serializeEnumSet<NodeAdapter, Helper::Day>(
          node, {"Table", "Value"}, element.days, toDayString);

        return node;
    }
}   // namespace Helper