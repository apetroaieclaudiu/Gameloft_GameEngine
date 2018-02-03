#pragma once
#include "ShaderResource.h"
#include "../Utilities/utilities.h"

class Shader
{
	ShaderResource	*mr;
	GLuint			program;
public:
	GLint	heightUniform;
	GLint	positionAttribute;
	GLint	matrixUniform;
	GLint	textureUniform[8];
	GLint	uvAttribute;
	GLint	uvBlendAttribute;
	void			Load();
	void			setMr(ShaderResource *);
	GLuint			getId();
	Shader();
	~Shader();
};

