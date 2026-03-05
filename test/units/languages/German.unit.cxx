#include "LanguageTestHelper.hxx"

class GermanTest : public testing::Test
{};

// Grüße aus der Welt / Guten Morgen
LANGUAGE_TESTS(GermanTest,
               "German",
               "Grüße aus der Welt",
               "Guten Morgen")
