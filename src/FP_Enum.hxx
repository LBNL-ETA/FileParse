#pragma once

#include <string>
#include <functional>
#include <optional>

namespace FileParse {
    template<typename NodeAdapter, typename EnumType>
    NodeAdapter serializeEnum(NodeAdapter node,
                              const std::string &tag,
                              const EnumType &e,
                              std::function<std::string(EnumType)> converter) {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        NodeAdapter childNode = node.addChild(tag);
        std::string value = converter(e);
        childNode.addText(value);

        return node;
    }

    template<typename NodeAdapter, typename EnumType>
    NodeAdapter deserializeEnum(const NodeAdapter &node,
                                const std::string &tag,
                                EnumType &e,
                                std::function<EnumType(std::string_view)> converter) {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");


        if (auto childNode{node.getChildNode(tag, 0)}; !childNode.isEmpty()) {
            const auto text = childNode.getText();
            e = converter(text);
        }

        return node;
    }

    template<typename NodeAdapter, typename EnumType>
    NodeAdapter serializeEnum(NodeAdapter node,
                              const std::string &tag,
                              const std::optional<EnumType> &opt,
                              std::function<std::string(EnumType)> converter) {
        if (opt.has_value())
            serializeEnum(node, tag, opt.value(), converter);

        return node;
    }

    template<typename NodeAdapter, typename EnumType>
    NodeAdapter deserializeEnum(const NodeAdapter &node,
                                const std::string &tag,
                                std::optional<EnumType> &e_opt,
                                std::function<EnumType(std::string_view)> converter) {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        if (auto childNode = node.getChildNode(tag, 0); !childNode.isEmpty()) {
            const auto text = childNode.getText();
            e_opt = converter(text);
        }

        return node;
    }
}