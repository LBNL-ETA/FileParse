#pragma once

#include "Common.hxx"
#include "Enum.hxx"

#include "test/helper/structures/StructureEnum.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & xmlNode, Helper::EnumElement & element)
    {
        FileParse::deserializeEnum<NodeAdapter, Helper::Day>(xmlNode, "Day", element.day, Helper::toDay);
        FileParse::deserializeEnum<NodeAdapter, Helper::Color>(xmlNode, "Color", element.color, Helper::toColor);

        return xmlNode;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter xmlNode, const Helper::EnumElement & element)
    {
        FileParse::serializeEnum<NodeAdapter, Helper::Day>(xmlNode, "Day", element.day, Helper::toDayString);
        FileParse::serializeEnum<NodeAdapter, Helper::Color>(xmlNode, "Color", element.color, Helper::toColorString);

        return xmlNode;
    }

    EnumElement loadEnumElement(std::string_view fileName);
    void saveEnumElement(const EnumElement& element, std::string_view fileName);
}   // namespace Helper