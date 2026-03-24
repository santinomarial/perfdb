#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

TEST(SmokeTest, BuildWorks) {
    spdlog::info("vexdb build system working");
    EXPECT_TRUE(true);
}
