/// File: Map.hxx
/// @brief: Provides serialization and deserialization functionalities for maps and enum maps
///         in the FileParse namespace, including utility functions for handling child nodes
///         and converting enum types to and from string representations.

#pragma once

#include <functional>

#include "Common.hxx"
#include "StringConversion.hxx"

namespace FileParse
{
    /// Serializes a child node with its associated map data.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam MapType The type of the map to be serialized.
    /// @param node The node to serialize the map into.
    /// @param value The Child object containing the map and node hierarchy information.
    /// @return Reference to the updated node.
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

    /// Deserializes a child node into its associated map data.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam MapType The type of the map to be deserialized.
    /// @param node The node to deserialize the map from.
    /// @param value The Child object that will hold the deserialized map and provides node
    /// hierarchy information.
    /// @return Const reference to the node.
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

    /// Serializes a map as child nodes of a given node.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam MapType The type of the map to be serialized.
    /// @param node The node to serialize the map into.
    /// @param childNodeName The name of the child nodes to create for each map entry.
    /// @param map The map to be serialized.
    /// @return Reference to the updated node.
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

    /// Deserializes child nodes of a given node into a map.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam MapType The type of the map to be deserialized.
    /// @param node The node to deserialize the map from.
    /// @param childNodeName The name of the child nodes to read for each map entry.
    /// @param map The map to store the deserialized values.
    /// @return Const reference to the node.
    template<typename NodeAdapter, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, const NodeAdapter &>
      deserializeMapAsChilds(const NodeAdapter & node,
                             std::string_view childNodeName,
                             MapType & map)
    {
        const auto childNodes{node.getChildNodesByName(childNodeName.data())};
        for(const auto & childNode : childNodes)
        {
            typename MapType::key_type key;
            typename MapType::mapped_type value;

            childNode >> key;
            childNode >> value;

            map[key] = value;
        }

        return node;
    }

    /// Serializes a map with enum keys, converting the enums to strings.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam EnumType The enumeration type of the map's keys.
    /// @tparam ValueType The type of the map's values.
    /// @tparam MapType The type of the map to be serialized.
    /// @param node The node to serialize the map into.
    /// @param map The map to be serialized.
    /// @param converter A function that converts the enum keys to strings.
    /// @return Reference to the updated node.
    template<typename NodeAdapter, typename EnumType, typename ValueType, typename MapType>
    inline typename std::enable_if_t<is_valid_map<MapType>::value, NodeAdapter &> serializeEnumMap(
      NodeAdapter & node, const MapType & map, std::function<std::string(EnumType)> converter)
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

    /// Deserializes a map with enum keys, converting the strings back to enums.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam EnumType The enumeration type of the map's keys.
    /// @tparam ValueType The type of the map's values.
    /// @tparam MapType The type of the map to be deserialized.
    /// @param node The node to deserialize the map from.
    /// @param map The map to store the deserialized values.
    /// @param converter A function that converts strings to enum keys.
    /// @return Const reference to the node.
    template<typename NodeAdapter, typename EnumType, typename ValueType, typename MapType>
    inline std::enable_if_t<is_valid_map<MapType>::value, const NodeAdapter &> deserializeEnumMap(
      const NodeAdapter & node, MapType & map, std::function<EnumType(std::string_view)> converter)
    {
        const auto & childNodes{node.getChildNodes()};
        for(const auto & childNode : childNodes)
        {
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