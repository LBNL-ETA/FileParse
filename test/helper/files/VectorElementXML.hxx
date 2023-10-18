#pragma once

#include <string>

namespace Helper
{
    struct VectorElement;
    struct OptionalVectorElement;
    struct EnumVectorElement;

    std::string testVectorElementDatabase();
    std::string testVectorElementEmptyOptionalDatabase();
    std::string testEmptyVectorElementDatabase();
    std::string testDayVectorElementDatabase();
    std::string vectorElement();
    std::string optionalVectorElement();
    std::string emptyVectorElement();
    std::string enumVectorElement();

    VectorElement loadVectorElement(std::string_view fileName);
    void saveVectorElement(const VectorElement & element, std::string_view fileName);

    OptionalVectorElement loadOptionalVectorElement(std::string_view fileName);
    void saveOptionalVectorElement(const OptionalVectorElement & element,
                                   std::string_view fileName);

    EnumVectorElement loadEnumVectorElement(std::string_view fileName);
    void saveEnumVectorElement(const EnumVectorElement & element, std::string_view fileName);
}