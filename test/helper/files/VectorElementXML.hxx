#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct VectorElement;
    struct OptionalVectorElement;
    struct EnumVectorElement;

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