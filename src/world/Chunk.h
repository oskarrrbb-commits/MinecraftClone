#pragma once 
#include <array>
#include <vector>
#include "Block.h"
struct MeshData {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};
class Chunk {
    public:
        static const int CHUNK_SIZE = 16;
        Chunk();
        void generate();
        BlockType getBlock(int x, int y, int z) const;
        void setBlock(int x, int y, int z, BlockType blockType);
        MeshData buildMesh() const;
    private:
        std::array<BlockType, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE> m_blocks;

        int index(int x, int y, int z) const;
           
};


