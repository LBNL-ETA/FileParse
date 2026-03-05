#include "LanguageTestHelper.hxx"

class GreekTest : public testing::Test
{};

// Γεια σου Κόσμε
LANGUAGE_TESTS(GreekTest,
               "Greek",
               "Γεια σου Κόσμε")
