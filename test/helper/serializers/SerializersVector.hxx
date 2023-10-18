#pragma once

#include "Common.hxx"
#include "Vector.hxx"

#include "test/helper/structures/StructureVector.hxx"

namespace Helper
{
    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::VectorElement & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        node >> Child{{"Table", "Value"}, element.values};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::VectorElement & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        node << Child{{"Table", "Value"}, element.values};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::OptionalVectorElement & element)
    {
        using FileParse::Child;
        using FileParse::operator>>;

        node >> Child{{"Table", "Value"}, element.values};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::OptionalVectorElement & element)
    {
        using FileParse::Child;
        using FileParse::operator<<;

        node << Child{{"Table", "Value"}, element.values};

        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator>>(const NodeAdapter & node, Helper::EnumVectorElement & element)
    {
        FileParse::deserializeEnumVector<NodeAdapter, Helper::Day>(
          node, {"Table", "Value"}, element.days, toDay);
        return node;
    }

    template<typename NodeAdapter>
    inline NodeAdapter operator<<(NodeAdapter node, const Helper::EnumVectorElement & element)
    {
        FileParse::serializeEnumVector<NodeAdapter, Helper::Day>(
          node, {"Table", "Value"}, element.days, toDayString);
        return node;
    }

    VectorElement loadVectorElement(std::string_view fileName);
    void saveVectorElement(const VectorElement & element, std::string_view fileName);

    OptionalVectorElement loadOptionalVectorElement(std::string_view fileName);
    void saveOptionalVectorElement(const OptionalVectorElement & element,
                                   std::string_view fileName);

    EnumVectorElement loadEnumVectorElement(std::string_view fileName);
    void saveEnumVectorElement(const EnumVectorElement & element, std::string_view fileName);


}   // namespace Helper