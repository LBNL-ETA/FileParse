#pragma once

#include "fileParse/Attributes.hxx"
#include "fileParse/Base.hxx"

#include "test/helper/structures/Attributes.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          Helper::AttributesTest & element)
    {
        FileParse::loadAttribute(node, "Name", element.name);
        FileParse::loadAttribute(node, "Age", element.age);
        FileParse::loadAttribute(node, "Height", element.height);
        FileParse::loadAttribute<NodeAdapter, Helper::Day>(node, "Day", element.day, Helper::toDay);
        FileParse::loadAttribute(node, "OptionalAge", element.optional_age);
        FileParse::loadAttribute(node, "Nickname", element.nickname);
        FileParse::loadAttribute<NodeAdapter, Helper::Color>(node, "Color", element.color, Helper::toColor);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::AttributesTest & element)
    {
        FileParse::saveAttribute(node, "Name", element.name);
        FileParse::saveAttribute(node, "Age", element.age);
        FileParse::saveAttribute(node, "Height", element.height);
        FileParse::saveAttribute<NodeAdapter, Helper::Day>(node, "Day", element.day, Helper::toDayString);
        FileParse::saveAttribute(node, "OptionalAge", element.optional_age);
        FileParse::saveAttribute(node, "Nickname", element.nickname);
        FileParse::saveAttribute<NodeAdapter, Helper::Color>(node, "Color", element.color, Helper::toColorString);

        return node;
    }
}   // namespace Helper