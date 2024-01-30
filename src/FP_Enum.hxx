#pragma once

#include <string>
#include <functional>
#include <optional>

namespace FileParse
{
    template<typename NodeAdapter, typename EnumType>
    NodeAdapter & serializeEnum(NodeAdapter & node,
                                const EnumType & e,
                                std::function<std::string(EnumType)> converter)
    {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        node.addText(converter(e));

        return node;
    }

    template<typename NodeAdapter, typename EnumType>
    const NodeAdapter & deserializeEnum(const NodeAdapter & node,
                                        EnumType & e,
                                        std::function<EnumType(std::string_view)> converter)
    {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        e = converter(node.getText());

        return node;
    }
}   // namespace FileParse