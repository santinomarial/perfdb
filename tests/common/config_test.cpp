#include <gtest/gtest.h>
#include <unordered_map>
#include "common/config.h"
#include "common/macros.h"

using namespace perfdb;

TEST(CommonTest, PageSizeIsPowerOfTwo) {
    EXPECT_EQ(PAGE_SIZE, 4096u);
    EXPECT_EQ(PAGE_SIZE & (PAGE_SIZE - 1), 0u);
}

TEST(CommonTest, InvalidConstants) {
    EXPECT_EQ(INVALID_PAGE_ID, -1);
    EXPECT_EQ(INVALID_LSN, -1);
}

TEST(CommonTest, RIDEquality) {
    RID a{1, 0}, b{1, 0}, c{2, 0};
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

TEST(CommonTest, RIDValidity) {
    RID valid{0, 0};
    EXPECT_TRUE(valid.IsValid());
    RID invalid{INVALID_PAGE_ID, 0};
    EXPECT_FALSE(invalid.IsValid());
}

TEST(CommonTest, RIDHash) {
    std::unordered_map<RID, int> m;
    RID key{1, 0};
    m[key] = 42;
    EXPECT_EQ(m[key], 42);
}

TEST(CommonTest, PerfdbAssert) {
    EXPECT_NO_THROW(PERFDB_ASSERT(1 == 1, "should pass"));
    EXPECT_THROW(PERFDB_ASSERT(1 == 2, "should fail"), std::runtime_error);
}
