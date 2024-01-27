#pragma once

#include <variant>

#include "FP_Common.hxx"

namespace FileParse
{
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

    template<typename T, typename NodeAdapter, typename... Ts>
    inline NodeAdapter & operator<<(NodeAdapter & node, const std::variant<T, Ts...> & v)
    {
        std::visit([&](auto && arg) { node << arg; }, v);
        return node;
    }
}   // namespace FileParse