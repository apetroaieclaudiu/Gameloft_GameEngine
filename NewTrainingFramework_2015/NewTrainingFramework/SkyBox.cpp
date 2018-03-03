#include "stdafx.h"
#include "SkyBox.h"
#include "Globals.h"


SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}

void	SkyBox::Draw()
{
	Matrix p;
	p.SetScale(scale);
	p = p * m.SetRotationX(rotation.x);
	p = p * m.SetRotationY(rotation.y);
	p = p * m.SetRotationZ(rotation.z);
	p = p * m.SetTranslation(position);
	p = p * m.SetTranslation(cam.getPos());
	m = p;
	mvp = m * cam.getView();
	Matrix P;
	P.SetPerspective(cam.getFOV(), (GLfloat)Globals::screenWidth / Globals::screenHeight, cam.getNear(), cam.getFar());
	mvp = mvp * P;
	glUseProgram(shader->getId()); //alegem shaderul folosit

	glBindBuffer(GL_ARRAY_BUFFER, model->getVId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getIId());

	SendCommonData();

	glDrawElements(GL_TRIANGLES, model->indices.size(), GL_UNSIGNED_INT, (void *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	SkyBox::Update()
{
	Matrix m, p;
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