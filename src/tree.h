#pragma once
#include "block.h"
#include <string>

namespace Bplusdia {
    class Tree {
      public:
        Tree();
        ~Tree();
        void add_key_value(long key, long value);
        void remove_key(long key);
        long get_value_by_key(long key);
    
        void persist();
        void init_new(std::string file_name, long block_size, long n_blocks, long b);
        void set_fd(int fd) {_fd = fd;}
        
        long get_n_blocks() {return _n_blocks;}
        void set_n_blocks(long n_blocks) {_n_blocks = n_blocks;}
 
        long get_block_size() {return _block_size;}
        void set_block_size(long block_size) {_block_size = block_size;}
        
        long get_b() {return _b;}
        void set_b(long b) {_b = b;}
      
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
        long _b;
     
        // a bit map to store indices that are currently occupied blocks
        std::vector<bool> _used;
    
        Block* root;
    };
    
    Tree* init_from_file(std::string file_name);   
     
}
