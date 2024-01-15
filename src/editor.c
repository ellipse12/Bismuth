#include "editor.h"
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
static bool shouldExit = false;

void start() {
	GLFWwindow* handle = create_window("test", 1000, 476);
	render_init();
	
	while (!glfwWindowShouldClose(handle)) {
		
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		render(handle);
		glfwSwapBuffers(handle);
		glfwPollEvents();
	}
}

