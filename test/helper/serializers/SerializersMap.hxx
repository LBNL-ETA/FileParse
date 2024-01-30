#pragma once

#include "FP_StringConversion.hxx"

#include "FP_Common.hxx"
#include "FP_Map.hxx"

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

        node >> Child{"DoubleMap", element.values};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::MapElementDouble & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        node << Child{"DoubleMap", element.values};

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

    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node, Helper::CMAOptions & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        node >> Child{"Glazing", element.glazingOption};
        node >> Child{"Spacer", element.spacerOption};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::CMAOptions & element)
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
}   // namespace Helper