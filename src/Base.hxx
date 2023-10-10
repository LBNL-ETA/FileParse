#pragma once

#include <string>

namespace FileParse
{
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
}   // namespace FileParse