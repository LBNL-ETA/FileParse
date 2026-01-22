#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct BaseElement;

    [[nodiscard]] std::optional<BaseElement> loadBaseElementJSON(std::string_view fileName);
    [[nodiscard]] int saveBaseElementJSON(const BaseElement & base, std::string_view fileName);
}
