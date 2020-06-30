#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "prog.h"

struct V2f {
	float x, y;
};

class Drawable {
	protected:
	GLuint vao, vbo, prog, vcount;
	GLenum primitive;
	public:
	Drawable();
	~Drawable() {}
	void draw();
};

class Txmap : public Drawable {
	public:
	Txmap();	
};

Drawable::Drawable() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Drawable::draw() {
	glBindVertexArray(vao);
	glUseProgram(prog);
	glDrawArrays(primitive, 0, vcount);
}

Txmap::Txmap() {
	primitive = GL_TRIANGLES;
	vcount = 6;
	V2f vertices[] = {{-1, 1}, {1, 1}, {1, -1}, {1, -1}, {-1, -1}, {-1, 1}};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	prog = progGen("vert.glsl", "frag.glsl");
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	GLFWwindow* window = glfwCreateWindow(vidmode->width, vidmode->height, "", 0, 0);
	glfwMakeContextCurrent(window);
	
	glewInit();

	Txmap drw;

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0, 0, 0.3, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		drw.draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
