#include "HexagonalPrism.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

HexagonalPrism::HexagonalPrism(glm::vec3 pos, float radiusTop, float radiusBottom, float height, float angle)
    : Hexagon(pos, radiusTop, height, angle), angle(angle) {
    init(radiusTop, radiusBottom, height);
}

HexagonalPrism::HexagonalPrism(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl,
                               float radiusTop, float radiusBottom, float height, float angle)
    : Hexagon(pos, rot, scl, radiusTop, height, angle), angle(angle) {
    init(radiusTop, radiusBottom, height);
}
/*
void HexagonalPrism::init(float radiusTop, float radiusBottom, float height) {

    vertices.clear();
    indices.clear();

    int segments = 6;
    float halfH = height / 2.0f;
    float step = 2.0f * M_PI / segments;

    // --- TOPO ---
    vertices.insert(vertices.end(), {0.0f, halfH, 0.0f, 0.5f, 0.5f});
    int topCenterIndex = 0;

    for (int i = 0; i <= segments; i++) {
        float theta = i * step;
        float x = radiusTop * cos(theta);
        float z = radiusTop * sin(theta);
        float u = (cos(theta) + 1.0f) * 0.5f;
        float v = (sin(theta) + 1.0f) * 0.5f;
        vertices.insert(vertices.end(), {x, halfH, z, u, v});
    }

    // --- BASE ---
    int baseCenterIndex = (int)vertices.size() / 5;
    vertices.insert(vertices.end(), {0.0f, -halfH, 0.0f, 0.5f, 0.5f});

    for (int i = 0; i <= segments; i++) {
        float theta = i * step;
        float x = radiusBottom * cos(theta);
        float z = radiusBottom * sin(theta);
        float u = (cos(theta) + 1.0f) * 0.5f;
        float v = (sin(theta) + 1.0f) * 0.5f;
        vertices.insert(vertices.end(), {x, -halfH, z, u, v});
    }

    // --- LATERAIS ---
    int sideStartIndex = (int)vertices.size() / 5;
    for (int i = 0; i <= segments; i++) {
        float theta = i * step;
        float xt = radiusTop * cos(theta);
        float zt = radiusTop * sin(theta);
        float xb = radiusBottom * cos(theta);
        float zb = radiusBottom * sin(theta);
        float u = 1.0f - (float)i / segments;

        vertices.insert(vertices.end(), {xt, halfH, zt, u, 1.0f});
        vertices.insert(vertices.end(), {xb, -halfH, zb, u, 0.0f});
    }

    // --- ÍNDICES ---
    // topo
    for (int i = 1; i <= segments; i++) {
        indices.push_back(topCenterIndex);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    // base
    for (int i = 1; i <= segments; i++) {
        indices.push_back(baseCenterIndex);
        indices.push_back(baseCenterIndex + i + 1);
        indices.push_back(baseCenterIndex + i);
    }

    // laterais
    for (int i = 0; i < segments; i++) {
        int top1 = sideStartIndex + i * 2;
        int bot1 = top1 + 1;
        int top2 = top1 + 2;
        int bot2 = bot1 + 2;

        indices.push_back(top1);
        indices.push_back(bot1);
        indices.push_back(top2);

        indices.push_back(top2);
        indices.push_back(bot1);
        indices.push_back(bot2);
    }

    // --- BUFFERS ---
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}*/

void HexagonalPrism::init(float radiusTop, float radiusBottom, float height) {

    vertices.clear();
    indices.clear();

    int segments = 6;
    float halfH = height * 0.5f;
    float step = 2.0f * M_PI / segments;

    auto addVertex = [&](float x, float y, float z, float u, float v,
                         float nx, float ny, float nz) {
        vertices.insert(vertices.end(), {x, y, z, u, v, nx, ny, nz});
    };

    // ============================
    // TOPO  (normal +Y)
    // ============================
    int topCenterIndex = vertices.size() / 8;
    addVertex(0, halfH, 0, 0.5f, 0.5f, 0, 1, 0);

    for (int i = 0; i <= segments; i++) {
        float theta = i * step;
        float x = radiusTop * cos(theta);
        float z = radiusTop * sin(theta);
        float u = (cos(theta) + 1.f) * 0.5f;
        float v = (sin(theta) + 1.f) * 0.5f;

        addVertex(x, halfH, z, u, v, 0, 1, 0);
    }

    // ============================
    // BASE (normal -Y)
    // ============================
    int baseCenterIndex = vertices.size() / 8;
    addVertex(0, -halfH, 0, 0.5f, 0.5f, 0, -1, 0);

    for (int i = 0; i <= segments; i++) {
        float theta = i * step;
        float x = radiusBottom * cos(theta);
        float z = radiusBottom * sin(theta);
        float u = (cos(theta) + 1.f) * 0.5f;
        float v = (sin(theta) + 1.f) * 0.5f;

        addVertex(x, -halfH, z, u, v, 0, -1, 0);
    }

    // ============================
    // LATERAIS
    // normais calculadas com cross-product
    // ============================
    int sideStartIndex = vertices.size() / 8;

    for (int i = 0; i <= segments; i++) {
        float theta = i * step;

        float xt = radiusTop * cos(theta);
        float zt = radiusTop * sin(theta);

        float xb = radiusBottom * cos(theta);
        float zb = radiusBottom * sin(theta);

        float u = 1.0f - float(i) / segments;

        // Calcula normal da lateral
        glm::vec3 top(xt, halfH, zt);
        glm::vec3 bot(xb, -halfH, zb);

        glm::vec3 up = top - bot;
        glm::vec3 radial(xt, 0, zt);

        glm::vec3 normal = glm::normalize(glm::cross(radial, up));

        addVertex(xt, halfH, zt, u, 1, normal.x, normal.y, normal.z);
        addVertex(xb, -halfH, zb, u, 0, normal.x, normal.y, normal.z);
    }

    // ============================
    // ÍNDICES
    // ============================

    // topo
    for (int i = 1; i <= segments; i++) {
        indices.push_back(topCenterIndex);
        indices.push_back(topCenterIndex + i);
        indices.push_back(topCenterIndex + i + 1);
    }

    // base
    for (int i = 1; i <= segments; i++) {
        indices.push_back(baseCenterIndex);
        indices.push_back(baseCenterIndex + i + 1);
        indices.push_back(baseCenterIndex + i);
    }

    // laterais
    for (int i = 0; i < segments; i++) {
        int t1 = sideStartIndex + i * 2;
        int b1 = t1 + 1;
        int t2 = t1 + 2;
        int b2 = b1 + 2;

        indices.push_back(t1);
        indices.push_back(b1);
        indices.push_back(t2);

        indices.push_back(t2);
        indices.push_back(b1);
        indices.push_back(b2);
    }

    // ============================
    // BUFFERS
    // ============================

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // posição (layout 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // UVs (layout 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // normais (layout 3)
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}
