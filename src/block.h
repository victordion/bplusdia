#pragma once
#include "util.h"
#include <vector>

class Block {
  public:
    Block();

    Block(long self_id) : _self_id(self_id) {
        
    }
    
    long get_self_id() {
        return _self_id;
    }
    
    long get_parent_id() {
        return _parent_id;
    }

    void set_parent_id(long parent_id) {
        _parent_id = parent_id;
    }
    virtual bool oversize() {return false;}
    virtual void add_key_value(long key, long value) {}
    virtual std::vector<long> get_children_keys() {return std::vector<long>();}
    virtual std::vector<long> get_children_ids() {return std::vector<long>();}
    virtual std::vector<Block*> get_children_block_ptrs() {return std::vector<Block*>();}

  protected:
    // in bytes
    virtual long size() {return 0L;}

    // Size in bytes
    long _size;
    // Id of this block
    long _self_id;

    long _parent_id;

};

class RootBlock : public Block {
  public:
    RootBlock() {}
    RootBlock(long self_id) : Block(self_id) {
     
    }

    //void add_key_value(long key, long value) {}
    void remove_key(long key) {}
    long get_child_id_by_key(long key) {return 0L;}

    long size() {return 0L;}
    
    //std::vector<long> get_children_keys();
    //std::vector<long> get_children_ids();
    //std::vector<Block*> get_children_block_ptrs();

  private:
  
    std::vector<long> _children_keys;
    std::vector<long> _children_ids;
    std::vector<Block*> _children_block_ptrs;
};

class InternalBlock : public Block {
  public:
    InternalBlock();
    void add_key_value(long key, long value);
    void remove_key(long key);    
    long get_child_id_by_key(long key);
    
    long get_next_sibling_id();
    
    long size();
    
    std::vector<long> get_children_keys;
    std::vector<long> get_children_ids;
    std::vector<Block*> get_children_block_ptrs;
  
  private:
    
    std::vector<long> _children_keys;
    std::vector<long> _children_ids;
    std::vector<Block*> _children_block_ptrs;
    
    long _next_sibling_id;
};

class DataBlock : public Block {

  public:

    void add_key_value(long key, long value);
    void remove_key_value(long key);
    long get_value_by_key(long key);
    long size(); 
    long get_next_sibling_id();

  private:
    std::vector<long> _keys;
    std::vector<long> _values;
    
    long _next_sibling_id;
};





