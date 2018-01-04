#include "stdafx.h"
#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
}

void	Texture::setMr(TextureResource *t)
{
	tr = t;
}

void	Texture::Load()
{
	char *array_pixeli;
	GLint		width, height, bpp;
	GLuint	format;
	array_pixeli = LoadTGA((char*)("../" + tr->path).c_str(), &width, &height, &bpp);

	if (bpp == 24) {
		format = GL_RGB;
	}
	else {
		format = GL_RGBA;
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)array_pixeli);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint		Texture::getId()
{
	return id;
}