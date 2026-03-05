#include "LanguageTestHelper.hxx"

class FrenchTest : public testing::Test
{};

// Bonjour le monde ! / Café crème
LANGUAGE_TESTS(FrenchTest,
               "French",
               "Bonjour le monde !",
               "Café crème")
