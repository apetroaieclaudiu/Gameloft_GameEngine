#include "stdafx.h"
#include "Shader.h"
#include <iostream>

Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::Load()
{
	GLuint vertexShader, fragmentShader;
	vertexShader = esLoadShader(GL_VERTEX_SHADER, (char*)("../" + mr->vs).c_str()); //primeste calea catre shader si compileaza

	if (vertexShader == 0)
		std::cerr << "Error Vertex Shader";

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, (char*)("../" + mr->fs).c_str()); // la fel ca la vertex shader

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		std::cerr << "Error Fragment Shader";
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL"); //ia locatia variabilei a_posL din shader ca sa modif variabile
	matrixUniform = glGetUniformLocation(program, "u_matrix");
	textureUniform = glGetUniformLocation(program, "u_texture");
	uvAttribute = glGetAttribLocation(program, "a_uv");
}

void		Shader::setMr(ShaderResource *r)
{
	mr = r;
}

GLuint		Shader::getId()
{
	return program;
}