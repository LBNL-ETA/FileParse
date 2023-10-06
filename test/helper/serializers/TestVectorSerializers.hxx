#pragma once

#include "test/helper/TestStructures.hxx"

#include "XMLNodeAdapter.hxx"

namespace Helper
{
    inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::VectorElement & element);
    inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::VectorElement & element);

    inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::OptionalVectorElement & element);
    inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::OptionalVectorElement & element);

    VectorElement loadVectorElement(std::string_view fileName);
    void saveVectorElement(const VectorElement& element, std::string_view fileName);

    OptionalVectorElement loadOptionalVectorElement(std::string_view fileName);
    void saveOptionalVectorElement(const OptionalVectorElement& element, std::string_view fileName);
}   // namespace Helper