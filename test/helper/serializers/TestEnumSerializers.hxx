#pragma once

#include "test/helper/TestStructures.hxx"

#include "XMLNodeAdapter.hxx"

namespace Helper
{
    inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::EnumElement & element);
    inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::EnumElement & element);

    EnumElement loadEnumElement(std::string_view fileName);
    void saveEnumElement(const EnumElement& element, std::string_view fileName);
}   // namespace Helper