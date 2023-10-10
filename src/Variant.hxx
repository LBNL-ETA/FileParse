#pragma once

#include <variant>

#include "Common.hxx"

namespace FileParse
{
    template<typename NodeAdapter, typename... Ts>
    void serializeVariant(NodeAdapter & node,
                          const std::vector<std::string> & nodeNames,
                          const std::variant<Ts...> & variantValue)
    {
        if(variantValue.index() < nodeNames.size())
        {
            std::visit([&](const auto & val) { node << Child{nodeNames[variantValue.index()], val}; }, variantValue);
        }
    }

    template<typename NodeAdapter, typename... Ts>
    void deserializeVariant(const NodeAdapter & node,
                            const std::vector<std::string> & nodeNames,
                            std::variant<Ts...> & variantValue)
    {
        bool deserialized = false;
        int index = 0;

        auto try_deserialize_variant = [&](auto && dummyType) {
            using Type = std::decay_t<decltype(dummyType)>;
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
}