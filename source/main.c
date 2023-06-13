#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"

/** @brief The width & height of the screen. */
int g_width = 800, g_height = 600; 

/** @brief The camera position & rotation of the current client. */
precise_vector3_t g_camera_position = {0.0, 0.0, 0.0}, g_camera_rotation = {0.0, 0.0, 0.0};

/** @brief Initial camera angle. */
float camera_angle = 0.0f;

/**
 *  @brief Load a file into RAM, and return pointer to it.
 *  @param filename The path to the file that shall be loaded.
 *  @warning This function assumes that the RAM usage isn't full.
 */
static char* load_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, length, file);
    if (bytes_read != length) {
        fclose(file);
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

/** @brief The main function, which is the entry point for our program. */
int main() {
    /* Initialize GLFW, and if it fails, just exit the program with exit code -1. */
	if(!glfwInit()) {
		return -1;
	}

    /* Attempt to create a window using GLFW, and then test if it succeded or not. */
	GLFWwindow *window = glfwCreateWindow(g_width, g_height, "Ruins", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}

    /* Set the current GLFW window to our window which was just created. */
	glfwMakeContextCurrent(window);

    /* Attempt to initialize GLEW, and if it doesn't return GLEW_OK, then exit the program with exit code -1. */
	if(glewInit() != GLEW_OK) {
		return -1;
	}

	glViewport(0, 0, g_width, g_height);

    glEnable(GL_DEPTH_TEST);

    /**
     *  @brief Load shader(s), compile them, link them to a single binary, and then use them.
     *
     *  @note All shaders are located in a subdirectory named `shaders`.
     */
	const char* vertex_shader_source = load_file("../shaders/vertex_shader.glsl");
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

	const char* fragment_shader_source = load_file("../shaders/fragment_shader.glsl");
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

	GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glUseProgram(shader_program);

    /**
     *  @brief Set up vertex atribute pointer & enable vertex attribute at index 0.
     */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    /**
     *  @brief Loop that renders objects.
     *
     *  @note Here we place functions useful for drawing to screen.
     */
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        draw_triangle((precise_vector3_t){-0.5, -0.5, 0.0}, (precise_vector3_t){0.5, -0.5, 0.0}, (precise_vector3_t){0.0,  0.5, 0.0});
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    /** @brief Delete the shader program & terminate GLFW, aswell as returning exit code 0. */
    glDeleteProgram(shader_program);
	glfwTerminate();

	return 0;
}
