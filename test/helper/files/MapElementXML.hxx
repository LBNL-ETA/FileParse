#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct MapElementString;
    struct MapElementOptionalString;
    struct MapElementEnum;
    struct MapElementDouble;
    struct MapElementEnumDouble;
    struct CMAElement;

    [[nodiscard]] std::string testCMAElementDatabase();
    [[nodiscard]] std::string cmaElement1();
    [[nodiscard]] std::string cmaElement2();

    [[nodiscard]] std::optional<MapElementString> loadMapElementString(std::string_view fileName);
    [[nodiscard]] int saveMapElementDouble(const MapElementString & element,
                                           std::string_view fileName);

    [[nodiscard]] std::optional<MapElementOptionalString>
      loadMapElementOptionalString(std::string_view fileName);
    [[nodiscard]] int saveMapElementOptionalString(const MapElementOptionalString & element,
                                                   std::string_view fileName);

    [[nodiscard]] std::optional<MapElementEnum> loadMapElementEnum(std::string_view fileName);
    [[nodiscard]] int saveMapElementEnum(const MapElementEnum & element, std::string_view fileName);

    [[nodiscard]] std::optional<MapElementDouble> loadMapElementDouble(std::string_view fileName);
    [[nodiscard]] int saveMapElementDouble(const MapElementDouble & element,
                                           std::string_view fileName);

    [[nodiscard]] std::optional<MapElementEnumDouble> loadMapElementEnumDouble(std::string_view fileName);
    [[nodiscard]] int saveMapElementEnumDouble(const MapElementEnumDouble & element,
                                               std::string_view fileName);

    [[nodiscard]] CMAElement loadCMAElement(std::string_view fileName);
    [[nodiscard]] int saveCMAElement(const CMAElement & element, std::string_view fileName);
}   // namespace Helper