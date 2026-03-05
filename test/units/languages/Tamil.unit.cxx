#include "LanguageTestHelper.hxx"

class TamilTest : public testing::Test
{};

// வணக்கம் உலகம் / காலை வணக்கம்
LANGUAGE_TESTS(TamilTest,
               "Tamil",
               "வணக்கம் உலகம்",
               "காலை வணக்கம்")
