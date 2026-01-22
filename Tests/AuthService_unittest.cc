#include "../src/AuthService.h"
#include <gtest/gtest.h>

namespace authTest {
    TEST(parserTest, TooManyArgs) {
        AuthService s{};

        EXPECT_FALSE(s.parser("test@gmail.com 6543 err"));
        EXPECT_FALSE(s.parser("test@gmail.com"));
        EXPECT_FALSE(s.parser("test@gmail.com 6543"));
        EXPECT_FALSE(s.parser(""));
        EXPECT_FALSE(s.parser("REG test@gmail.com"));
        EXPECT_FALSE(s.parser("REG"));
        EXPECT_FALSE(s.parser("REG test@gmail.com 4321 arg"));
        EXPECT_FALSE(s.parser("LOG test@gmail.com"));
        EXPECT_FALSE(s.parser("LOG test@gmail.com 1234"));
        EXPECT_FALSE(s.parser("LOG"));
        EXPECT_FALSE(s.parser("LOG test@gmail.com 4321 arg"));
        EXPECT_FALSE(s.parser("GET test@gmail.com 4321"));
        EXPECT_FALSE(s.parser("GET"));
    }

    TEST(parserTest, CorrectArgs) {
        {
            AuthService s{};
            EXPECT_TRUE(s.parser("REG test@gmail.com 6543"));
        }
        {
            AuthService s{};
            EXPECT_TRUE(s.parser("LOG test@gmail.com 6543"));
        }
        {
            AuthService s{};
            EXPECT_TRUE(s.parser("GET test"));
        }
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}