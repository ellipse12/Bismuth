#include "renderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <stdio.h>
#include <stdlib.h>
#include "texture.h"
#include "shader.h"
#include "widget.h"
#include "math.h"

void init_glfw() {
	if (!glfwInit()) {
		perror("Failed to initialize glfw");
		exit(-1);
	}
}

void init_glew() {
	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		perror("Failed to initialize OpenGL");
		exit(-1);
	}
}


void getWindowSize(GLFWwindow* window, ivec2 window_size) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	window_size[0] = width;
	window_size[1] = height;
}
static Widget widget = { 0 };
static Model model = { 0 };
static Texture texture = { 0 };
static Shader shader = { 0 };
void render_init() {
	init_shader(&shader, "vertex_shader.vert", "fragment_shader.frag");
	create_model_for_widget(&model, &texture, "test.png");
	create_widget(&widget, (vec2) { 0, 0 }, (vec2) { 1, 1 }, &model);
}

void render(GLFWwindow* window) {
	ivec2 win_size;
	getWindowSize(window, win_size);
	shader_bind(&shader);
	glBindVertexArray(widget.model->vao_id);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, widget.model->texture->texture_id);

	
	float scaleX = (float)widget.model->texture->width / (float)win_size[0];
	scaleX *= widget.scale[0];
	float scaleY = (float)widget.model->texture->height / (float)win_size[1];
	scaleY *= widget.scale[1];
	mat4 transform;
	create_transformation_matrix(transform, widget.position, (vec2){scaleX, scaleY});
	glUniformMatrix4fv(get_uniform_location(&shader, "transformation"),  1, false, transform);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, widget.model->vertex_count);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
	shader_release();

}



void resize_window_callback(GLFWwindow* window, ui32 width, ui32 height) {
	glViewport(0, 0, width, height);
}


GLFWwindow* create_window(const char* title, ui32 width, ui32 height) {
	init_glfw();
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow *handle = glfwCreateWindow(width, height, title, NULL, NULL);
	if (handle == NULL) {
		perror("Could not create GLFW window");
		glfwTerminate();
		exit(-1);
		
	}

	glfwSetWindowSizeCallback(handle, resize_window_callback);

	glfwMakeContextCurrent(handle);
	
	init_glew();


	glfwSwapInterval(1);
	glfwShowWindow(handle);


	return handle;

}

