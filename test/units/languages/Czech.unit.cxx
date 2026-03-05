#include "LanguageTestHelper.hxx"

class CzechTest : public testing::Test
{};

// Ahoj světe / Příjemný den
LANGUAGE_TESTS(CzechTest,
               "Czech",
               "Ahoj světe",
               "Příjemný den")
