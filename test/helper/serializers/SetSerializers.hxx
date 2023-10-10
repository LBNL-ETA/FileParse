#pragma once

#include "test/helper/structures/StructureSet.hxx"
#include "XMLNodeAdapter.hxx"

namespace Helper
{
    inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::SetElementDouble & element);
    inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::SetElementDouble & element);

    SetElementDouble loadSetElementDouble(std::string_view fileName);
    void saveSetElementDouble(const SetElementDouble& element, std::string_view fileName);
}