#pragma once

enum BlockType {
    ROOT = 0,
    INTERNAL = 1,
    LEAF = 2,
    DATA = 3
};

// the b
const long BLOCK_MAX_DEGREE = 10;
