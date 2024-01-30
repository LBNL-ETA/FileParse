#pragma once

#include <functional>

#include "FP_Common.hxx"
#include "FP_StringConversion.hxx"

namespace FileParse
{
    template<typename NodeAdapter, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, NodeAdapter &>
      operator<<(NodeAdapter & node, const Child<const MapType> & value)
    {
        if(value.nodeNames.empty() || value.data.empty())
            return node;

        auto secondToLastNode{insertAllChilds(node, value.nodeNames)};

        secondToLastNode << value.data;

        return node;
    }

    template<typename NodeAdapter, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, const NodeAdapter &>
      operator>>(const NodeAdapter & node, Child<const MapType> & value)
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

    template<typename NodeAdapter, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, NodeAdapter &>
      serializeMapAsChilds(NodeAdapter & node, std::string_view childNodeName, const MapType & map)
    {
        if(map.empty())
            return node;

        for(const auto & [enumKey, mapValue] : map)
        {
            auto childNode{node.addChild(childNodeName)};
            childNode << enumKey;
            childNode << mapValue;
        }

        return node;
    }

    template<typename NodeAdapter, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, const NodeAdapter &>
      deserializeMapAsChilds(const NodeAdapter & node,
                             std::string_view childNodeName,
                             MapType & map)
    {
        int childCount = node.nChildNode(childNodeName.data());
        for(int i = 0; i < childCount; ++i)
        {
            auto childNode = node.getChildNode(childNodeName.data(), i);

            // Assuming key and value types have default constructors and
            // have the appropriate `>>` operators overloaded.
            typename MapType::key_type key;
            typename MapType::mapped_type value;

            childNode >> key;
            childNode >> value;

            map[key] = value;
        }

        return node;
    }

    template<typename NodeAdapter, typename EnumType, typename ValueType>
    inline std::enable_if_t<is_valid_map<std::map<EnumType, ValueType>>::value
                              || is_valid_map<std::unordered_map<EnumType, ValueType>>::value,
                            NodeAdapter &>
      serializeEnumMap(NodeAdapter & node,
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


    template<typename NodeAdapter, typename EnumType, typename ValueType, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, const NodeAdapter &> deserializeEnumMap(
      const NodeAdapter & node, MapType & map, std::function<EnumType(std::string_view)> converter)
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