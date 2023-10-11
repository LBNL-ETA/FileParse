#pragma once

#include <string>
#include <vector>

#include "Base.hxx"

namespace FileParse
{
    template<typename T>
    struct Child
    {
        std::vector<std::string> nodeNames;
        T & data;
        size_t index{0u};

        Child(const std::string & nodeName, T & data, size_t index = 0u) :
            nodeNames({nodeName}), data(data), index(index)
        {}

        Child(std::initializer_list<std::string> nodeNames, T & data, size_t index = 0u) :
            nodeNames(nodeNames), data(data), index(index)
        {}

        Child(const std::vector<std::string> & nodeNames, T & data, size_t index = 0u) :
            nodeNames(nodeNames), data(data), index(index)
        {}
    };

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<T> & child)
    {
        auto childNode = node;
        for(const auto & nodeName : child.nodeNames)
        {
            childNode = childNode.addChild(nodeName);
        }
        childNode << child.data;
        return node;
    }

    template<typename NodeAdapter, typename T>
    inline NodeAdapter operator>>(const NodeAdapter & node, const Child<T> & child)
    {
        for(const auto & nodeName : child.nodeNames)
        {
            auto childNode = node.getChildNode(nodeName);
            if(!childNode.isEmpty())
            {
                childNode >> child.data;
            }
        }
        return node;
    }
}   // namespace FileParse