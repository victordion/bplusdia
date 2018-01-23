#include "tree.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <typeinfo>

Tree::Tree() {

}

void Tree::init(std::string file_name, long block_size, long n_blocks) {

    _n_blocks = n_blocks;
    _block_size = block_size;
    _n_used_blocks = 0;
    _used.resize(_n_blocks);
 
    _fd = open(file_name.c_str(), O_RDWR);
    off_t total_size = (off_t) block_size * n_blocks;
    lseek(_fd, total_size, SEEK_SET);

    const char* place_holder = "\0";
    write(_fd, (const void*)place_holder, 1);
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
