#include "block.h"
#include <cstddef>

Block::Block() {

}

// An implementation assuming no duplicate key will be added
void DataBlock::add_key_value(long key, long value) {
    if(_keys.empty()) {
        _keys.push_back(key);
        _values.push_back(value);
    } else {
        for(size_t i = 0; i < _keys.size(); ++i) {
            // Overwrite
            if(key == _keys[i]) {
                _values[i] = value;
                return;
            }
            else if(key < _keys[i]) {
                _keys.insert(_keys.begin() + i, key);
                _values.insert(_values.begin() + i, value);
                return;
            }
        }
    }
    _keys.push_back(key);
    _values.push_back(value);
}


long DataBlock::size() {
    return 2 * sizeof(long) * (_keys.size()) + sizeof(long);
}


long DataBlock::get_value_by_key(long key) {
    for(size_t i = 0; i < _keys.size(); ++i) {
        if(key == _keys[i]) {
            return _values[i];
        }
    }
    // indicates not found
    return -1;
}
