#pragma once

#include <gtest/gtest.h>

#include "fileParse/FileDataHandler.hxx"

#include "test/helper/structures/StructureLanguages.hxx"
#include "test/helper/serializers/SerializersLanguages.hxx"

#include "test/helper/MockNodeAdapter.hxx"

namespace LanguageTest
{
    inline void verifyMockNodeRoundTrip(const std::string & language,
                                        const std::string & text,
                                        const std::optional<std::string> & optionalText = std::nullopt)
    {
        Helper::LanguageEntry original;
        original.language = language;
        original.text = text;
        original.optional_text = optionalText;

        Helper::MockNode elementNode("Entry");
        Helper::MockNodeAdapter adapter{&elementNode};
        adapter << original;

        Helper::LanguageEntry loaded;
        const Helper::MockNodeAdapter readAdapter{&elementNode};
        readAdapter >> loaded;

        EXPECT_EQ(original.language, loaded.language);
        EXPECT_EQ(original.text, loaded.text);
        EXPECT_EQ(original.optional_text, loaded.optional_text);
    }

    inline void verifyXMLStringRoundTrip(const std::string & language,
                                          const std::string & text,
                                          const std::optional<std::string> & optionalText = std::nullopt)
    {
        Helper::LanguageEntry original;
        original.language = language;
        original.text = text;
        original.optional_text = optionalText;

        const auto xmlString = Common::saveToXMLString(original, "Entry");
        ASSERT_FALSE(xmlString.empty());

        const auto loaded = Common::loadFromXMLString<Helper::LanguageEntry>(xmlString, "Entry");
        ASSERT_TRUE(loaded.has_value());

        EXPECT_EQ(original.language, loaded->language);
        EXPECT_EQ(original.text, loaded->text);
        EXPECT_EQ(original.optional_text, loaded->optional_text);
    }

    inline void verifyJSONStringRoundTrip(const std::string & language,
                                           const std::string & text,
                                           const std::optional<std::string> & optionalText = std::nullopt)
    {
        Helper::LanguageEntry original;
        original.language = language;
        original.text = text;
        original.optional_text = optionalText;

        const auto jsonString = Common::saveToJSONString(original, "Entry");
        ASSERT_FALSE(jsonString.empty());

        const auto loaded = Common::loadFromJSONString<Helper::LanguageEntry>(jsonString, "Entry");
        ASSERT_TRUE(loaded.has_value());

        EXPECT_EQ(original.language, loaded->language);
        EXPECT_EQ(original.text, loaded->text);
        EXPECT_EQ(original.optional_text, loaded->optional_text);
    }
}   // namespace LanguageTest

// Macro to generate all standard language tests from just a fixture name and data.
// Each language file only needs to define the fixture, the test data, and invoke this macro.
// NOLINTBEGIN(cppcoreguidelines-macro-usage)
#define LANGUAGE_TESTS(FixtureName, language, text, ...)                                            \
    TEST_F(FixtureName, MockNodeRoundTrip)                                                         \
    {                                                                                              \
        LanguageTest::verifyMockNodeRoundTrip(language, text, ##__VA_ARGS__);                       \
    }                                                                                              \
    TEST_F(FixtureName, XMLStringRoundTrip)                                                        \
    {                                                                                              \
        LanguageTest::verifyXMLStringRoundTrip(language, text, ##__VA_ARGS__);                      \
    }                                                                                              \
    TEST_F(FixtureName, JSONStringRoundTrip)                                                       \
    {                                                                                              \
        LanguageTest::verifyJSONStringRoundTrip(language, text, ##__VA_ARGS__);                     \
    }
// NOLINTEND(cppcoreguidelines-macro-usage)
