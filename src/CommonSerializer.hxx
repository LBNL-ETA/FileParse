#pragma once

#include <vector>
#include <string>
#include <optional>
#include <variant>


class XMLNodeAdapter;

inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const std::string & text)
{
    xmlNode.addText(text);
    return xmlNode;
}

inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, std::string & text)
{
    text = xmlNode.getText();
    return xmlNode;
}

inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, bool value)
{
    xmlNode.addText(value ? "true" : "false");
    return xmlNode;
}

inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, bool & value)
{
    const auto text{xmlNode.getText()};
    value = (text == "true");
    return xmlNode;
}

inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, int value)
{
    xmlNode.addText(std::to_string(value));
    return xmlNode;
}

inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, int & value)
{
    const auto text{xmlNode.getText()};
    value = std::stoi(text);
    return xmlNode;
}

inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, double value)
{
    xmlNode.addText(std::to_string(value));
    return xmlNode;
}

inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, double & value)
{
    const auto text{xmlNode.getText()};
    value = std::stod(text);
    return xmlNode;
}

inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, size_t value)
{
    xmlNode.addText(std::to_string(value));
    return xmlNode;
}

inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, size_t & value)
{
    const auto text{xmlNode.getText()};
    value = std::stoul(text);
    return xmlNode;
}

template<typename T>
inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const std::optional<T> & opt)
{
    if(opt.has_value())
    {
        xmlNode << opt.value();
    }
    return xmlNode;
}

template<typename T>
inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, std::optional<T> & opt)
{
    if(!xmlNode.isEmpty())
    {
        T value;
        xmlNode >> value;
        opt = value;
    }
    return xmlNode;
}

template<typename T>
std::optional<T> TryOptionalReadFromCurrentNode(const XMLNodeAdapter & xmlNode, std::string nodeName)
{
    std::optional<T> result;
    if(xmlNode.isCurrentTag(nodeName))
    {
        T value;
        xmlNode >> value;
        result = value;
    }
    return result;
}

template<typename T, typename... Ts>
inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const std::variant<T, Ts...> & v)
{
    std::visit([&](auto && arg) { xmlNode << arg; }, v);
    return xmlNode;
}

template<typename T, typename... Ts>
inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, std::variant<T, Ts...> & v)
{
    std::visit([&](auto && arg) { xmlNode >> arg; }, v);
    return xmlNode;
}

template<typename T>
struct Child
{
    std::vector<std::string> nodeNames;
    T & data;
    size_t index{0u};

    Child(const std::string & nodeName, T & data, size_t index = 0u) :
        nodeNames({nodeName}),
        data(data),
        index(index)
    {}

    Child(std::initializer_list<std::string> nodeNames, T & data, size_t index = 0u) :
        nodeNames(nodeNames),
        data(data),
        index(index)
    {}
};

template<typename T>
inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Child<T> & child)
{
    auto childNode = xmlNode;
    for(const auto & nodeName : child.nodeNames)
    {
        childNode = childNode.addChild(nodeName);
    }
    childNode << child.data;
    return xmlNode;
}

template<typename T>
inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, const Child<T> & child)
{
    for(const auto & nodeName : child.nodeNames)
    {
        auto childNode = xmlNode.getChildNode(nodeName);
        if(!childNode.isEmpty())
        {
            childNode >> child.data;
        }
    }
    return xmlNode;
}

template<typename T>
inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Child<const std::optional<T>> & child)
{
    if(child.data.has_value())
    {
        for(const auto & nodeName : child.nodeNames)
        {
            xmlNode = xmlNode.addChild(nodeName);
        }
        xmlNode << child.data.value();
    }
    return xmlNode;
}

template<typename T>
inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Child<const std::vector<T>> & vec)
{
    for(const auto & item : vec.data)
    {
        XMLNodeAdapter currentNode = xmlNode;
        for(const auto & nodeName : vec.nodeNames)
        {
            currentNode = currentNode.addChild(nodeName);
        }
        currentNode << item;
    }
    return xmlNode;
}

template<typename T>
inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, const Child<std::vector<T>> & vec)
{
    vec.data.clear();
    for(int i = 0; i < xmlNode.nChildNode(vec.nodeNames.front()); ++i)
    {
        XMLNodeAdapter currentNode = xmlNode;
        for(const auto & nodeName : vec.nodeNames)
        {
            currentNode = currentNode.getChildNode(nodeName, i);
        }
        T item;
        currentNode >> item;
        vec.data.push_back(item);
    }
    return xmlNode;
}

template<typename T>
inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, const Child<std::optional<std::vector<T>>> & opt_vec)
{
    if(xmlNode.nChildNode(opt_vec.nodeNames.front()) == 0)
    {
        return xmlNode;
    }

    XMLNodeAdapter childNode = xmlNode;
    for(size_t i = 0u; i < opt_vec.nodeNames.size() - 1u; ++i)
    {
        childNode = childNode.getChildNode(opt_vec.nodeNames[i]);
        if(childNode.isEmpty() || childNode.nChildNode() == 0)
        {
            return xmlNode;
        }
    }

    opt_vec.data = std::vector<T>();
    for(int i = 0; i < childNode.nChildNode(opt_vec.nodeNames.back()); ++i)
    {
        auto tableNode = childNode.getChildNode(opt_vec.nodeNames.back(), i);
        T item;
        tableNode >> item;
        opt_vec.data->push_back(item);
    }
    return xmlNode;
}

template<typename T>
inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Child<const std::optional<std::vector<T>>> & opt_vec)
{
    if(opt_vec.data.has_value())
    {
        XMLNodeAdapter currentNode = xmlNode;
        for(size_t i = 0u; i < opt_vec.nodeNames.size() - 1; ++i)
        {
            currentNode = currentNode.addChild(opt_vec.nodeNames[i]);
        }

        for(const auto & item : opt_vec.data.value())
        {
            auto tableNode = currentNode.addChild(opt_vec.nodeNames.back());
            tableNode << item;
        }
    }

    return xmlNode;
}
