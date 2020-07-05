#include <stdio.h>
#include <GL/glew.h>
#include "prog.h"
#include "txmap.h"


Txmap::Txmap(V2f ul, V2f br) {
	if (!s_count) {
		s_prog = progGen("txmap_vert.glsl", "txmap_frag.glsl"); 
		printf("Txmap: program generated\n");
	}
	s_count++;
	m_prog = s_prog;
	m_primitive = GL_TRIANGLES;
	m_vcount = 6;
	V2f vertices[] = {ul, br, {br.x, ul.y}, ul, br, {ul.x, br.y}};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
}

Txmap::~Txmap() {
	if (s_count == 1) {
		glDeleteProgram(s_prog);
		printf("Txmap: program deleted\n");
	}
	s_count--;
}
