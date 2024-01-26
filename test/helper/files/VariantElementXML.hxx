#pragma once

#include <string>

namespace Helper
{
    struct VariantParent;
    struct VariantsAll;

    [[nodiscard]] std::string testVariantParent();
    [[nodiscard]] std::string variantParentTemperature();
    [[nodiscard]] std::string variantParentHumidity();

    [[nodiscard]] VariantsAll loadVariantAll(std::string_view fileName);
    [[nodiscard]] int saveVariantAll(const VariantsAll & element, std::string_view fileName);
}