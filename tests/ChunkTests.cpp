#include <gtest/gtest.h>
#include "../src/world/Chunk.h"

TEST(ChunkTests, EmptyChunkHasNoMesh) {
    Chunk chunk;
    MeshData mesh = chunk.buildMesh(ChunkNeighbors{});

    EXPECT_EQ(mesh.vertices.size(), 0u);
    EXPECT_EQ(mesh.indices.size(), 0u);
}
TEST(ChunkTests, SingleBlockHasSixFaces) {
    Chunk chunk;
    chunk.setBlock(5, 5, 5, BlockType::Dirt);
    MeshData mesh = chunk.buildMesh(ChunkNeighbors{});

    EXPECT_EQ(mesh.vertices.size(), 144u);
    EXPECT_EQ(mesh.indices.size(), 36u);
}
TEST(ChunkTests, BorderFaceHiddenBySolidNeighbor) {
    Chunk a;
    Chunk b;
    a.setBlock(15, 5, 5, BlockType::Dirt);
    b.setBlock(0, 5, 5, BlockType::Dirt);
    ChunkNeighbors neighbors;
    neighbors.posX = &b;
    MeshData mesh = a.buildMesh(neighbors);

    EXPECT_EQ(mesh.vertices.size(), 120u);
    EXPECT_EQ(mesh.indices.size(), 30u);
}
TEST(ChunkTests, SolidSlabHasOnlyOuterFaces) {
    Chunk chunk;
    for (int x = 0; x < Chunk::CHUNK_SIZE; ++x) {
        for (int y = 0; y < 8; ++y) {
            for (int z = 0; z < Chunk::CHUNK_SIZE; ++z) {
                chunk.setBlock(x, y, z, BlockType::Dirt);
            }
        }
    }
    MeshData mesh = chunk.buildMesh(ChunkNeighbors{});

    EXPECT_EQ(mesh.vertices.size(), 24576u);
    EXPECT_EQ(mesh.indices.size(), 6144u);
}
TEST(ChunkTests, MissingNeighborCountsAsAir) {
    Chunk a;
    a.setBlock(15, 5, 5, BlockType::Dirt);
    ChunkNeighbors neighbors;
    neighbors.posX = nullptr;
    MeshData mesh = a.buildMesh(neighbors);

    EXPECT_EQ(mesh.vertices.size(), 144u);
    EXPECT_EQ(mesh.indices.size(), 36u);
}