#include "gtest/gtest.h"
#include "tree.h"
#include <stdexcept>
#include <stdio.h>

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
        remove("tree.dat");
    }

    virtual void TearDown()
    {
    }
};


TEST_F(TreeTest, Haha) {
    Bplusdia::Tree* tree = new Bplusdia::Tree();
    string file = "tree.dat";
    long block_size = 4096L;
    long n_blocks = 1024L;
    long b = 5L;
    tree->init_new(file, block_size, n_blocks, b);
    delete tree;
    
    Bplusdia::Tree* recovered = Bplusdia::init_from_file("tree.dat");
    EXPECT_EQ(recovered->get_n_blocks(), 1024L); 
    EXPECT_EQ(recovered->get_block_size(), 4096L); 
    EXPECT_EQ(recovered->get_b(), 5L); 
}

// Compile with Google test using
// g++ -I${GTEST_DIR}/include -pthread gtest_tree.cpp ${GTEST_DIR}/libgtest.a -o gtest_tree
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
