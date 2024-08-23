/// File: Variant.hxx
/// @brief Provides functionality to serialize and deserialize std::variant and
///        std::optional<std::variant> types in the FileParse namespace.

#pragma once

#include <variant>

#include "Common.hxx"

namespace FileParse
{
    /// Serializes a std::variant into a node.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam Ts Variadic template representing the types held by the variant.
    /// @param node The node to serialize the variant into.
    /// @param nodeNames A vector of strings representing the names for each type in the variant.
    /// @param variantValue The std::variant value to be serialized.
    template<typename NodeAdapter, typename... Ts>
    void serializeVariant(NodeAdapter & node,
                          const std::vector<std::string> & nodeNames,
                          const std::variant<Ts...> & variantValue)
    {
        if(variantValue.index() < nodeNames.size())
        {
            std::visit(
              [&node, &nodeNames, &variantValue](const auto & val) {
                  node << Child{nodeNames[variantValue.index()], val};
              },
              variantValue);
        }
    }

    /// Deserializes a node into a std::variant.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam Ts Variadic template representing the types held by the variant.
    /// @param node The node to deserialize the variant from.
    /// @param nodeNames A vector of strings representing the names for each type in the variant.
    /// @param variantValue The std::variant value to store the deserialized data.
    template<typename NodeAdapter, typename... Ts>
    void deserializeVariant(const NodeAdapter & node,
                            const std::vector<std::string> & nodeNames,
                            std::variant<Ts...> & variantValue)
    {
        bool deserialized = false;
        size_t index{0u};

        auto try_deserialize_variant = [&](auto dummyType) {
            using Type = decltype(dummyType);
            if(!deserialized && index < nodeNames.size())
            {
                Type value;
                if(node.nChildNode(nodeNames[index]) > 0)
                {
                    node >> Child{nodeNames[index], value};
                    variantValue = value;
                    deserialized = true;
                }
            }
            index++;
        };

        (try_deserialize_variant(Ts{}), ...);
    }

    /// Serializes a std::optional<std::variant> into a node.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam Ts Variadic template representing the types held by the variant.
    /// @param node The node to serialize the optional variant into.
    /// @param nodeNames A vector of strings representing the names for each type in the variant.
    /// @param optionalVariantValue The std::optional<std::variant> value to be serialized.
    template<typename NodeAdapter, typename... Ts>
    void serializeOptionalVariant(NodeAdapter & node,
                                  const std::vector<std::string> & nodeNames,
                                  const std::optional<std::variant<Ts...>> & optionalVariantValue)
    {
        if(optionalVariantValue.has_value())
        {
            serializeVariant(node, nodeNames, *optionalVariantValue);
        }
        // If optional is empty, no serialization is done.
    }

    /// Deserializes a node into a std::optional<std::variant>.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam Ts Variadic template representing the types held by the variant.
    /// @param node The node to deserialize the optional variant from.
    /// @param nodeNames A vector of strings representing the names for each type in the variant.
    /// @param optionalVariantValue The std::optional<std::variant> value to store the deserialized
    /// data.
    template<typename NodeAdapter, typename... Ts>
    void deserializeOptionalVariant(const NodeAdapter & node,
                                    const std::vector<std::string> & nodeNames,
                                    std::optional<std::variant<Ts...>> & optionalVariantValue)
    {
        std::variant<Ts...> variantValue;
        bool successfullyDeserialized = false;
        size_t index{0u};

        auto try_deserialize_variant = [&](auto dummyType) {
            using Type = decltype(dummyType);
            if(!successfullyDeserialized && index < nodeNames.size())
            {
                Type value;
                if(node.nChildNode(nodeNames[index]) > 0)
                {
                    node >> Child{nodeNames[index], value};
                    variantValue = value;
                    successfullyDeserialized = true;
                }
            }
            index++;
        };

        (try_deserialize_variant(Ts{}), ...);

        if(successfullyDeserialized)
        {
            optionalVariantValue = variantValue;
        }
        else
        {
            optionalVariantValue = std::nullopt;
        }
    }

    /// Overloaded operator<< for serializing a std::variant.
    /// @tparam T The first type in the variant.
    /// @tparam Ts Variadic template representing the remaining types held by the variant.
    /// @param node The node to serialize the variant into.
    /// @param v The std::variant value to be serialized.
    /// @return Reference to the updated node.
    template<typename T, typename NodeAdapter, typename... Ts>
    inline NodeAdapter & operator<<(NodeAdapter & node, const std::variant<T, Ts...> & v)
    {
        std::visit([&](auto && arg) { node << arg; }, v);
        return node;
    }
}   // namespace FileParse