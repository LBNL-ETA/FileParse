#pragma once

#include <map>
#include <functional>

#include "Common.hxx"

namespace FileParse
{
    template<typename NodeAdapter, typename Value>
    inline NodeAdapter operator<<(NodeAdapter node, const Child<const std::map<std::string, Value>> & value)
    {
        if(value.nodeNames.empty() || value.data.empty())
            return node;

        auto secondToLastNode{insertAllChilds(node, value.nodeNames)};

        secondToLastNode << value.data;

        return node;
    }

    template<typename NodeAdapter, typename Value>
    inline NodeAdapter operator>>(NodeAdapter node, Child<const std::map<std::string, Value>> & value)
    {
        if(value.nodeNames.empty())
        {
            return node;
        }

        NodeAdapter parentNode = node;
        for(const auto & nodeName : value.nodeNames)
        {
            parentNode = parentNode.getChildByName(nodeName);
            if(!parentNode.isValid())
            {
                return node;
            }
        }

        parentNode >> value.data;

        return node;
    }

    template<typename NodeAdapter, typename EnumType>
    NodeAdapter serializeEnumMap(NodeAdapter node,
                                 const std::map<EnumType, std::string> & map,
                                 std::function<std::string(EnumType)> converter)
    {
        if(map.empty())
            return node;

        std::map<std::string, std::string> mapToSerialize;
        for(const auto & [enumKey, mapValue] : map)
        {
            mapToSerialize[converter(enumKey)] = mapValue;
        }

        node << mapToSerialize;

        return node;
    }

    template<typename NodeAdapter, typename EnumType>
    NodeAdapter deserializeEnumMap(const NodeAdapter & node,
                                   std::map<EnumType, std::string> & map,
                                   std::function<EnumType(std::string_view)> converter)
    {
        int totalNodes = node.nChildNode();
        for(int i = 0; i < totalNodes; ++i)
        {
            NodeAdapter childNode = node.getChildNode(i);
            if(!childNode.isEmpty())
            {
                const auto text = childNode.getText();
                const auto key = childNode.getCurrentTag();
                map[converter(key)] = text;
            }
        }

        return node;
    }

}   // namespace FileParse