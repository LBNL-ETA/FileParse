/// File: FP_Enum.hxx
/// @brief Provides templates for serializing and deserializing enumeration types
///        using NodeAdapter in the FileParse namespace. It includes functionality
///        to convert enumeration types to and from their string representations
///        using custom converter functions.

#pragma once

#include <string>
#include <functional>
#include <optional>

namespace FileParse
{
    /// Serializes an enumeration value to a node using a custom converter function.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam EnumType The enumeration type to be serialized.
    /// @param node The node to serialize the enumeration value into.
    /// @param e The enumeration value to be serialized.
    /// @param converter A function that converts the enumeration value to a string.
    /// @return Reference to the updated node.
    /// @note This function requires EnumType to be an enumeration type.
    template<typename NodeAdapter, typename EnumType>
    NodeAdapter & serializeEnum(NodeAdapter & node,
                                const EnumType & e,
                                std::function<std::string(EnumType)> converter)
    {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        node.addText(converter(e));

        return node;
    }

    /// Deserializes an enumeration value from a node using a custom converter function.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam EnumType The enumeration type to be deserialized.
    /// @param node The node to deserialize the enumeration value from.
    /// @param e Reference to the enumeration variable where the deserialized value will be stored.
    /// @param converter A function that converts a string to an enumeration value.
    /// @return Const reference to the node.
    /// @note This function requires EnumType to be an enumeration type.
    template<typename NodeAdapter, typename EnumType>
    const NodeAdapter & deserializeEnum(const NodeAdapter & node,
                                        EnumType & e,
                                        std::function<EnumType(std::string_view)> converter)
    {
        static_assert(std::is_enum_v<EnumType>, "Provided type is not an enum!");

        e = converter(node.getText());

        return node;
    }
}   // namespace FileParse