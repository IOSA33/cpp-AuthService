#include "../src/AuthService.h"
#include <gtest/gtest.h>

namespace authTest {
    TEST(parserTest, TooManyArgs) {
        AuthService s{};
        EXPECT_EQ(false, s.parser("test@gmail.com 6543 err"));
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}