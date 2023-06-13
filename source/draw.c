#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "draw.h"
#include "types.h"

extern precise_vector3_t camera;

void draw_triangle(precise_vector3_t a, precise_vector3_t b, precise_vector3_t c)
{
    double points[] = {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, NULL);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}