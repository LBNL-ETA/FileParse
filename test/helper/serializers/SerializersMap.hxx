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

    inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::MapElementDouble & element);
    inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::MapElementDouble & element);

    inline XMLNodeAdapter operator>>(const XMLNodeAdapter & xmlNode, Helper::MapElementEnumDouble & element);
    inline XMLNodeAdapter operator<<(XMLNodeAdapter xmlNode, const Helper::MapElementEnumDouble & element);

    MapElementString loadMapElementString(std::string_view fileName);
    void saveMapElementDouble(const MapElementString& element, std::string_view fileName);

    MapElementOptionalString loadMapElementOptionalString(std::string_view fileName);
    void saveMapElementOptionalDouble(const MapElementOptionalString& element, std::string_view fileName);

    MapElementEnum loadMapElementEnum(std::string_view fileName);
    void saveMapElementEnum(const MapElementEnum& element, std::string_view fileName);

    MapElementDouble loadMapElementDouble(std::string_view fileName);
    void saveMapElementDouble(const MapElementDouble& element, std::string_view fileName);

    MapElementEnumDouble loadMapElementEnumDouble(std::string_view fileName);
    void saveMapElementEnumDouble(const MapElementEnumDouble& element, std::string_view fileName);
}