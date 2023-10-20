#pragma once

#include <string>

namespace Helper
{
    struct VariantParent;
    struct VariantsAll;

    std::string testVariantParent();
    std::string variantParentString();
    std::string variantParentDouble();

    VariantsAll loadVariantAll(std::string_view fileName);
    void saveVariantAll(const VariantsAll & element, std::string_view fileName);
}