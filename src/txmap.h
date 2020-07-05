#ifndef TXMAP_H
#define TXMAP_H

#include "drawable.h"

class Txmap : public Drawable {
	inline static GLuint s_prog;
	inline static int s_count;
	GLuint m_texture;
	public:
	Txmap(V2f ul, V2f br);
	~Txmap();
};

#endif
