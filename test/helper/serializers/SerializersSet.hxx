#pragma once

#include "Common.hxx"
#include "Set.hxx"

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
    inline NodeAdapter operator<<(NodeAdapter node,
                                     const Helper::SetElementEnum & element)
    {
        FileParse::serializeEnumSet<NodeAdapter, Helper::Day>(
          node, {"Table", "Value"}, element.days, toDayString);

        return node;
    }

    SetElementDouble loadSetElementDouble(std::string_view fileName);
    void saveSetElementDouble(const SetElementDouble & element, std::string_view fileName);

    SetElementOptionalDouble loadSetElementOptionalDouble(std::string_view fileName);
    void saveSetElementOptionalDouble(const SetElementOptionalDouble & element,
                                      std::string_view fileName);

    SetElementEnum loadSetElementEnum(std::string_view fileName);
    void saveSetElementEnum(const SetElementEnum & element, std::string_view fileName);
}   // namespace Helper