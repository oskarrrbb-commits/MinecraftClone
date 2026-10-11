#pragma once
#include <map>
#include <memory>
#include "Chunk.h"

struct ChunkCoord {
    int x, z;
    bool operator<(const ChunkCoord& other) const {
        if (x != other.x) return x < other.x;
        return z < other.z;
    }
};

class ChunkManager {
public:
    void generateChunk(int x, int z);
    Chunk* getChunk(int x, int z);

private:
    std::map<ChunkCoord, std::unique_ptr<Chunk>> m_chunks;
};