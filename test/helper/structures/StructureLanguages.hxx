#pragma once

#include <string>
#include <optional>
#include <vector>

namespace Helper
{
    struct LanguageEntry
    {
        std::string language;
        std::string text;
        std::optional<std::string> optional_text;
    };

    struct LanguageCollection
    {
        std::vector<LanguageEntry> entries;
    };
}   // namespace Helper
