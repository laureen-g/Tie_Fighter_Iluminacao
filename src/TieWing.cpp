#include "TieWing.h"

TieWing::TieWing(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
    : Object(pos, rot, scl) {
    init();
}
/*
void TieWing::init() {

    float vertices[] = {
        0.0f, 0.0f, -0.6f, 0.0f, 0.0f, // A 0
        0.0f, 0.5f, -0.3f, 0.0f, 1.0f, // C 1
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f, // G 2
        0.0f, 0.5f,  0.3f, 0.0f, 1.0f, // D 3
        0.0f, 0.0f,  0.6f, 0.0f, 1.0f, // B 4
        0.0f, -0.5f, 0.3f, 0.0f, 1.0f, // F 5
        0.0f, -0.5f, -0.3f, 0.0f, 1.0f, // E 6
        0.1f, 0.0f, -0.6f, 0.0f, 0.0f, // A1 7
        0.1f, 0.5f, -0.3f, 0.0f, 1.0f, // C1 8
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f, // G1 9
        0.1f, 0.5f,  0.3f, 0.0f, 1.0f, // D1 10
        0.1f, 0.0f,  0.6f, 0.0f, 1.0f, // B1 11
        0.1f, -0.5f, 0.3f, 0.0f, 1.0f, // F1 12
        0.1f, -0.5f, -0.3f, 0.0f, 1.0f // E1 13
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 4, 3,
        3, 4, 2, 4, 5, 2,
        5, 6, 2, 6, 0, 2,
        7, 8, 9, 8, 10, 9,
        10, 11, 9, 11, 12, 9,
        12, 13, 9, 13, 7, 9,

        0, 7, 8, 8, 1, 0,
        1, 8, 10, 10, 3, 1,
        3, 10, 11, 11, 4, 3,
        4,11, 12, 12, 5, 4,
        5, 12, 13, 13, 6, 5,
        6, 13, 7, 7, 0, 6
    };

    float vertices2[] = {
        0.0f, 0.0f, -0.6f, 0.0f, 0.0f, // A 1
        0.0f, 0.5f, -0.3f, 0.0f, 1.0f, // C 2
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f, // G 3

        0.0f, 0.5f, -0.3f, 0.0f, 0.0f, // C 2
        0.0f, 0.5f,  0.3f, 0.0f, 1.0f, // D 4
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f, // G 3

        0.0f, 0.5f,  0.3f, 0.0f, 0.0f, // D 4
        0.0f, 0.0f,  0.6f, 0.0f, 1.0f, // B 5
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f, // G 3

        0.0f, 0.0f,  0.6f, 0.0f, 0.0f, // B 5
        0.0f, -0.5f, 0.3f, 0.0f, 1.0f, // F 6
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f, // G 3

        0.0f, -0.5f,  0.3f, 0.0f, 0.0f, // F 6
        0.0f, -0.5f, -0.3f, 0.0f, 1.0f, // E 7
        0.0f, 0.0f,   0.0f, 1.0f, 1.0f, // G 3

        0.0f, -0.5f, -0.3f, 0.0f, 0.0f, // E 7
        0.0f, 0.0f, -0.6f,  0.0f, 1.0f, // A 1
        0.0f, 0.0f,   0.0f, 1.0f, 1.0f, // G 3
        //
        0.1f, 0.0f, -0.6f, 0.0f, 0.0f, // A1 8
        0.1f, 0.5f, -0.3f, 0.0f, 1.0f, // C1 9
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f, // G1 10

        0.1f, 0.5f, -0.3f, 0.0f, 0.0f, // C1 9
        0.1f, 0.5f,  0.3f, 0.0f, 1.0f, // D1 11
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f, // G1 10

        0.1f, 0.5f,  0.3f, 0.0f, 0.0f, // D1 11
        0.1f, 0.0f,  0.6f, 0.0f, 1.0f, // B1 12
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f, // G1 10

        0.1f, 0.0f,  0.6f, 0.0f, 0.0f, // B1 12
        0.1f, -0.5f, 0.3f, 0.0f, 1.0f, // F1 13
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f, // G1 10

        0.1f, -0.5f,  0.3f, 0.0f, 0.0f, // F1 13
        0.1f, -0.5f, -0.3f, 0.0f, 1.0f, // E1 14
        0.1f, 0.0f,   0.0f, 1.0f, 1.0f, // G1 10

        0.1f, -0.5f, -0.3f, 0.0f, 0.0f, // E1 14
        0.1f, 0.0f,  -0.6f, 0.0f, 1.0f, // A1 8
        0.1f, 0.0f,   0.0f, 1.0f, 1.0f, // G1 10

        0.0f, 0.0f, -0.6f, 1.0f, 1.0f, // A 1
        0.1f, 0.0f, -0.6f, 1.0f, 0.0f, // A1 8
        0.1f, 0.5f, -0.3f, 0.0f, 0.0f, // C1 9
        0.1f, 0.5f, -0.3f, 1.0f, 1.0f, // C1 9
        0.0f, 0.5f, -0.3f, 1.0f, 0.0f, // C 2
        0.0f, 0.0f, -0.6f, 0.0f, 0.0f, // A 1

        0.0f, 0.5f, -0.3f, 1.0f, 1.0f, // C 2
        0.1f, 0.5f, -0.3f, 1.0f, 0.0f, // C1 9
        0.1f, 0.5f,  0.3f, 0.0f, 0.0f, // D1 11
        0.1f, 0.5f,  0.3f, 1.0f, 1.0f, // D1 11
        0.0f, 0.5f,  0.3f, 1.0f, 0.0f, // D 4
        0.0f, 0.5f, -0.3f, 0.0f, 0.0f, // C 2

        0.0f, 0.5f,  0.3f, 1.0f, 1.0f, // D 4
        0.1f, 0.5f,  0.3f, 1.0f, 0.0f, // D1 11
        0.1f, 0.0f,  0.6f, 0.0f, 0.0f, // B1 12
        0.1f, 0.0f,  0.6f, 1.0f, 1.0f, // B1 12
        0.0f, 0.0f,  0.6f, 1.0f, 0.0f, // B 5
        0.0f, 0.5f,  0.3f, 0.0f, 0.0f, // D 4

        0.0f, 0.0f,  0.6f, 1.0f, 1.0f, // B 5
        0.1f, 0.0f,  0.6f, 1.0f, 0.0f, // B1 12
        0.1f, -0.5f, 0.3f, 0.0f, 0.0f, // F1 13
        0.1f, -0.5f, 0.3f, 1.0f, 1.0f, // F1 13
        0.0f, -0.5f, 0.3f, 1.0f, 0.0f, // F 6
        0.0f, 0.0f,  0.6f, 0.0f, 0.0f, // B 5

        0.0f, -0.5f, 0.3f,  1.0f, 0.0f, // F 6
        0.1f, -0.5f, 0.3f,  1.0f, 1.0f, // F1 13
        0.1f, -0.5f, -0.3f, 0.0f, 1.0f, // E1 14
        0.1f, -0.5f, -0.3f, 0.0f, 1.0f, // E1 14
        0.0f, -0.5f, -0.3f, 0.0f, 1.0f, // E 7
        0.0f, -0.5f, 0.3f,  1.0f, 0.0f, // F 6

        0.0f, -0.5f, -0.3f, 1.0f, 1.0f, // E 7
        0.1f, -0.5f, -0.3f, 1.0f, 0.0f, // E1 14
        0.1f, 0.0f, -0.6f,  0.0f, 0.0f, // A1 8
        0.1f, 0.0f, -0.6f,  1.0f, 1.0f, // A1 8
        0.0f, 0.0f, -0.6f,  1.0f, 0.0f, // A 1
        0.0f, -0.5f, -0.3f, 0.0f, 0.0f  // E 7
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // tex coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}
*/

void TieWing::init() {

    float vertices[] = {
        // x, y, z,       u, v,      nx, ny, nz

        // ----- LADO ESQUERDO (normal -X)
        0.0f, 0.0f, -0.6f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        0.0f, 0.5f, -0.3f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,

        0.0f, 0.5f, -0.3f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        0.0f, 0.5f,  0.3f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,

        0.0f, 0.5f,  0.3f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f,  0.6f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,

        0.0f, 0.0f,  0.6f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.3f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,

        0.0f, -0.5f,  0.3f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, -0.5f, -0.3f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f,   0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

        0.0f, -0.5f, -0.3f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -0.6f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f,   0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,


        // ----- LADO DIREITO (normal +X)
        0.1f, 0.0f, -0.6f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        0.1f, 0.5f, -0.3f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,

        0.1f, 0.5f, -0.3f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        0.1f, 0.5f,  0.3f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,

        0.1f, 0.5f,  0.3f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        0.1f, 0.0f,  0.6f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,

        0.1f, 0.0f,  0.6f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        0.1f, -0.5f, 0.3f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,

        0.1f, -0.5f, 0.3f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        0.1f, -0.5f, -0.3f,0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,

        0.1f, -0.5f, -0.3f,0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        0.1f, 0.0f, -0.6f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ---- POSITION (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ---- TEXCOORD (location 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // ---- NORMAL (location 3)
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

void TieWing::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 72);
    glBindVertexArray(0);
}
