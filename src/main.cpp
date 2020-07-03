#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "prog.h"
#include "txmap.h"


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	GLFWwindow* window = glfwCreateWindow(vidmode->width, vidmode->height, "", 0, 0);
	glfwMakeContextCurrent(window);
	
	glewInit();

	Txmap a({0, 0}, {1, -1});
	Txmap b({-0.5, 0.5}, {0, 0});
	Txmap c({-0.3, -0.3}, {-0.1, -0.6});

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0, 0, 0.3, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		a.draw();
		b.draw();
		c.draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
