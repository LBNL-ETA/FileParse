#include "LanguageTestHelper.hxx"

class AmharicTest : public testing::Test
{};

// ሰላም ዓለም / እንደምን አደርክ
LANGUAGE_TESTS(AmharicTest,
               "Amharic",
               "ሰላም ዓለም",
               "እንደምን አደርክ")
