#pragma once

#include "test/helper/structures/StructureMap.hxx"
#include "XMLNodeAdapter.hxx"

namespace Helper
{
    inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::MapElementString & element);
    inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::MapElementString & element);

    inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::MapElementOptionalString & element);
    inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::MapElementOptionalString & element);

    inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::MapElementEnum & element);
    inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::MapElementEnum & element);

    MapElementString loadMapElementString(std::string_view fileName);
    void saveSetElementDouble(const MapElementString& element, std::string_view fileName);

    MapElementOptionalString loadMapElementOptionalString(std::string_view fileName);
    void saveSetElementOptionalDouble(const MapElementOptionalString& element, std::string_view fileName);

    MapElementEnum loadMapElementEnum(std::string_view fileName);
    void saveSetElementEnum(const MapElementEnum& element, std::string_view fileName);
}