#pragma once
#include "util.h"
#include <vector>

class Block {
  public:
    Block();
    
  protected:
    // in bytes
    virtual long size() = 0;

    long get_self_id();

    virtual bool is_oversize() = 0;
  
  private:
    // Size in bytes
    long _size;
    // Id of this block
    long self_id;

    long parent_id;

    long n_children;

    long* children_ids;

    long* children_keys;
    
    BlockType type; 

};


class RootBlock : public Block {
  public:
    RootBlock();
    void add_key(long key);
    void delete_key(long key);
    // SPlit into 3 blocks
    // 1st block: new root
    // 2nd block: left child of new root
    // 3rd block: right child of new root
    std::vector<Block> split();

    bool is_oversize();
  private:
};

class InternalBlock : public Block {
  public:
    InternalBlock();
    void add_key(long key);
    void delete_key(long key);    

  private:

};

class DataBlock : Block {

  public:

    void add_key_value(long key, long value);
    void remove_key_value(long key);
    long get_value_by_key(long key);
    long size(); 
    std::vector<DataBlock> split(long* pivot_key);

  private:
    std::vector<std::pair<long, long> > _data;
    
    long right_sibling_id;
};





