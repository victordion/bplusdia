#include "block.h"
#include <cstddef>

Block::Block() {

}

// An implementation assuming no duplicate key will be added
void DataBlock::add_key_value(long key, long value) {
    if(_data.empty()) {
        _data.push_back(std::pair<long,long>(key, value));
    } else {
        for(auto it = _data.begin(); it != _data.end(); ++it) {
            if( key < (*it).first) {
                _data.insert(it,std::pair<long,long>(key, value));
                return;
            }
        }
    }
    _data.push_back(std::pair<long,long>(key, value));

}


long DataBlock::size() {
    return sizeof(long) * (_data.size() + 1);
}


long DataBlock::get_value_by_key(long key) {
    for(size_t i = 0; i < _data.size(); ++i) {
        if(key == _data[i].first) {
            return _data[i].second;
        }
    }
    // indicates not found
    return -1;
}
