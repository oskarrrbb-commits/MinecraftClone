#include "Chunk.h"
#include <vector>
#include <glm/glm.hpp>

static const int neighborOffsets[6][3] = {
    { 1, 0, 0}, {-1, 0, 0},
    { 0, 1, 0}, { 0,-1, 0},
    { 0, 0, 1}, { 0, 0,-1},
};

static const float faceVertexOffsets[6][12] = {
{1,0,0, 1,1,0, 1,1,1, 1,0,1},
    {0,0,1, 0,1,1, 0,1,0, 0,0,0},
    {0,1,0, 1,1,0, 1,1,1, 0,1,1},
    {0,0,1, 1,0,1, 1,0,0, 0,0,0},
    {1,0,1, 1,1,1, 0,1,1, 0,0,1},
    {0,0,0, 0,1,0, 1,1,0, 1,0,0},
};
Chunk::Chunk(){
    m_blocks.fill(BlockType::Air);
};
int Chunk::index(int x, int y, int z)const{
    return x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE;
}
BlockType Chunk::getBlock(int x, int y, int z) const {
    return m_blocks[index(x, y, z)];
}

void Chunk::setBlock(int x, int y, int z, BlockType blockType) {
    m_blocks[index(x, y, z)] = blockType;
}
glm::vec3 Chunk::getBlockColor(BlockType blockType) const {
    switch (blockType) {
        case BlockType::Dirt:
            return {0.545f, 0.271f, 0.075f};
        case BlockType::Grass:
            return {0.0f, 0.5f, 0.0f};
        case BlockType::Stone:
            return {0.5f, 0.5f, 0.5f};
        default:
            return {1.0f, 1.0f, 1.0f};
    }
}

void Chunk::generate(){
    for(int x = 0; x < Chunk::CHUNK_SIZE; ++x) {
        for (int y = 0; y < Chunk::CHUNK_SIZE; ++y) {
            for (int z = 0; z < Chunk::CHUNK_SIZE; ++z) {
                if (y == 0) {
                    setBlock(x, y, z, BlockType::Grass);
                } else if (y < 4) {
                    setBlock(x, y, z, BlockType::Dirt);
                } else if (y < 8) {
                    setBlock(x, y, z, BlockType::Stone);
                } else {
                    setBlock(x, y, z, BlockType::Air);
                }
            }
        }
    }
}
MeshData Chunk::buildMesh() const {
    MeshData result;
    for(int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) { 
                    if(getBlock(x, y, z) == BlockType::Air) {
                        continue;
                    }
                    for (int face = 0; face < 6; ++face) {
                    int nx = x + neighborOffsets[face][0];
                    int ny = y + neighborOffsets[face][1];
                    int nz = z + neighborOffsets[face][2];

                    bool neighborIsAir;
                    if (nx < 0 || nx >= CHUNK_SIZE || ny < 0 || ny >= CHUNK_SIZE || nz < 0 || nz >= CHUNK_SIZE) {
                        neighborIsAir = true;
                    } else {
                        neighborIsAir = (getBlock(nx, ny, nz) == BlockType::Air);
                    }

                    if (neighborIsAir) {
                        unsigned int base =result.vertices.size() / 6;
                        for (int corner = 0; corner < 4; ++corner) {
                            float ox = faceVertexOffsets[face][corner * 3 + 0];
                            float oy = faceVertexOffsets[face][corner * 3 + 1];
                            float oz = faceVertexOffsets[face][corner * 3 + 2];
                            result.vertices.push_back(x + ox);
                            result.vertices.push_back(y + oy);
                            result.vertices.push_back(z + oz);
                            glm::vec3 color = getBlockColor(getBlock(x, y, z));
                            result.vertices.push_back(color.r);
                            result.vertices.push_back(color.g);
                            result.vertices.push_back(color.b);
                        }
                        result.indices.push_back(base + 0);
                        result.indices.push_back(base + 1);
                        result.indices.push_back(base + 2);
                        result.indices.push_back(base + 2);
                        result.indices.push_back(base + 3);
                        result.indices.push_back(base + 0);
                        
                }
            }
        }
    }
}
    return result;
}
