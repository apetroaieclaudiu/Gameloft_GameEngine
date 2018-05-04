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
	heightUniform = glGetUniformLocation(program, "u_height"); //ia locatia variabilei a_posL din shader ca sa modif variabile
	positionAttribute = glGetAttribLocation(program, "a_posL"); //ia locatia variabilei a_posL din shader ca sa modif variabile
	matrixUniform = glGetUniformLocation(program, "u_matrix");
	textureUniform[0] = glGetUniformLocation(program, "u_texture0");
	textureUniform[1] = glGetUniformLocation(program, "u_texture1");
	textureUniform[2] = glGetUniformLocation(program, "u_texture2");
	textureUniform[3] = glGetUniformLocation(program, "u_texture3");
	skyboxUniform = glGetUniformLocation(program, "u_cube_texture");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	camUniform = glGetUniformLocation(program, "u_cam");
	rUniform = glGetUniformLocation(program, "u_r");
	worldUniform = glGetUniformLocation(program, "u_world");
	RUniform = glGetUniformLocation(program, "u_R");
	colorUniform = glGetUniformLocation(program, "u_color");
	uvBlendAttribute = glGetAttribLocation(program, "a_uv_blend");
	uTimeUniform = glGetUniformLocation(program, "u_time");
	dispMaxUniform = glGetUniformLocation(program, "u_dispMax");
	ambUniform = glGetUniformLocation(program, "c_amb");
	normAttribute = glGetAttribLocation(program, "a_norm");
	diffColorUniform = glGetUniformLocation(program, "c_luminaDiff");
	diffDirectionUniform = glGetUniformLocation(program, "L");
	ratioUniform = glGetUniformLocation(program, "ratio");
	specColorUniform = glGetUniformLocation(program, "c_luminaSpec");
	specPowerUniform = glGetUniformLocation(program, "SpecPower");
	spotLightOpeningUniform = glGetUniformLocation(program, "u_spot_pos");
	spotLightPositionUniform = glGetUniformLocation(program, "u_spot_opening");
	lightTypesUniform = glGetUniformLocation(program, "u_lights_type");
	spotLightAttenuation = glGetUniformLocation(program, "u_spot_attenuation");
}

void		Shader::setMr(ShaderResource *r)
{
	mr = r;
}

GLuint		Shader::getId()
{
	return program;
}