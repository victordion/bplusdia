#include "tree.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <typeinfo>
#include <string.h>
#include <cstring>

namespace Bplusdia {
    
    Tree::Tree() {
    
    }
    
    void Tree::init_new(std::string file_name, long block_size, long n_blocks, long b) {
        _b = b;
        _n_blocks = n_blocks;
        _block_size = block_size;
        _n_used_blocks = 0;
        _used.resize(_n_blocks);
     
        if (access(file_name.c_str(), F_OK ) != -1) {
            throw "File exists. Exiting.";
        }

        _fd = open(file_name.c_str(), O_RDWR | O_CREAT, 0666);
        
        /* Fill in file metadata */
 
        lseek(_fd, 0, SEEK_SET);
        write(_fd, "Bplusdia", 8);
        
        lseek(_fd, 16, SEEK_SET);
        write(_fd, (void*) &n_blocks, 8);
        
        lseek(_fd, 24, SEEK_SET);
        write(_fd, (void*) &block_size, 8);
    
        lseek(_fd, 32, SEEK_SET);
        write(_fd, (void*) &b, 8);

        long root_block_id = 0;
        lseek(_fd, 40, SEEK_SET);
        write(_fd, (void*) &root_block_id, 8);
       
        long max_n_blocks = 8192;
        long n_bytes_in_bitmap = max_n_blocks / 8; 
        char bitmap[n_bytes_in_bitmap];
        memset(bitmap, 0, n_bytes_in_bitmap);         
        lseek(_fd, 1024, SEEK_SET);
        write(_fd, (void*) bitmap, n_bytes_in_bitmap);

        long block_data_base_offset = 1024 + max_n_blocks / 8;
        long block_data_size = _n_blocks * _block_size;
       
        /* Seek to Block 0, i.e. root block */
        lseek(_fd, block_data_base_offset, SEEK_SET);
        write(_fd, (void*) &root_block_id, 8);


        // Seek to end of file and write something there
        lseek(_fd, block_data_base_offset + block_data_size, SEEK_SET);
        write(_fd, (void*) "****", 4);
        
    }
    
    void Tree::add_key_value(long key, long value) {
        if (!root) {
            root = new RootBlock(0);
            root->add_key_value(key, value);
        } else {
            Block* current = root;
            current->add_key_value(key, value);
            
            if (current->oversize()) {
            
            }
            
        }
    }
    
    long Tree::get_value_by_key(long key) {
        return get_value_by_key(key, root);
    }
    
    long Tree::get_value_by_key(long key, Block* block) {
        if (!block) {
            return -1;
        } 
        else {
            if(typeid(block) == typeid(DataBlock)) {
                return ((DataBlock*)block)->get_value_by_key(key);
            }
            else {
                std::vector<long> keys = block->get_children_keys();
                for(size_t i = 0; i < keys.size(); ++i) {
                    if (key < keys[i]) {
                        return get_value_by_key(key, block->get_children_block_ptrs()[i]);
                    }
                }
            }
        }
    }
    
    Tree::~Tree() {
        close(_fd);
    }
   
    /*
     *
     */ 
    Tree* init_from_file(std::string file_name) {
      
        Tree* tree = new Tree();
        
        int fd = open(file_name.c_str(), O_RDWR);
        tree->set_fd(fd); 
        
        char buf[4096];
        read(fd, (void *) buf, 4096);

        
        char logo[8];
        memcpy(logo, buf, 8);
        std::string logo_str(logo, logo + 8);

        if (logo_str != "Bplusdia") {
            return NULL;
        }
              
        return tree;
    } 
}
