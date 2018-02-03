#include "stdafx.h"
#include "SceneObject.h"
#include "Globals.h"
#include "../Utilities/utilities.h"

using namespace std;

SceneObject::SceneObject()
{
}

SceneObject::~SceneObject()
{
}
SceneObject::SceneObject(Vector3 pos, Vector3 rot, Vector3 scl, bool depth)
{
	position = pos;
	rotation = rot;
	scale = scl;
	depthTest = depth;
}

void	SceneObject::setModel(Model* md)
{
	model = md;
}

void	SceneObject::setShader(Shader* st)
{
	shader = st;
}

void	SceneObject::addTexture(Texture *tr)
{
	textures.push_back(tr);
}

void	SceneObject::Draw()
{
	glUseProgram(shader->getId()); //alegem shaderul folosit

	glBindBuffer(GL_ARRAY_BUFFER, model->getVId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getIId());

	SendCommonData();

	glDrawElements(GL_TRIANGLES, model->indices.size(), GL_UNSIGNED_INT, (void *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void		SceneObject::Update()
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
void		SceneObject::SendCommonData()
{

	for (int i = 0; i < textures.size(); i++)
	{
		if (shader->textureUniform[i] != -1)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures.at(i)->getId());
			glUniform1i(shader->textureUniform[i], i);
		}
	}
	if (shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvAttribute);
		glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(4 * sizeof(Vector3)));
	}

	if (shader->uvBlendAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvBlendAttribute);
		glVertexAttribPointer(shader->uvBlendAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(4 * sizeof(Vector3) + sizeof(Vector2)));
	}

	if (shader->matrixUniform != -1)
	{
		glUniformMatrix4fv(shader->matrixUniform, 1, GL_FALSE, (GLfloat *)mvp.m);
	}
}