#pragma once

#include <set>
#include <functional>
#include <stdexcept>

#include "Common.hxx"

namespace FileParse {
    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<const std::set<T>> &value) {
        if (value.nodeNames.empty() || value.data.empty())
            return node;

        auto secondToLastNode{insertAllButLastChild(node, value.nodeNames)};

        for (const auto &item: value.data) {
            NodeAdapter lastNode = secondToLastNode.addChild(value.nodeNames.back());
            lastNode << item;
        }

        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter &node, const Child<std::set<T>> &vec) {
        vec.data.clear();

        if (!node.hasChildNode(vec.nodeNames.front()))
            return node;

        if (auto currentNode{findParentOfLastTag(node, vec.nodeNames)}; currentNode.has_value()) {
            for (int i = 0; i < currentNode.value().nChildNode(vec.nodeNames.back()); ++i) {
                NodeAdapter activeNode = currentNode.value().getChildNode(vec.nodeNames.back(), i);
                T item;
                activeNode >> item;
                vec.data.insert(item);
            }
        }

        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter &node, const Child<std::optional<std::set<T>>> &opt_vec) {


        if (auto childNode{findParentOfLastTag(node, opt_vec.nodeNames)}; !childNode.has_value() ||
                                                                          childNode.value().nChildNode(
                                                                                  opt_vec.nodeNames.back()) == 0) {
            return node;
        }

        opt_vec.data = std::set<T>();
        node >> Child{opt_vec.nodeNames, opt_vec.data.value()};

        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<const std::optional<std::set<T>>> &opt_vec) {
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
    NodeAdapter serializeEnumSet(NodeAdapter node,
                                 const std::vector<std::string> &tags,
                                 const std::set<EnumType> &vec,
                                 std::function<std::string(EnumType)> converter) {
        if (tags.empty()) {
            throw std::invalid_argument("Tag set is empty");
        }

        auto currentNode{insertAllButLastChild(node, tags)};

        for (const auto &value: vec) {
            NodeAdapter childNode = currentNode.addChild(tags.back());
            childNode.addText(converter(value));
        }

        return node;
    }


    template<typename NodeAdapter, typename EnumType>
    NodeAdapter deserializeEnumSet(const NodeAdapter &node,
                                   const std::vector<std::string> &tags,
                                   std::set<EnumType> &vec,
                                   std::function<EnumType(std::string_view)> converter) {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        vec.clear();

        if (tags.empty()) {
            throw std::invalid_argument("Tag set is empty");
        }

        if (auto currentNode{findParentOfLastTag(node, tags)}; currentNode.has_value()) {
            int totalNodes = currentNode.value().nChildNode(tags.back());
            for (int i = 0; i < totalNodes; ++i) {
                NodeAdapter childNode = currentNode.value().getChildNode(tags.back(), i);
                if (!childNode.isEmpty()) {
                    const auto text = childNode.getText();
                    vec.insert(converter(text));
                }
            }
        }

        return node;
    }
}   // namespace FileParse