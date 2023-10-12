#pragma once

#include "test/helper/structures/StructureMap.hxx"
#include "XMLNodeAdapter.hxx"

namespace Helper
{
    inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::MapElementString & element);
    inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::MapElementString & element);

    MapElementString loadMapElementString(std::string_view fileName);
    void saveSetElementDouble(const MapElementString& element, std::string_view fileName);
}