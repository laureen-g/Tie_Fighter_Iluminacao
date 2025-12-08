#ifndef HEXPRISM_H
#define HEXPRISM_H

#include <vector>
#include <cmath>

class HexPrism {
public:
    unsigned int VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    //HexPrism() {}

    HexPrism(float radius = 0.5f, float height = 1.0f) {
        generateHexPrism(radius, height);
        setupBuffers();
    }

    void draw(Shader &shader, glm::mat4 model) {
        model = glm::translate(model, position);
        model = glm::scale(model, scale);

        shader.setMat4("model", model);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

private:
    void generateHexPrism(float radius, float height) {
        vertices.clear();
        indices.clear();

        float halfHeight = height / 2.0f;

        // --- Gerar vértices do hexágono superior e inferior ---
        for (int k = 0; k < 2; k++) { // 0 = inferior, 1 = superior
            float y = (k == 0 ? -halfHeight : halfHeight);
            for (int i = 0; i < 6; i++) {
                float angle = (float)i / 6.0f * 2.0f * M_PI;
                float x = radius * cos(angle);
                float z = radius * sin(angle);

                // posição
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                //// normal aproximada (apontando para fora no eixo radial)
                //vertices.push_back(cos(angle));
                //vertices.push_back(0.0f);
                //vertices.push_back(sin(angle));

                // coordenadas de textura (simples mapeamento planar)
                vertices.push_back((cos(angle) + 1.0f) * 0.5f);
                vertices.push_back((sin(angle) + 1.0f) * 0.5f);
            }
        }

        // Centro do topo e base (para os triângulos das tampas)
        vertices.insert(vertices.end(), {0.0f, -halfHeight, 0.0f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f}); // centro base
        vertices.insert(vertices.end(), {0.0f,  halfHeight, 0.0f, 0.0f,  1.0f, 0.0f, 0.5f, 0.5f}); // centro topo

        int baseCenterIndex = 12;
        int topCenterIndex  = 13;

        // --- Índices das tampas (bases hexagonais) ---
        for (int i = 0; i < 6; i++) {
            int next = (i + 1) % 6;
            // base inferior
            indices.push_back(baseCenterIndex);
            indices.push_back(i);
            indices.push_back(next);

            // base superior
            indices.push_back(topCenterIndex);
            indices.push_back(6 + next);
            indices.push_back(6 + i);
        }

        // --- Índices das laterais ---
        for (int i = 0; i < 6; i++) {
            int next = (i + 1) % 6;

            int i0 = i;
            int i1 = next;
            int i2 = 6 + next;
            int i3 = 6 + i;

            // dois triângulos para cada lado
            indices.push_back(i0);
            indices.push_back(i1);
            indices.push_back(i2);

            indices.push_back(i0);
            indices.push_back(i2);
            indices.push_back(i3);
        }
    }

    void setupBuffers() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        /*
        // posição (3 floats)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // normal (3 floats)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // texcoords (2 floats)
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        */

        // posição (3 floats) + tex coords (2 floats)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }
};

#endif
