#include <GL/glew.h>
#include "drawable.h"

Drawable::Drawable() {
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

Drawable::~Drawable() {
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void Drawable::draw() {
	glBindVertexArray(m_vao);
	glUseProgram(m_prog);
	glDrawArrays(m_primitive, 0, m_vcount);
}


