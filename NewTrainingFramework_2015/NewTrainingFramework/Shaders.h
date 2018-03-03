#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLuint	program, vertexShader, fragmentShader;
	char	fileVS[260];
	char	fileFS[260];
	GLint	positionAttribute;
	GLint	matrixUniform;
	GLint	textureUniform;
	GLint	uvAttribute;
	GLint	skyboxUniform;
	GLint	uvBlendAttribute;
	int		id;

	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};