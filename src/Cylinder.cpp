#include "Cylinder.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Cylinder::Cylinder(glm::vec3 pos, float radius, float height, int segments, float ang)
    :Object(pos, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), angle(ang){
    //: position(pos), rotation(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f, 1.0f, 1.0f)), angle(ang){
    init(radius, height, segments);
}

Cylinder::Cylinder(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float radius, float height, int segments, float ang)
    : Object(pos, rot, scl), angle(ang)  {
    init(radius, height, segments);
}

void Cylinder::init(float radius, float height, int segments) {
    vertices.clear();
    indices.clear();

    float halfH = height / 2.0f;
    float step = 2.0f * M_PI / segments;

    // ---------------------------
    //     TOPO
    // ---------------------------
    // centro do topo
    vertices.insert(vertices.end(), {
        0.0f, halfH, 0.0f,          // posição
        0.5f, 0.5f,                 // tex
        0.0f, 1.0f, 0.0f            // normal
    });

    int topCenterIndex = 0;
    int indexCount = 1;

    for (int i = 0; i <= segments; i++) {
        float theta = i * step;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        float u = (cos(theta) + 1.0f) * 0.5f;
        float v = (sin(theta) + 1.0f) * 0.5f;

        vertices.insert(vertices.end(), {
            x, halfH, z,     // pos
            u, v,            // tex
            0.0f, 1.0f, 0.0f // normal topo
        });
        indexCount++;
    }

    // ---------------------------
    //     BASE
    // ---------------------------
    int baseCenterIndex = indexCount;

    vertices.insert(vertices.end(), {
        0.0f, -halfH, 0.0f,
        0.5f, 0.5f,
        0.0f, -1.0f, 0.0f
    });

    indexCount++;

    for (int i = 0; i <= segments; i++) {
        float theta = i * step;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        float u = (cos(theta) + 1.0f) * 0.5f;
        float v = (sin(theta) + 1.0f) * 0.5f;

        vertices.insert(vertices.end(), {
            x, -halfH, z,
            u, v,
            0.0f, -1.0f, 0.0f
        });

        indexCount++;
    }

    // ---------------------------
    //     LATERAL
    // ---------------------------
    int sideStartIndex = indexCount;

    for (int i = 0; i <= segments; i++) {
        float theta = i * step;
        float x = radius * cos(theta);
        float z = radius * sin(theta);

        float u = 1.0f - (float)i / segments;

        // normal radial (x,z normalizado)
        float nx = cos(theta);
        float nz = sin(theta);

        // topo lateral
        vertices.insert(vertices.end(), {
            x, halfH, z,
            u, 1.0f,
            nx, 0.0f, nz
        });

        // base lateral
        vertices.insert(vertices.end(), {
            x, -halfH, z,
            u, 0.0f,
            nx, 0.0f, nz
        });

        indexCount += 2;
    }

    // ---------------------------
    //     ÍNDICES
    // ---------------------------
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

    // lateral
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

    // ---------------------------
    //     OPENGL BUFFERS
    // ---------------------------
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // posição
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texcoords —> location 2
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(2);

    // normal —> location 3
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}


void Cylinder::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(angle), rotation);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
