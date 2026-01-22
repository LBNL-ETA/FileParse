#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct VectorElement;
    struct OptionalVectorElement;
    struct EnumVectorElement;

    // XML functions
    [[nodiscard]] std::optional<VectorElement> loadVectorElementXML(std::string_view fileName);
    [[nodiscard]] int saveVectorElementXML(const VectorElement & element, std::string_view fileName);

    [[nodiscard]] std::optional<OptionalVectorElement>
      loadOptionalVectorElementXML(std::string_view fileName);
    [[nodiscard]] int saveOptionalVectorElementXML(const OptionalVectorElement & element,
                                                   std::string_view fileName);

    [[nodiscard]] std::optional<EnumVectorElement> loadEnumVectorElementXML(std::string_view fileName);
    [[nodiscard]] int saveEnumVectorElementXML(const EnumVectorElement & element,
                                               std::string_view fileName);

    // JSON functions
    [[nodiscard]] std::optional<VectorElement> loadVectorElementJSON(std::string_view fileName);
    [[nodiscard]] int saveVectorElementJSON(const VectorElement & element, std::string_view fileName);

    [[nodiscard]] std::optional<OptionalVectorElement>
      loadOptionalVectorElementJSON(std::string_view fileName);
    [[nodiscard]] int saveOptionalVectorElementJSON(const OptionalVectorElement & element,
                                                    std::string_view fileName);

    [[nodiscard]] std::optional<EnumVectorElement> loadEnumVectorElementJSON(std::string_view fileName);
    [[nodiscard]] int saveEnumVectorElementJSON(const EnumVectorElement & element,
                                                std::string_view fileName);

    // Unified functions (auto-detect format)
    [[nodiscard]] std::optional<VectorElement> loadVectorElement(std::string_view fileName);
    [[nodiscard]] int saveVectorElement(const VectorElement & element, std::string_view fileName);

    [[nodiscard]] std::optional<OptionalVectorElement>
      loadOptionalVectorElement(std::string_view fileName);
    [[nodiscard]] int saveOptionalVectorElement(const OptionalVectorElement & element,
                                                std::string_view fileName);

    [[nodiscard]] std::optional<EnumVectorElement> loadEnumVectorElement(std::string_view fileName);
    [[nodiscard]] int saveEnumVectorElement(const EnumVectorElement & element,
                                            std::string_view fileName);
}   // namespace Helper
