#pragma once

#include <functional>

#include "StringConversion.hxx"
#include "Common.hxx"

namespace FileParse
{
    template<typename NodeAdapter, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, NodeAdapter> operator<<(NodeAdapter node,
                                                                                  const Child<const MapType> & value)
    {
        if(value.nodeNames.empty() || value.data.empty())
            return node;

        auto secondToLastNode{insertAllChilds(node, value.nodeNames)};

        secondToLastNode << value.data;

        return node;
    }

    template<typename NodeAdapter, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, NodeAdapter> operator>>(NodeAdapter node,
                                                                                  Child<const MapType> & value)
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

    template<typename NodeAdapter, typename EnumType, typename ValueType>
    inline std::enable_if_t<is_valid_map<std::map<EnumType, ValueType>>::value
                              || is_valid_map<std::unordered_map<EnumType, ValueType>>::value,
                            NodeAdapter>
      serializeEnumMap(NodeAdapter node,
                       const std::map<EnumType, ValueType> & map,
                       std::function<std::string(EnumType)> converter)
    {
        if(map.empty())
            return node;

        std::map<std::string, ValueType> mapToSerialize;
        for(const auto & [enumKey, mapValue] : map)
        {
            mapToSerialize[converter(enumKey)] = mapValue;
        }

        node << mapToSerialize;

        return node;
    }

    template<typename NodeAdapter, typename EnumType, typename ValueType>
    inline std::enable_if_t<is_valid_map<std::map<EnumType, ValueType>>::value
                              || is_valid_map<std::unordered_map<EnumType, ValueType>>::value,
                            NodeAdapter>
      deserializeEnumMap(const NodeAdapter & node,
                         std::map<EnumType, ValueType> & map,
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
                map[converter(key)] = from_string_helper<ValueType>(text);
            }
        }

        return node;
    }

}   // namespace FileParse