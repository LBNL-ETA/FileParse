#include "LanguageTestHelper.hxx"

class HindiTest : public testing::Test
{};

// नमस्ते दुनिया / शुभ प्रभात
LANGUAGE_TESTS(HindiTest,
               "Hindi",
               "नमस्ते दुनिया",
               "शुभ प्रभात")
