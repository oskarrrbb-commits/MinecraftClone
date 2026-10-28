#pragma once 
#include <array>
#include <vector>
#include <glm/glm.hpp>
#include "Block.h"
struct MeshData {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};
class Chunk;
struct ChunkNeighbors {
    const Chunk* posX = nullptr;
    const Chunk* negX = nullptr;
    const Chunk* posZ = nullptr;
    const Chunk* negZ = nullptr;
};
class Chunk {
    public:
        static const int CHUNK_SIZE = 16;
        Chunk();
        void generate();
        glm::vec3 getBlockColor(BlockType type) const;
        BlockType getBlock(int x, int y, int z) const;
        void setBlock(int x, int y, int z, BlockType blockType);
        MeshData buildMesh(const ChunkNeighbors& neighbors) const;
    private:
        std::array<BlockType, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE> m_blocks;
        bool isAir(int x, int y, int z, const ChunkNeighbors& neighbors) const;
        int index(int x, int y, int z) const;
           
};