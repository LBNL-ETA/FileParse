#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct VariantParent;
    struct VariantsAll;

    // XML functions
    [[nodiscard]] std::optional<VariantsAll> loadVariantAllXML(std::string_view fileName);
    [[nodiscard]] int saveVariantAllXML(const VariantsAll & element, std::string_view fileName);

    // JSON functions
    [[nodiscard]] std::optional<VariantsAll> loadVariantAllJSON(std::string_view fileName);
    [[nodiscard]] int saveVariantAllJSON(const VariantsAll & element, std::string_view fileName);
}   // namespace Helper
