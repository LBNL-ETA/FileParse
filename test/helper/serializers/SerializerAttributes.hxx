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

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::AttributesTest & element)
    {
        FileParse::saveAttribute(node, "Name", element.name);
        FileParse::saveAttribute(node, "Age", element.age);
        FileParse::saveAttribute(node, "Height", element.height);
        FileParse::saveAttribute<NodeAdapter, Helper::Day>(node, "Day", element.day, Helper::toDayString);

        return node;
    }
}   // namespace Helper