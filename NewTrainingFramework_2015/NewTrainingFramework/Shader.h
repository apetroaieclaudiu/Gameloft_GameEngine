#pragma once
#include "ShaderResource.h"
#include "../Utilities/utilities.h"

class Shader
{
	ShaderResource	*mr;
	GLuint			program;
public:
	GLint	positionAttribute;
	GLint	matrixUniform;
	GLint	textureUniform[8];
	GLint	uvAttribute;
	void			Load();
	void			setMr(ShaderResource *);
	GLuint			getId();
	Shader();
	~Shader();
};

