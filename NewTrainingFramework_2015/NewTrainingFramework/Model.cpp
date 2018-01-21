#include "stdafx.h"
#include "Model.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

Model::~Model()
{

}

int							Model::getNr()
{
	return (nr_vertex);
}

int							Model::getInd()
{
	return(nr_index);
}

void			Model::setMr(ModelResource *m)
{
	mr = m;
}

Model::Model()
{

}

void		Model::Load()
{
	std::string		aux;
	unsigned int	ind1, ind;
	float			vertex;
	std::ifstream	f("../" + mr->path);

	if (!f)
		std::cerr << "Nu s a gasit modelul";

	f >> aux;
	f >> aux;

	nr_vertex = atoi(aux.c_str());

	for (int i = 0; i < nr_vertex; i++)
	{
		points.push_back(Vertex());
		f >> aux;
		f >> aux;
		aux.erase(0, 5);
		vertex = atof(aux.c_str());

		points[i].pos.x = (GLfloat)vertex;
		f >> vertex;

		points[i].pos.y = (GLfloat)vertex;

		f >> aux;
		f >> aux;
		vertex = atof(aux.c_str());

		points[i].pos.z = (GLfloat)vertex;

		f >> aux;
		aux.erase(0, 6);
		vertex = atof(aux.c_str());

		points[i].norm.x = (GLfloat)vertex;

		f >> vertex;

		points[i].norm.y = (GLfloat)vertex;

		f >> aux;
		f >> aux;
		vertex = atof(aux.c_str());

		points[i].norm.z = (GLfloat)vertex;

		f >> aux;
		aux.erase(0, 8);
		vertex = atof(aux.c_str());

		points[i].binorm.x = (GLfloat)vertex;

		f >> vertex;

		points[i].binorm.y = (GLfloat)vertex;

		f >> aux;
		f >> aux;
		vertex = atof(aux.c_str());

		points[i].binorm.z = (GLfloat)vertex;


		f >> aux;
		aux.erase(0, 5);
		vertex = atof(aux.c_str());

		points[i].tgt.x = (GLfloat)vertex;

		f >> vertex;

		points[i].tgt.y = (GLfloat)vertex;

		f >> aux;
		f >> aux;
		vertex = atof(aux.c_str());

		points[i].tgt.z = (GLfloat)vertex;


		f >> aux;
		aux.erase(0, 4);
		vertex = atof(aux.c_str());

		points[i].uv.x = (GLfloat)vertex;

		f >> vertex;

		points[i].uv.y = (GLfloat)vertex;

		points[i].uv_blend.x = (GLfloat) 0.0f;
		points[i].uv_blend.y = (GLfloat) 0.0f;


		std::getline(f, aux);
	}

	f >> aux;
	f >> aux;
	nr_index = atoi(aux.c_str());

	for (int i = 0; i < nr_index / 3; i++)
	{
		f >> aux;
		f >> aux;
		ind = atoi(aux.c_str());
		ind1 = ind;
		indices.push_back(ind);
		windices.push_back(ind);
		f >> aux;
		ind = atoi(aux.c_str());
		indices.push_back(ind);
		windices.push_back(ind);
		windices.push_back(ind);
		f >> aux;
		ind = atoi(aux.c_str());
		windices.push_back(ind);
		windices.push_back(ind);
		windices.push_back(ind1);
		indices.push_back(ind);
	}

	nr_indici_wired = windices.size();

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &(indices)[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//buffer object
	glGenBuffers(1, &vboId);
	//Imi leaga buffer de vboId
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(Vertex), &(points)[0], GL_STATIC_DRAW); //Static draw -> nu mi modifica bufferul
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &wiredIboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wiredIboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, windices.size() * sizeof(unsigned int), &(windices)[0], GL_STATIC_DRAW); //Static draw -> nu mi modifica bufferul
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint		Model::getVId()
{
	return vboId;
}

GLuint		Model::getWId()
{
	return wiredIboId;
}

GLuint		Model::getIId()
{
	return iboId;
}