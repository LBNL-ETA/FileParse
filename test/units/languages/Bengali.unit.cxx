#include "LanguageTestHelper.hxx"

class BengaliTest : public testing::Test
{};

// হ্যালো বিশ্ব / সুপ্রভাত
LANGUAGE_TESTS(BengaliTest,
               "Bengali",
               "হ্যালো বিশ্ব",
               "সুপ্রভাত")
