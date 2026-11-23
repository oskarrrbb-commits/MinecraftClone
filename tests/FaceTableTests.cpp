#include <gtest/gtest.h>
#include "../src/world/Chunk.h"
#include <glm/glm.hpp>

TEST(FaceTableTests, EveryTriangleFacesOutward) {
    Chunk chunk;
    chunk.setBlock(5, 5, 5, BlockType::Dirt);
    MeshData mesh = chunk.buildMesh(ChunkNeighbors{});
    for(size_t i = 0; i < mesh.indices.size(); i += 3) {
        size_t ia = mesh.indices[i];
        size_t ib = mesh.indices[i + 1];
        size_t ic = mesh.indices[i + 2];
        glm::vec3 a(mesh.vertices[ia * 6], mesh.vertices[ia * 6 + 1], mesh.vertices[ia * 6 + 2]);
        glm::vec3 b(mesh.vertices[ib * 6], mesh.vertices[ib * 6 + 1], mesh.vertices[ib * 6 + 2]);
        glm::vec3 c(mesh.vertices[ic * 6], mesh.vertices[ic * 6 + 1], mesh.vertices[ic * 6 + 2]);
        glm::vec3 normal = glm::cross(b - a, c - a);
        glm::vec3 outward = (a + b + c) / 3.0f - glm::vec3(5.5f, 5.5f, 5.5f);
        EXPECT_GT(glm::dot(normal, outward), 0.0f)<< "triangle: " << i / 3 << " is facing inward";
    }
    
}