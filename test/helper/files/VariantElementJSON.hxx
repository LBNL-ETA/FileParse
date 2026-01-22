#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct VariantParent;
    struct VariantsAll;

    [[nodiscard]] std::optional<VariantsAll> loadVariantAllJSON(std::string_view fileName);
    [[nodiscard]] int saveVariantAllJSON(const VariantsAll & element, std::string_view fileName);
}
