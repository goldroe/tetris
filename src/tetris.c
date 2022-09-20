/*
 * File: tetris.c
 * Author: Carlos Rivera
 */
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define HANDMADE_MATH_NO_SSE
#define HANDMADE_MATH_IMPLEMENTATION
#define HMM_PREFIX
#include <HandmadeMath.h>

typedef hmm_vec2 vec2;
typedef hmm_vec3 vec3;
typedef hmm_mat4 mat4;

#include <stdio.h>
#include <assert.h>
#define ASSERT assert

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


int get_file_size(FILE *fp) {
	fseek(fp, 0L, SEEK_END);
	int result = ftell(fp);
	rewind(fp);
	return result;
}

GLuint load_shaders(const char *vertex_path, const char *fragment_path) {
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	char *vertex_source = NULL;
	FILE *vertex_file = fopen(vertex_path, "rb");
	ASSERT(vertex_file);
	int vertex_size = get_file_size(vertex_file);
	vertex_source = malloc(vertex_size + 1);
	fread(vertex_source, 1, vertex_size, vertex_file);
	vertex_source[vertex_size] = 0;
	fclose(vertex_file);

	char *fragment_source = NULL;
	FILE *fragment_file = fopen(fragment_path, "rb");
	ASSERT(fragment_file);
	int fragment_size = get_file_size(fragment_file);
	fragment_source = malloc(fragment_size + 1);
	rewind(fragment_file);
	fread(fragment_source, 1, fragment_size, fragment_file);
	fragment_source[fragment_size] = 0;
	fclose(fragment_file);

	glShaderSource(vertex_shader, 1, &vertex_source, &vertex_size);
	glCompileShader(vertex_shader);

	GLint status;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
	if (!status) {
		GLsizei len = 0;
		GLchar message[1024];
		glGetShaderInfoLog(vertex_shader, 1024, &len, message);
		printf("VERTEX SHADER COMPILATION ERROR: %s\n", message);
	}

	glShaderSource(fragment_shader, 1, &fragment_source, &fragment_size);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
	if (!status) {
		GLsizei len = 0;
		GLchar message[1024];
		glGetShaderInfoLog(fragment_shader, 1024, &len, message);
		printf("FRAGMENT SHADER COMPILATION ERROR: %s\n", message);
	}

	GLuint program_id = glCreateProgram();

	glAttachShader(program_id, vertex_shader);
	glAttachShader(program_id, fragment_shader);
	glLinkProgram(program_id);

	glGetProgramiv(program_id, GL_LINK_STATUS, &status);
	if (!status) {
		GLsizei len = 0;
		GLchar message[1024];
		glGetProgramInfoLog(program_id, 1024, &len, message);
		printf("PROGRAM LINK ERROR: %s\n", message);
	}
	
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program_id;
}

vec2 get_window_size(GLFWwindow *window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return Vec2((float)width, (float)height);
}

void render_quad(vec2 pos, vec2 size, vec3 color) {

}

int main(int argc, char **argv) {
	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(1280, 720, "Tetris", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	GLuint shader = load_shaders("data/shaders/vertex.glsl", "data/shaders/fragment.glsl");

	float vertices[] = {
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
	};

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

	glBindVertexArray(0);
	glUseProgram(0);

	GLint proj_loc =  glGetUniformLocation(shader, "proj");
	GLint model_loc = glGetUniformLocation(shader, "model");
	GLint color_loc = glGetUniformLocation(shader, "color");
	

#define GRID_X 10
#define GRID_Y 18

	vec3 colors[GRID_X] = {
		(vec3){0.f, 0.f, 0.f},
		(vec3){0.f, 0.f, 1.f},
		(vec3){0.f, 1.f, 0.f},
		(vec3){0.f, 1.f, 1.f},
		(vec3){1.f, 0.f, 0.f},
		(vec3){1.f, 0.f, 1.f},
		(vec3){1.f, 1.f, 0.f},
		(vec3){1.f, 1.f, 1.f},
		(vec3){0.2f, 0.4f, 5.f},
	};

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		glUseProgram(shader);
		glBindVertexArray(vao);

		vec2 window_size = get_window_size(window);
		
		mat4 proj = Orthographic(0.f, (float)window_size.width, 0.f, (float)window_size.height, -1.0f, 1.0f);

		vec2 center = Vec2(window_size.width/2.f, window_size.height/2.f);
		vec2 block_size = Vec2(window_size.width/GRID_X, window_size.height/GRID_Y);

		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, (float *)&proj);

		for (int y = 0; y < GRID_Y; y++) {
			for (int x = 0; x < GRID_X; x++) {
				vec2 block_pos = {x * block_size.width, y * block_size.height};
				mat4 model = Translate((vec3){block_pos.x, block_pos.y, 0.f});
				mat4 scale = Scale((vec3){block_size.width, block_size.height, 1.f});
				model = MultiplyMat4(model, scale);

				vec3 color = colors[x];

				glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float *)&model);
				glUniform3fv(color_loc, 1, (float *)&color);

				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	return 0;
}
