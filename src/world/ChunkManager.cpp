#include <map>
#include <memory>
#include "ChunkManager.h"

void ChunkManager::generateChunk(int x, int z) {
    ChunkCoord coord{x, z};
    if (m_chunks.find(coord) == m_chunks.end()) {
        auto newChunk = std::make_unique<Chunk>();
        newChunk->generate();
        m_chunks[coord] = std::move(newChunk);
    }
}
Chunk* ChunkManager::getChunk(int x, int z){
    ChunkCoord coord{x, z};
    auto it = m_chunks.find(coord);
    if (it == m_chunks.end()) {
        return nullptr;
    }
    return it->second.get();
}