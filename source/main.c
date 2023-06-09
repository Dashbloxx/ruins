#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "render.h"

int g_width = 800, g_height = 600;

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

int main() {
	if(!glfwInit()) {
		return -1;
	}

	GLFWwindow *window = glfwCreateWindow(g_width, g_height, "Ruins", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if(glewInit() != GLEW_OK) {
		return -1;
	}

	glViewport(0, 0, g_width, g_height);

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

	while(!glfwWindowShouldClose(window)) {
		render();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    glDeleteProgram(shader_program);

	glfwTerminate();

	return 0;
}
