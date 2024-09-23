#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct VariantParent;
    struct VariantsAll;

    [[nodiscard]] std::optional<VariantsAll> loadVariantAll(std::string_view fileName);
    [[nodiscard]] int saveVariantAll(const VariantsAll & element, std::string_view fileName);
}