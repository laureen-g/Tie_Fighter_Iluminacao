#include "Sphere.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>


Sphere::Sphere(glm::vec3 pos, float radius, int sectors, int stacks)
    : Object(pos, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)) {
    init(radius, sectors, stacks);
}

Sphere::Sphere(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float radius, int sectors, int stacks)
    : Object(pos,rot,scl) {
    init(radius, sectors, stacks);
}

void Sphere::init(float radius, int sectors, int stacks) {
    vertices.clear();
    indices.clear();

    float sectorStep = 2.0f * M_PI / sectors;
    float stackStep  = M_PI / stacks;

    // VERTICES
    for (int i = 0; i <= stacks; ++i) {

        float stackAngle = M_PI / 2.0f - i * stackStep;
        float xy = radius * cosf(stackAngle);
        float y  = radius * sinf(stackAngle);

        for (int j = 0; j <= sectors; ++j) {

            float sectorAngle = j * sectorStep;

            float x = xy * cosf(sectorAngle);
            float z = xy * sinf(sectorAngle);

            // UV mapeamento longitude/latitude
            float u = 1.0f - (float)j / sectors;
            float v = 1.0f - (float)i / stacks;

            // normal = posição normalizada (esfera perfeita)
            float nx = x / radius;
            float ny = y / radius;
            float nz = z / radius;

            // adiciona 8 floats: pos(3), tex(2), normal(3)
            vertices.insert(vertices.end(), {
                x, y, z,
                u, v,
                nx, ny, nz
            });
        }
    }

    // INDICES
    for (int i = 0; i < stacks; ++i) {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {

            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != stacks - 1) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    // posição (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texcoords (location 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // normais (location 3)
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

void Sphere::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

