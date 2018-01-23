#pragma once
#include "block.h"
#include <string>

class Tree {
  public:
    Tree();
    ~Tree();
    void add_key_value(long key, long value);
    void remove_key(long key);
    long get_value_by_key(long key);

    void persist();
    void init(std::string file_name, long block_size, long n_blocks);
  protected:
  private:

    long get_value_by_key(long key, Block* block);
    long find_next_unused_block_id();
    long mark_block_as_used(long id);
    long mark_block_as_unused(long id);
   
    std::string _file_name;
    int _fd;
    long _block_size;
    long _n_blocks;
    long _n_used_blocks;
 
    // a bit map to store indices that are currently occupied blocks
    std::vector<bool> _used;

    Block* root;
};
