#pragma once

#include "StringConversion.hxx"

#include "Common.hxx"
#include "Map.hxx"

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

    MapElementString loadMapElementString(std::string_view fileName);
    void saveMapElementDouble(const MapElementString & element, std::string_view fileName);

    MapElementOptionalString loadMapElementOptionalString(std::string_view fileName);
    void saveMapElementOptionalDouble(const MapElementOptionalString & element,
                                      std::string_view fileName);

    MapElementEnum loadMapElementEnum(std::string_view fileName);
    void saveMapElementEnum(const MapElementEnum & element, std::string_view fileName);

    MapElementDouble loadMapElementDouble(std::string_view fileName);
    void saveMapElementDouble(const MapElementDouble & element, std::string_view fileName);

    MapElementEnumDouble loadMapElementEnumDouble(std::string_view fileName);
    void saveMapElementEnumDouble(const MapElementEnumDouble & element, std::string_view fileName);
}   // namespace Helper