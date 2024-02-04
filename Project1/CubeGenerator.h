#ifndef CUBEGENERATOR_H
#define CUBEGENERATOR_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

// Function prototype
void CreateCube(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, glm::vec3 size, glm::vec3 position);

// Implementation
void CreateCube(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, glm::vec3 size, glm::vec3 position) {
    // Unit cube vertices centered at origin
    GLfloat unitVertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
    };

    // Unit cube indices
    GLuint unitIndices[] = {
        0, 1, 2, 2, 3, 0,
        1, 5, 6, 6, 2, 1,
        7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4,
        4, 5, 1, 1, 0, 4,
        3, 2, 6, 6, 7, 3,
    };

    vertices.clear();
    indices.clear();

    // Scale and translate unit cube vertices based on size and position
    for (int i = 0; i < 24; i += 3) {
        vertices.push_back(unitVertices[i] * size.x + position.x);
        vertices.push_back(unitVertices[i + 1] * size.y + position.y);
        vertices.push_back(unitVertices[i + 2] * size.z + position.z);
    }

    for (int i = 0; i < 36; i++) {
        indices.push_back(unitIndices[i]);
    }
}

#endif // CUBEGENERATOR_H
