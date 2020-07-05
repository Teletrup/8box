#ifndef DRAWABLE_H
#define DRAWABLE_H

struct V2f {
	float x, y;
};

class Drawable {
	protected:
	GLuint m_vao, m_vbo, m_prog, m_vcount;
	GLenum m_primitive;
	public:
	Drawable();
	~Drawable();
	void draw();
};

#endif
