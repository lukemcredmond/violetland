#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../../system/utility/ImageUtility.h"

class Texture {
private:
	GLuint m_textureId;
	GLenum m_type;
	int m_width, m_height;
public:
	Texture(int width, int height, GLenum type, GLint filter);
	Texture(SDL_Surface *surface, GLenum type, GLint filter,
			bool takeCareOfSurface);
	const int getWidth();
	const int getHeight();
	const GLuint getTextureId();
	const GLenum getType();
	virtual ~Texture();
};

#endif /* TEXTURE_H_ */