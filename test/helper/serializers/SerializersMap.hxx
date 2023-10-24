#pragma once

#include "FP_StringConversion.hxx"

#include "FP_Common.hxx"
#include "FP_Map.hxx"

#include "test/helper/structures/StructureMap.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::MapElementString & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        node >> Child{"OrderedMap", element.ordered};
        node >> Child{"UnorderedMap", element.unordered};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::MapElementString & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        node << Child{"OrderedMap", element.ordered};
        node << Child{"UnorderedMap", element.unordered};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node,
                                  Helper::MapElementOptionalString & element)
    {
        using FileParse::operator>>;

        node >> element.values;

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node,
                                  const Helper::MapElementOptionalString & element)
    {
        using FileParse::operator<<;

        node << element.values;

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::MapElementEnum & element)
    {
        FileParse::deserializeEnumMap<NodeAdapter, Helper::Day>(node, element.days, Helper::toDay);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::MapElementEnum & element)
    {
        FileParse::serializeEnumMap<NodeAdapter, Helper::Day>(
          node, element.days, Helper::toDayString);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::MapElementDouble & element)
    {
        using FileParse::operator>>;

        node >> element.values;

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::MapElementDouble & element)
    {
        using FileParse::operator<<;

        node << element.values;

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::MapElementEnumDouble & element)
    {
        FileParse::deserializeEnumMap<NodeAdapter, Helper::Day>(node, element.days, Helper::toDay);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter xmlNode, const Helper::MapElementEnumDouble & element)
    {
        FileParse::serializeEnumMap<NodeAdapter, Helper::Day>(
          xmlNode, element.days, Helper::toDayString);

        return xmlNode;
    }
}   // namespace Helper