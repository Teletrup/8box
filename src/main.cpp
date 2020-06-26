#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Drawable {
	GLuint vao, vbo, prog;
	public:
	Drawable();
	~Drawable() {}
	void draw();
};


static GLfloat vertices[] = {-1, 1, 1, 1, 1, -1, -1, -1};

static const char* v_shd_src = ""
"#version 420 core\n"
"layout(location = 0) in vec2 pos;\n"
"void main() {\n"
"gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);\n"
"}";

static const char* f_shd_src = ""
"#version 420 core\n"
"out vec4 color;\n"
"void main() {\n"
"color = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}";



Drawable::Drawable() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint v_shd = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v_shd, 1, &v_shd_src, 0);
	glCompileShader(v_shd);
	char log_v[512];
	glGetShaderInfoLog(v_shd, 512, 0, log_v);
	printf(log_v);

	GLuint f_shd = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f_shd, 1, &f_shd_src, 0);
	glCompileShader(f_shd);
	char log_f[512];
	glGetShaderInfoLog(f_shd, 512, 0, log_f);
	printf(log_f);

	prog = glCreateProgram();
	glAttachShader(prog, v_shd);
	glAttachShader(prog, f_shd);
	glLinkProgram(prog);
	char log_p[512];
	glGetProgramInfoLog(prog, 512, 0, log_p);
	printf(log_p);

	glDeleteShader(v_shd);
	glDeleteShader(f_shd);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
}

void Drawable::draw() {
	glBindVertexArray(vao);
	glUseProgram(prog);
	glDrawArrays(GL_TRIANGLES, 0, 3);
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

	Drawable drw;

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0, 0, 0.3, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		drw.draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
