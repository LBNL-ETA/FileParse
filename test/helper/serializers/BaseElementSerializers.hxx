#pragma once

#include "test/helper/structures/StructureBase.hxx"

#include "XMLNodeAdapter.hxx"

namespace Helper
{
    inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::BaseElement & base);
    inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::BaseElement & base);

    BaseElement loadBaseElement(std::string_view fileName);
    void saveBaseElement(const BaseElement& base, std::string_view fileName);
}   // namespace Helper