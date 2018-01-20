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
	textureUniform[0] = glGetUniformLocation(program, "u_texture0");
	textureUniform[1] = glGetUniformLocation(program, "u_texture1");
	textureUniform[2] = glGetUniformLocation(program, "u_texture2");
	textureUniform[3] = glGetUniformLocation(program, "u_texture3");
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