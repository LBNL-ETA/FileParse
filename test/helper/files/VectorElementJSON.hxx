#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct VectorElement;
    struct OptionalVectorElement;
    struct EnumVectorElement;

    [[nodiscard]] std::optional<VectorElement> loadVectorElementJSON(std::string_view fileName);
    [[nodiscard]] int saveVectorElementJSON(const VectorElement & element, std::string_view fileName);

    [[nodiscard]] std::optional<OptionalVectorElement>
      loadOptionalVectorElementJSON(std::string_view fileName);
    [[nodiscard]] int saveOptionalVectorElementJSON(const OptionalVectorElement & element,
                                                    std::string_view fileName);

    [[nodiscard]] std::optional<EnumVectorElement> loadEnumVectorElementJSON(std::string_view fileName);
    [[nodiscard]] int saveEnumVectorElementJSON(const EnumVectorElement & element,
                                                std::string_view fileName);
}   // namespace Helper
