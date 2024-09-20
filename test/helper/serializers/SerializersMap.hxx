#pragma once

#include "include/fileParse/StringConversion.hxx"

#include "include/fileParse/Common.hxx"
#include "include/fileParse/Map.hxx"

#include "test/helper/structures/StructureMap.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          Helper::MapElementString & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        node >> Child{"OrderedMap", element.ordered};
        node >> Child{"UnorderedMap", element.unordered};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::MapElementString & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        node << Child{"OrderedMap", element.ordered};
        node << Child{"UnorderedMap", element.unordered};

        return node;
    }

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          Helper::MapElementOptionalString & element)
    {
        using FileParse::operator>>;

        node >> element.values;

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node,
                                    const Helper::MapElementOptionalString & element)
    {
        using FileParse::operator<<;

        node << element.values;

        return node;
    }

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          Helper::MapElementEnum & element)
    {
        FileParse::deserializeEnumMap<NodeAdapter, Helper::Day, std::string>(
          node, element.days, Helper::toDay);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::MapElementEnum & element)
    {
        FileParse::serializeEnumMap<NodeAdapter, Helper::Day, std::string>(
          node, element.days, Helper::toDayString);

        return node;
    }

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          Helper::MapElementDouble & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        node >> Child{"MapDouble", element.values};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::MapElementDouble & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        node << Child{"MapDouble", element.values};

        return node;
    }

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          Helper::MapElementEnumDouble & element)
    {
        FileParse::deserializeEnumMap<NodeAdapter, Helper::Day, double>(
          node, element.days, Helper::toDay);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node,
                                    const Helper::MapElementEnumDouble & element)
    {
        FileParse::serializeEnumMap<NodeAdapter, Helper::Day, double>(
          node, element.days, Helper::toDayString);

        return node;
    }
}   // namespace Helper