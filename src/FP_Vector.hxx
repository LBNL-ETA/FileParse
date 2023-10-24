#pragma once

#include <vector>
#include <optional>
#include <functional>
#include <stdexcept>

#include "FP_Common.hxx"

namespace FileParse {
    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<const std::vector<T>> &vec) {
        if (vec.nodeNames.empty() || vec.data.empty())
            return node;

        auto secondToLastNode{insertAllButLastChild(node, vec.nodeNames)};

        const auto &lastNodeName = vec.nodeNames.back();

        for (const auto &item: vec.data) {
            NodeAdapter lastNode = secondToLastNode.addChild(lastNodeName);
            lastNode << item;
        }

        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter &node, const Child<std::vector<T>> &vec) {
        vec.data.clear();

        if (!node.hasChildNode(vec.nodeNames.front()))
            return node;

        if (auto currentNode{findParentOfLastTag(node, vec.nodeNames)};currentNode.has_value()) {
            int childCount = currentNode.value().nChildNode(vec.nodeNames.back());
            vec.data.reserve(childCount);
            for (int i = 0; i < childCount; ++i) {
                NodeAdapter activeNode = currentNode.value().getChildNode(vec.nodeNames.back(), i);
                T item;
                activeNode >> item;
                vec.data.push_back(item);
            }
        }

        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter &node, const Child<std::optional<std::vector<T>>> &opt_vec) {

        if (auto childNode{findParentOfLastTag(node, opt_vec.nodeNames)};!childNode.has_value() ||
                                                                         childNode.value().nChildNode(
                                                                                 opt_vec.nodeNames.back()) == 0) {
            return node;
        }

        opt_vec.data = std::vector<T>();
        node >> Child{opt_vec.nodeNames, opt_vec.data.value()};

        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<const std::optional<std::vector<T>>> &opt_vec) {
        if (opt_vec.data.has_value()) {
            auto currentNode{insertAllButLastChild(node, opt_vec.nodeNames)};

            for (const auto &item: opt_vec.data.value()) {
                auto tableNode = currentNode.addChild(opt_vec.nodeNames.back());
                tableNode << item;
            }
        }

        return node;
    }

    template<typename NodeAdapter, typename EnumType>
    NodeAdapter serializeEnumVector(NodeAdapter node,
                                    const std::vector<std::string> &tags,
                                    const std::vector<EnumType> &vec,
                                    std::function<std::string(EnumType)> converter) {
        if (tags.empty()) {
            throw std::invalid_argument("Tag vector is empty");
        }

        auto currentNode{insertAllButLastChild(node, tags)};

        for (const auto &value: vec) {
            NodeAdapter childNode = currentNode.addChild(tags.back());
            childNode.addText(converter(value));
        }

        return node;
    }


    template<typename NodeAdapter, typename EnumType>
    NodeAdapter deserializeEnumVector(const NodeAdapter &node,
                                      const std::vector<std::string> &tags,
                                      std::vector<EnumType> &vec,
                                      std::function<EnumType(std::string_view)> converter) {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        vec.clear();

        if (tags.empty()) {
            throw std::invalid_argument("Tag vector is empty");
        }

        if (auto currentNode{findParentOfLastTag(node, tags)};currentNode.has_value()) {
            int totalNodes = currentNode.value().nChildNode(tags.back());
            for (int i = 0; i < totalNodes; ++i) {
                NodeAdapter childNode = currentNode.value().getChildNode(tags.back(), i);
                if (!childNode.isEmpty()) {
                    const auto text = childNode.getText();
                    vec.emplace_back(converter(text));
                }
            }
        }

        return node;
    }

}   // namespace FileParse