#pragma once

#include "fileParse/Attributes.hxx"
#include "fileParse/Common.hxx"

#include "test/helper/structures/Attributes.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline const NodeAdapter & operator>>(const NodeAdapter & node,
                                          Helper::AttributesTest & element)
    {
        FileParse::assignIfHasValue(node.getAttribute("Name"), element.name);

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter & operator<<(NodeAdapter & node, const Helper::AttributesTest & element)
    {
        node.addAttribute("Name", element.name);

        return node;
    }
}   // namespace Helper