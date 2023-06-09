#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "render.h"
#include "draw.h"
#include "types.h"

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_cube((integer_vector3_t){0, 0, 0});
}