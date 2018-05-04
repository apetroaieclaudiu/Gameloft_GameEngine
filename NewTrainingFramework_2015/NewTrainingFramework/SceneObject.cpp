#include "stdafx.h"
#include "SceneObject.h"
#include "Globals.h"
#include "../Utilities/utilities.h"
#include "sceneManager.h"

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
void		SceneObject::SendCommonData()
{
	for (int i = 0; i < textures.size(); i++)
	{
		if (shader->textureUniform[i] != -1)
		{
			for (int i = 0; i < textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textures.at(i)->getId());
				glUniform1i(shader->textureUniform[i], i);
			}
		}
	}

	if (shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (shader->skyboxUniform != -1)
	{
		for (int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textures.at(i)->getId());
			glUniform1i(shader->skyboxUniform, i);
		}
	}

	if (shader->camUniform != -1)
	{
		glUniform3f(shader->camUniform, cam.getPos().x, cam.getPos().y, cam.getPos().z);
	}

	if (shader->rUniform != -1)
	{
		glUniform1f(shader->rUniform, sceneManager::getInstance()->r);
	}

	if (shader->RUniform != -1)
	{
		glUniform1f(shader->rUniform, sceneManager::getInstance()->R);
	}

	if (shader->worldUniform != -1)
	{
		glUniformMatrix4fv(shader->worldUniform, 1, GL_FALSE, (GLfloat *)m.m);
	}

	if (shader->colorUniform != -1)
	{
		glUniform3f(shader->colorUniform, sceneManager::getInstance()->color.x, sceneManager::getInstance()->color.y, sceneManager::getInstance()->color.z);
	}

	if (shader->ambUniform != -1)
	{
		glUniform3f(shader->ambUniform, sceneManager::getInstance()->ambientalColor.x, sceneManager::getInstance()->ambientalColor.y, sceneManager::getInstance()->ambientalColor.z);
	}

	if (shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvAttribute);
		glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(4 * sizeof(Vector3)));
	}

	if (shader->diffColorUniform != -1)
	{
		glUniform3f(shader->diffColorUniform, sceneManager::getInstance()->diffColor.x, sceneManager::getInstance()->diffColor.y, sceneManager::getInstance()->diffColor.z);
	}

	if (shader->ratioUniform != -1)
	{
		glUniform1f(shader->ratioUniform, sceneManager::getInstance()->ratio);
	}

	if (shader->diffDirectionUniform != -1)
	{
		glUniform3f(shader->diffDirectionUniform, sceneManager::getInstance()->diffDirection.x, sceneManager::getInstance()->diffDirection.y, sceneManager::getInstance()->diffDirection.z);
	}
	if (shader->normAttribute != -1)
	{
		glEnableVertexAttribArray(shader->normAttribute);
		glVertexAttribPointer(shader->normAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(Vector3)));
	}

	if (shader->uvBlendAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvBlendAttribute);
		glVertexAttribPointer(shader->uvBlendAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(4 * sizeof(Vector3) + sizeof(Vector2)));
	}

	if (shader->specColorUniform != -1)
	{
		glUniform3f(shader->specColorUniform, sceneManager::getInstance()->specColor.x, sceneManager::getInstance()->specColor.y, sceneManager::getInstance()->specColor.z);
	}

	if (shader->specPowerUniform != -1)
	{
		glUniform1f(shader->specPowerUniform, sceneManager::getInstance()->specPower);
	}

	if (shader->spotLightOpeningUniform != -1)
	{
		glUniform1f(shader->spotLightOpeningUniform, sceneManager::getInstance()->spotLightOpening);
	}

	if (shader->spotLightPositionUniform != -1)
	{
		glUniform3f(shader->spotLightPositionUniform, sceneManager::getInstance()->spotLightPosition.x, sceneManager::getInstance()->spotLightPosition.y, sceneManager::getInstance()->spotLightPosition.z);
	}


	if (shader->spotLightAttenuation != -1)
	{
		glUniform1f(shader->spotLightAttenuation, sceneManager::getInstance()->spotLightAttenuation);
	}

	if (shader->lightTypesUniform != -1)
	{
		glUniform3f(shader->lightTypesUniform, sceneManager::getInstance()->lightTypes.x, sceneManager::getInstance()->lightTypes.y, sceneManager::getInstance()->lightTypes.z);
	}
	if (shader->matrixUniform != -1)
	{
		glUniformMatrix4fv(shader->matrixUniform, 1, GL_FALSE, (GLfloat *)mvp.m);
	}
}