#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct BaseElement;

    // XML functions
    [[nodiscard]] std::optional<BaseElement> loadBaseElementXML(std::string_view fileName);
    [[nodiscard]] int saveBaseElementXML(const BaseElement & base, std::string_view fileName);

    // JSON functions
    [[nodiscard]] std::optional<BaseElement> loadBaseElementJSON(std::string_view fileName);
    [[nodiscard]] int saveBaseElementJSON(const BaseElement & base, std::string_view fileName);

    // Unified functions (auto-detect format from extension or content)
    [[nodiscard]] std::optional<BaseElement> loadBaseElement(std::string_view fileName);
    [[nodiscard]] int saveBaseElement(const BaseElement & base, std::string_view fileName);
}   // namespace Helper
