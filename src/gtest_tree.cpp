#include "gtest/gtest.h"

using namespace std;

class TreeTest : public ::testing::Test {
  protected:
    static void SetUpTestCase()
    {
    }

    static void TearDownTestCase()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};


TEST_F(TreeTest, Haha) {
    ASSERT_EQ(0, 0);
}

// Compile with Google test using
// g++ -I${GTEST_DIR}/include -pthread gtest_tree.cpp ${GTEST_DIR}/libgtest.a -o gtest_tree
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
