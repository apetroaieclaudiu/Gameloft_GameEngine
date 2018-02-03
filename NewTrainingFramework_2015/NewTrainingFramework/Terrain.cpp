#include "stdafx.h"
#include "Terrain.h"


Terrain::Terrain()
{
}

Terrain::Terrain(int nr_celule, float dimensiune_celula, float offsetY, std::string mod):nr_celule(nr_celule), dimensiune_celula(dimensiune_celula), offsetY(offsetY), mdl(mod)
{
	centru = cam.getPos();
	model = new Model();
	if (mdl == "generated")
	{
		for (int i = nr_celule / 2, uv_i = 0; i >= -nr_celule / 2; i--, uv_i++)
			for (int j = -nr_celule / 2, uv_j = 0; j <= +nr_celule / 2; j++, uv_j++)
			{
				Vertex *coord = new Vertex();
				coord->pos = Vector3(centru.x + j * dimensiune_celula, offsetY, centru.z + i * dimensiune_celula);
				coord->norm = Vector3(0.0f, 1.0f, 0.0f);
				coord->binorm = Vector3(0.0f, 1.0f, 0.0f);
				coord->tgt = Vector3(0.0f, 1.0f, 0.0f);
				coord->uv = Vector2(uv_i, uv_j);
				coord->uv_blend = Vector2((float) uv_i / nr_celule, (float) uv_j / nr_celule);
				model->points.push_back(*coord);
				delete coord;
			}

		for (unsigned int i = 0; i < nr_celule; i++)
		{
			for (unsigned int j = 0; j < nr_celule; j++)
			{
				model->indices.push_back(i * (nr_celule + 1) + j);
				
				model->indices.push_back((i + 1) * (nr_celule + 1) + j);
				model->indices.push_back(i * (nr_celule + 1) + j + 1);
				model->indices.push_back(i * (nr_celule + 1) + j + 1);
				model->indices.push_back((i + 1) * (nr_celule + 1) + j);
				model->indices.push_back((i + 1) * (nr_celule + 1) + j + 1);

			}
		}
		
		glGenBuffers(1, &model->iboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indices.size() * sizeof(unsigned int), model->indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//buffer object
		glGenBuffers(1, &model->vboId);
		//Imi leaga buffer de vboId
		glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
		glBufferData(GL_ARRAY_BUFFER, model->points.size() * sizeof(Vertex), model->points.data(), GL_STATIC_DRAW); //Static draw -> nu mi modifica bufferul
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}
}
Terrain::~Terrain()
{
}

void	Terrain::Update()
{
	SceneObject::Update();
	if (abs(cam.getPos().z - centru.z) > dimensiune_celula && cam.getPos().z > centru.z)
	{
		for (int i = 0; i < model->points.size(); i++)
		{
			model->points[i].pos.z += dimensiune_celula;
			model->points[i].uv_blend.x -= 1.0 / nr_celule;
		}
		centru.z += dimensiune_celula;
	}
	else if (abs(cam.getPos().z - centru.z) > dimensiune_celula && cam.getPos().z < centru.z)
	{
		for (int i = 0; i < model->points.size(); i++)
		{
			model->points[i].pos.z -= dimensiune_celula;
			model->points[i].uv_blend.x += 1.0 / nr_celule;
		}
		centru.z -= dimensiune_celula;
	}
	
	if (abs(cam.getPos().x - centru.x) > dimensiune_celula && cam.getPos().x > centru.x)
	{
		for (int i = 0; i < model->points.size(); i++)
		{
			model->points[i].pos.x += dimensiune_celula;
			model->points[i].uv_blend.y += 1.0 / nr_celule;
		}
		centru.x += dimensiune_celula;
	}
	else if (abs(cam.getPos().x - centru.x) > dimensiune_celula && cam.getPos().x < centru.x)
	{
		for (int i = 0; i < model->points.size(); i++)
		{
			model->points[i].pos.x -= dimensiune_celula;
			model->points[i].uv_blend.y -= 1.0 / nr_celule;
		}
		centru.x -= dimensiune_celula;
	}
	glGenBuffers(1, &model->vboId);
	//Imi leaga buffer de vboId
	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	glBufferData(GL_ARRAY_BUFFER, model->points.size() * sizeof(Vertex), model->points.data(), GL_STATIC_DRAW); //Static draw -> nu mi modifica bufferul
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Terrain::Draw()
{
	glUseProgram(shader->getId()); //alegem shaderul folosit

	glBindBuffer(GL_ARRAY_BUFFER, model->getVId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getIId());

	if (shader->heightUniform != -1)
	{
		glUniform3f(shader->heightUniform, height.x, height.y, height.z);
	}
	SendCommonData();

	glDrawElements(GL_TRIANGLES, model->indices.size(), GL_UNSIGNED_INT, (void *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	Terrain::setHeight(Vector3 height)
{
	this->height = height;
}