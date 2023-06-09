#include <GLFW/glfw3.h>

#include "draw.h"
#include "types.h"

void draw_cube(integer_vector3_t position)
{
    GLdouble vertices[] = {
        -0.5 + position.x, -0.5 + position.y, 0.5 + position.z,
        0.5 + position.x, -0.5 + position.y, 0.5 + position.z,
        0.5 + position.x, 0.5 + position.y, 0.5 + position.z,
        -0.5 + position.x, 0.5 + position.y, 0.5 + position.z,
        -0.5 + position.x, -0.5 + position.y, -0.5 + position.z,
        0.5 + position.x, -0.5 + position.y, -0.5 + position.z,
        0.5 + position.x, 0.5 + position.y, -0.5 + position.z,
        -0.5 + position.x, 0.5 + position.y, -0.5 + position.z
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,
        1, 5, 6,
        6, 2, 1,
        7, 6, 5,
        5, 4, 7,
        4, 0, 3,
        3, 7, 4,
        4, 5, 1,
        1, 0, 4,
        3, 2, 6,
        6, 7, 3
    };

    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
}
