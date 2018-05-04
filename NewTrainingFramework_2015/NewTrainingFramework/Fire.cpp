#include "stdafx.h"
#include "Fire.h"
#include "Globals.h"
#include "sceneManager.h"

Fire::Fire()
{
}


Fire::~Fire()
{
}

Fire::Fire(float disp) :dispMax(disp)
{
}

void	Fire::Draw()
{
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(shader->getId()); //alegem shaderul folosit
	if (shader->uTimeUniform != -1)
	{
		glUniform1f(shader->uTimeUniform, uTime);
	}

	if (shader->dispMaxUniform != -1)
	{
		glUniform1f(shader->dispMaxUniform, dispMax);
	}

	glBindBuffer(GL_ARRAY_BUFFER, model->getVId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getIId());

	SendCommonData();

	glDrawElements(GL_TRIANGLES, model->indices.size(), GL_UNSIGNED_INT, (void *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void		Fire::Update()
{
	Matrix p;
	p.SetScale(scale);
	p = p * m.SetRotationX(rotation.x);
	p = p * m.SetRotationY(rotation.y);
	p = p * m.SetRotationZ(rotation.z);
	p = p * m.SetTranslation(position);
	m = p;
	mvp = m * cam.getView();
	Matrix P;
	P.SetPerspective(cam.getFOV(), (GLfloat)Globals::screenWidth / Globals::screenHeight, cam.getNear(), cam.getFar());
	mvp = mvp * P;
}