#include "LanguageTestHelper.hxx"

class EmojiTest : public testing::Test
{};

// Pure emoji strings with no ASCII
LANGUAGE_TESTS(EmojiTest,
               "Emoji",
               "🌍🌎🌏🔥💧🌿",
               "👨‍👩‍👧‍👦🏠🎉")
