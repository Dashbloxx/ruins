#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "draw.h"
#include "types.h"

extern precise_vector3_t camera;

void draw_triangle(precise_vector3_t a, precise_vector3_t b, precise_vector3_t c, char *image_path)
{
    // Define texture coordinates for each vertex
    GLfloat texCoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f
    };

    // Define vertices of the triangle
    GLfloat vertices[] = {
        a.x, a.y, a.z,
        b.x, b.y, b.z,
        c.x, c.y, c.z
    };

    // Load and bind the texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image using STB Image
    int width, height, channels;
    unsigned char* image = stbi_load(image_path, &width, &height, &channels, 0);

    // Upload texture data
    if (image)
    {
        GLenum format = (channels == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    }
    else
    {
        fprintf(stderr, "Failed to load image to memory...\n");
    }

    // Free the image data
    stbi_image_free(image);

    // Enable texture coordinate array
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    // Enable vertex array
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    // Enable texture mapping
    glEnable(GL_TEXTURE_2D);

    // Render the triangle with the texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set the color to white
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Cleanup
    glBindTexture(GL_TEXTURE_2D, 0);  // Unbind the texture
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDeleteTextures(1, &textureID);  // Delete the texture
}