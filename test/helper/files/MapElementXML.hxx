#pragma once

#include <string>

namespace Helper
{
    struct MapElementString;
    struct MapElementOptionalString;
    struct MapElementEnum;
    struct MapElementDouble;
    struct MapElementEnumDouble;
    struct CMAElement;

    std::string testMapElementStringDatabase();
    std::string mapElementString();

    std::string testMapElementDoubleDatabase();
    std::string mapElementDouble();

    std::string testMapElementOptionalStringDatabase();
    std::string mapElementOptionalString();

    std::string testMapElementEmptyStringDatabase();
    std::string mapElementEmptyString();

    std::string testMapElementDayStringDatabase();
    std::string mapElementDayString();

    std::string testMapElementDayDoubleDatabase();
    std::string mapElementDayDouble();

    std::string testCMAElementDatabase();
    std::string cmaElement1();
    std::string cmaElement2();

    MapElementString loadMapElementString(std::string_view fileName);
    void saveMapElementDouble(const MapElementString & element, std::string_view fileName);

    MapElementOptionalString loadMapElementOptionalString(std::string_view fileName);
    void saveMapElementOptionalDouble(const MapElementOptionalString & element,
                                      std::string_view fileName);

    MapElementEnum loadMapElementEnum(std::string_view fileName);
    void saveMapElementEnum(const MapElementEnum & element, std::string_view fileName);

    MapElementDouble loadMapElementDouble(std::string_view fileName);
    void saveMapElementDouble(const MapElementDouble & element, std::string_view fileName);

    MapElementEnumDouble loadMapElementEnumDouble(std::string_view fileName);
    void saveMapElementEnumDouble(const MapElementEnumDouble & element, std::string_view fileName);

    CMAElement loadCMAElement(std::string_view fileName);
    void saveCMAElement(const CMAElement & element, std::string_view fileName);
}