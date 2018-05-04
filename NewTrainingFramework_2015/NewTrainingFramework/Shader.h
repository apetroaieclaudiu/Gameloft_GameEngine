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
	GLint	skyboxUniform;
	GLint	camUniform;
	GLint	worldUniform;
	GLint	colorUniform;
	GLint	rUniform;
	GLint	RUniform;
	GLint	uvBlendAttribute;
	GLint	uTimeUniform;
	GLint	dispMaxUniform;
	GLint	normAttribute;
	GLint	ambUniform;
	GLint	diffColorUniform;
	GLint	diffDirectionUniform;
	GLint	ratioUniform;
	GLint	specColorUniform;
	GLint	specPowerUniform;
	GLint	spotLightPositionUniform;
	GLint	spotLightOpeningUniform;
	GLint	lightTypesUniform;
	GLint	spotLightAttenuation;

	void			Load();
	void			setMr(ShaderResource *);
	int Init(char * fileVertexShader, char * fileFragmentShader);
	GLuint			getId();
	Shader();
	~Shader();
};

