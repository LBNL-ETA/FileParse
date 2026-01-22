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

    // XML functions
    [[nodiscard]] std::optional<MapElementString> loadMapElementStringXML(std::string_view fileName);
    [[nodiscard]] int saveMapElementStringXML(const MapElementString & element,
                                              std::string_view fileName);

    [[nodiscard]] std::optional<MapElementOptionalString>
      loadMapElementOptionalStringXML(std::string_view fileName);
    [[nodiscard]] int saveMapElementOptionalStringXML(const MapElementOptionalString & element,
                                                      std::string_view fileName);

    [[nodiscard]] std::optional<MapElementEnum> loadMapElementEnumXML(std::string_view fileName);
    [[nodiscard]] int saveMapElementEnumXML(const MapElementEnum & element, std::string_view fileName);

    [[nodiscard]] std::optional<MapElementDouble> loadMapElementDoubleXML(std::string_view fileName);
    [[nodiscard]] int saveMapElementDoubleXML(const MapElementDouble & element,
                                              std::string_view fileName);

    [[nodiscard]] std::optional<MapElementEnumDouble> loadMapElementEnumDoubleXML(std::string_view fileName);
    [[nodiscard]] int saveMapElementEnumDoubleXML(const MapElementEnumDouble & element,
                                                  std::string_view fileName);

    [[nodiscard]] std::optional<CMAElement> loadCMAElementXML(std::string_view fileName);
    [[nodiscard]] int saveCMAElementXML(const CMAElement & element, std::string_view fileName);

    // JSON functions
    [[nodiscard]] std::optional<MapElementString> loadMapElementStringJSON(std::string_view fileName);
    [[nodiscard]] int saveMapElementStringJSON(const MapElementString & element,
                                               std::string_view fileName);

    [[nodiscard]] std::optional<MapElementOptionalString>
      loadMapElementOptionalStringJSON(std::string_view fileName);
    [[nodiscard]] int saveMapElementOptionalStringJSON(const MapElementOptionalString & element,
                                                       std::string_view fileName);

    [[nodiscard]] std::optional<MapElementEnum> loadMapElementEnumJSON(std::string_view fileName);
    [[nodiscard]] int saveMapElementEnumJSON(const MapElementEnum & element, std::string_view fileName);

    [[nodiscard]] std::optional<MapElementDouble> loadMapElementDoubleJSON(std::string_view fileName);
    [[nodiscard]] int saveMapElementDoubleJSON(const MapElementDouble & element,
                                               std::string_view fileName);

    [[nodiscard]] std::optional<MapElementEnumDouble> loadMapElementEnumDoubleJSON(std::string_view fileName);
    [[nodiscard]] int saveMapElementEnumDoubleJSON(const MapElementEnumDouble & element,
                                                   std::string_view fileName);

    [[nodiscard]] std::optional<CMAElement> loadCMAElementJSON(std::string_view fileName);
    [[nodiscard]] int saveCMAElementJSON(const CMAElement & element, std::string_view fileName);
}   // namespace Helper
