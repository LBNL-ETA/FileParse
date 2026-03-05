#include "LanguageTestHelper.hxx"

class ArabicTest : public testing::Test
{};

// مرحبا بالعالم / صباح الخير
LANGUAGE_TESTS(ArabicTest,
               "Arabic",
               "مرحبا بالعالم",
               "صباح الخير")
