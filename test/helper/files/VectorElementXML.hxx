#pragma once

#include <string>

namespace Helper
{
    struct VectorElement;
    struct OptionalVectorElement;
    struct EnumVectorElement;

    [[nodiscard]] std::string testVectorElementDatabase();
    [[nodiscard]] std::string testVectorElementEmptyOptionalDatabase();
    [[nodiscard]] std::string testEmptyVectorElementDatabase();
    [[nodiscard]] std::string testDayVectorElementDatabase();
    [[nodiscard]] std::string vectorElement();
    [[nodiscard]] std::string optionalVectorElement();
    [[nodiscard]] std::string emptyVectorElement();
    [[nodiscard]] std::string enumVectorElement();

    [[nodiscard]] VectorElement loadVectorElement(std::string_view fileName);
    [[nodiscard]] int saveVectorElement(const VectorElement & element, std::string_view fileName);

    [[nodiscard]] OptionalVectorElement loadOptionalVectorElement(std::string_view fileName);
    [[nodiscard]] int saveOptionalVectorElement(const OptionalVectorElement & element,
                                   std::string_view fileName);

    [[nodiscard]] EnumVectorElement loadEnumVectorElement(std::string_view fileName);
    [[nodiscard]] int saveEnumVectorElement(const EnumVectorElement & element, std::string_view fileName);
}