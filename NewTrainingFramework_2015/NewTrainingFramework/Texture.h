#pragma once
#include "TextureResource.h"
#include "../Utilities/utilities.h"

class Texture
{
	TextureResource		*tr;
	GLuint				id;
public:
	void	Load();
	void	setMr(TextureResource *);
	GLuint	getId();
	Texture();
	~Texture();
};