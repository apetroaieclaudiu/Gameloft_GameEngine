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
	char	*array_pixeli;
	GLint	width, height, bpp;
	GLuint	format;
	array_pixeli = LoadTGA((char*)("../" + tr->path).c_str(), &width, &height, &bpp);

	if (bpp == 24) {
		format = GL_RGB;
	}
	else {
		format = GL_RGBA;
	}

	if (strcmp(tr->type.c_str(),"3d") != 0)
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)array_pixeli);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		int NC = width / 4 * (bpp / 8);
		char *buff = new char[NC * height / 3];
		
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_CUBE_MAP, id);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		for (int i = 0; i < height / 3; i++)
			for (int j = 0; j < NC; j++)
			{
				buff[i* NC + j] = array_pixeli[i * width * bpp / 8 + (j + width / 4 * bpp / 8)];
			}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0,format, width/4, height/3, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)buff);
		
		for (int i = 0; i < height / 3; i++)
			for (int j = 0; j < NC; j++)
			{
				buff[i* NC + j] = array_pixeli[(i + height / 3) * width * bpp / 8 + j];
			}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)buff);
		
		for (int i = 0; i < height / 3; i++)
			for (int j = 0; j < NC; j++)
			{
				buff[i* NC + j] = array_pixeli[(i + height/3) * width * bpp / 8 + (j + width / 4 * bpp / 8)];
			}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)buff);
		
		for (int i = 0; i < height / 3; i++)
			for (int j = 0; j < NC; j++)
			{
				buff[i* NC + j] = array_pixeli[(i + height / 3) * width * bpp / 8 + (j + 2 * width / 4 * bpp / 8)];
			}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)buff);
		
		for (int i = 0; i < height / 3; i++)
			for (int j = 0; j < NC; j++)
			{
				buff[i* NC + j] = array_pixeli[(i + height / 3) * width * bpp / 8 + (j + 3 * width / 4 * bpp / 8)];
			}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)buff);
		
		for (int i = 0; i < height / 3; i++)
			for (int j = 0; j < NC; j++)
			{
				buff[i* NC + j] = array_pixeli[(i + 2 * height / 3) * width * bpp / 8 + (j + width / 4 * bpp / 8)];
			}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)buff);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}

GLuint		Texture::getId()
{
	return id;
}