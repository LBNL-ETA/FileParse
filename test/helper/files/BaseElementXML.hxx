#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct BaseElement;

    [[nodiscard]] std::optional<BaseElement> loadBaseElement(std::string_view fileName);
    [[nodiscard]] int saveBaseElement(const BaseElement & base, std::string_view fileName);
}