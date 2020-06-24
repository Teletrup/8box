#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static GLuint vbo, v_pos, v_shd, f_shd, prog;

static GLfloat vertices[] = {-1, 1, 1, 1, 1, -1, -1, -1};

static const char* v_shd_src = ""
"#version 130\n"
"attribute vec2 pos;\n"
"void main() {\n"
"gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);\n"
"}";

static const char* f_shd_src = ""
"#version 130\n"
//"varying color_o;\n"
"void main() {\n"
"gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}";


void shitInit() {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	v_shd = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v_shd, 1, &v_shd_src, 0);
	glCompileShader(v_shd);
	char log_v[512];
	glGetShaderInfoLog(v_shd, 512, 0, log_v);
	printf(log_v);
	f_shd = glCreateShader(GL_FRAGMENT_SHADER);
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
	v_pos = glGetAttribLocation(prog, "pos");

}

void draw() {
	glClearColor(0, 0, 0.3, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glVertexAttribPointer(v_pos, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
	glEnableVertexAttribArray(v_pos);
	glUseProgram(prog);
	glDrawArrays(GL_QUADS, 0, 4);
}

int main() {
	glfwInit();
	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	GLFWwindow* window = glfwCreateWindow(vidmode->width, vidmode->height, "", 0, 0);
	glfwMakeContextCurrent(window);
	
	glewInit();
	shitInit();
	while (!glfwWindowShouldClose(window)) {
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}
