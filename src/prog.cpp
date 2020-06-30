#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

void shdLoad(const char* name, GLuint prog, GLenum type) {
	FILE* f;
	f = fopen(name, "r");
	if (!f) {
		printf("%s not found\n", name);
		exit(-1);
	}
	fseek(f, 0, SEEK_END);
	int sz = ftell(f) + 1;
	fseek(f, 0, SEEK_SET);
	char* src = new char[sz];
	src[sz-1] = 0;
	fread(src, 1, sz, f);
	fclose(f);
	GLuint shd = glCreateShader(type);
	glShaderSource(shd, 1, &src, 0);
	glCompileShader(shd);
	char log[512];
	glGetShaderInfoLog(shd, 512, 0, log);
	printf(log);
	delete src;
	glAttachShader(prog, shd);
	glDeleteShader(shd);
}

GLuint progGen(const char* v_name, const char* f_name, const char* g_name, const char* c_name) {
	GLuint prog = glCreateProgram();
	if (v_name) {
		printf("compiling vertex shader\n");
		shdLoad(v_name, prog, GL_VERTEX_SHADER);
	}
	if (f_name) {
		printf("compiling fragment shader\n");
		shdLoad(f_name, prog, GL_FRAGMENT_SHADER);
	}
	if (g_name) {
		printf("compiling geometry shader\n");
		shdLoad(g_name, prog, GL_GEOMETRY_SHADER);
	}
	if (c_name) {
		printf("compiling compute shader\n");
		shdLoad(c_name, prog, GL_COMPUTE_SHADER);
	}
	glLinkProgram(prog);
	char log[512];
	glGetProgramInfoLog(prog, 512, 0, log);
	return prog;
}
