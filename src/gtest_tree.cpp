#include "gtest/gtest.h"
#include "tree.h"
#include <stdexcept>

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
    try {
        Bplusdia::Tree* tree = new Bplusdia::Tree();
        string file = "tree.dat";
        long block_size = 4096L;
        long n_blocks = 1024L;
        long b = 5;
        tree->init_new(file, block_size, n_blocks, b);
        delete tree;
        
        Bplusdia::Tree* recoverd = Bplusdia::init_from_file("tree.dat"); 
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
}

// Compile with Google test using
// g++ -I${GTEST_DIR}/include -pthread gtest_tree.cpp ${GTEST_DIR}/libgtest.a -o gtest_tree
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
