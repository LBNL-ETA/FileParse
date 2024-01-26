#pragma once

#include <string>
#include <optional>
#include <map>
#include <unordered_map>

namespace FileParse
{
    template<typename NodeAdapter>
    NodeAdapter insertAllChilds(NodeAdapter node, const std::vector<std::string> & nodeNames)
    {
        NodeAdapter lastNode = node;
        for(const auto & nodeName : nodeNames)
        {
            lastNode = lastNode.addChild(nodeName);
        }

        return lastNode;
    }

    template<typename NodeAdapter>
    NodeAdapter insertAllButLastChild(NodeAdapter node, const std::vector<std::string> & nodeNames)
    {
        NodeAdapter secondToLastNode = node;
        for(size_t i = 0; i < nodeNames.size() - 1; ++i)
        {
            secondToLastNode = secondToLastNode.addChild(nodeNames[i]);
        }

        return secondToLastNode;
    }

    template<typename NodeAdapter>
    std::optional<NodeAdapter> findLastTag(NodeAdapter node, const std::vector<std::string> & nodeNames)
    {
        NodeAdapter currentNode = node;

        for (const auto& nodeName : nodeNames) {
            currentNode = currentNode.getChildNode(nodeName);
            if (currentNode.isEmpty()) {
                return std::nullopt;
            }
        }

        return currentNode;
    }

    template<typename NodeAdapter>
    std::optional<NodeAdapter> findParentOfLastTag(NodeAdapter node, const std::vector<std::string> & nodeNames)
    {
        NodeAdapter currentNode = node;

        for(size_t i = 0; i < nodeNames.size() - 1; ++i)
        {
            currentNode = currentNode.getChildNode(nodeNames[i], 0);
            if(currentNode.isEmpty())
            {
                return std::nullopt;
            }
        }

        return currentNode;
    }

    template<typename NodeAdapter>
    int numberOfChilds(NodeAdapter node, const std::vector<std::string> & nodeNames)
    {
        auto currentNode{findParentOfLastTag(node, nodeNames)};

        if(!currentNode.has_value())
        {
            return 0;
        }

        return currentNode.value().nChilds(nodeNames.size());
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const std::string & text)
    {
        node.addText(text);
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, std::string & text)
    {
        text = node.getText();
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, bool value)
    {
        node.addText(value ? "true" : "false");
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, bool & value)
    {
        const auto text{node.getText()};
        value = (text == "true");
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, int value)
    {
        node.addText(std::to_string(value));
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, int & value)
    {
        const auto text{node.getText()};
        value = std::stoi(text);
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, double value)
    {
        node.addText(std::to_string(value));
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, double & value)
    {
        const auto text{node.getText()};
        value = std::stod(text);
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, size_t value)
    {
        node.addText(std::to_string(value));
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, size_t & value)
    {
        const auto text{node.getText()};
        value = std::stoul(text);
        return node;
    }

    template<template<typename...> class Template, typename T>
    struct is_instance_of : std::false_type
    {};

    template<template<typename...> class Template, typename... Args>
    struct is_instance_of<Template, Template<Args...>> : std::true_type
    {};

    template<typename T>
    struct is_valid_map : std::false_type
    {};

    template<typename K, typename V>
    struct is_valid_map<std::map<K, V>> : std::true_type
    {};

    template<typename K, typename V>
    struct is_valid_map<std::unordered_map<K, V>> : std::true_type
    {};

    template<typename NodeAdapter, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, NodeAdapter> operator<<(NodeAdapter node, const MapType & map)
    {
        for(const auto & [key, val] : map)
        {
            NodeAdapter lastNode = node.addChild(key);
            lastNode << val;
        }

        return node;
    }

    template<typename NodeAdapter, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, NodeAdapter> operator>>(NodeAdapter node, MapType & map)
    {
        for(int i = 0; i < node.nChildNode(); ++i)
        {
            auto childNode = node.getChildNode(i);
            std::string key = childNode.getCurrentTag();

            typename MapType::mapped_type val;
            childNode >> val;
            map[key] = val;
        }

        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const std::optional<T> & opt)
    {
        if(opt.has_value())
        {
            node << opt.value();
        }
        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter & node, std::optional<T> & opt)
    {
        if(!node.isEmpty())
        {
            T value;
            node >> value;
            opt = value;
        }
        return node;
    }
}   // namespace FileParse