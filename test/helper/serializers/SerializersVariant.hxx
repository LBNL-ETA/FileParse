#pragma once

#include <typeindex>

#include "Common.hxx"
#include "Vector.hxx"
#include "Variant.hxx"

#include "test/helper/structures/StructureVariant.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::ElementTemperature & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;
        using FileParse::deserializeVariant;

        node >> Child{"Temperature", element.temperature};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::ElementTemperature & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;
        using FileParse::serializeVariant;

        node << Child{"Temperature", element.temperature};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::ElementHumidity & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;
        using FileParse::deserializeVariant;

        node >> Child{"Humidity", element.humidity};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::ElementHumidity & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;
        using FileParse::serializeVariant;

        node << Child{"Humidity", element.humidity};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::VariantParent & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;
        using FileParse::deserializeVariant;

        node >> Child{"Name", element.name};

        std::map<std::string, std::function<void(const NodeAdapter &, Helper::VariantParent &)>>
          handlers
          = {{"VariantParentTemperature",
              [&](const NodeAdapter & aNode, Helper::VariantParent & el) {
                  Helper::ElementTemperature data;
                  aNode >> data;
                  el.value = data;
              }},
             {"VariantParentHumidity", [&](const NodeAdapter & aNode, Helper::VariantParent & el) {
                  Helper::ElementHumidity data;
                  aNode >> data;
                  el.value = data;
              }}};

        auto currentTag{node.getCurrentTag()};
        if(auto handler = handlers.find(currentTag); handler != handlers.end())
        {
            handler->second(node, element);
        }

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::VariantParent & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;
        using FileParse::serializeVariant;

        node << Child{"Name", element.name};
        node << element.value;

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::VariantsAll & element)
    {
        auto processTag = [&node, &element](const std::string & tagValue) {
            const auto n{node.nChildNode(tagValue)};
            for(int i = 0; i < n; ++i)
            {
                Helper::VariantParent vp;
                node.getChildNode(tagValue, i) >> vp;
                element.values.push_back(vp);
            }
        };

        element.values.clear();

        processTag("VariantParentTemperature");
        processTag("VariantParentHumidity");

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::VariantsAll & element)
    {
        std::map<std::type_index, std::function<void(const Helper::VariantParent &, NodeAdapter &)>>
          serializers = {
            {std::type_index(typeid(Helper::ElementTemperature)),
             [](const Helper::VariantParent & vp, NodeAdapter & aNode) {
                              aNode.addChild("VariantParentTemperature") << vp;
             }},
            {std::type_index(typeid(Helper::ElementHumidity)),
             [](const Helper::VariantParent & vp, NodeAdapter & aNode) {
                              aNode.addChild("VariantParentHumidity") << vp;
             }}
          };

        for(const auto & vp : element.values)
        {
            std::visit(
              [&](auto && arg) {
                  using T = std::decay_t<decltype(arg)>;
                  serializers[std::type_index(typeid(T))](vp, node);
              },
              vp.value);
        }

        return node;
    }
}   // namespace Helper