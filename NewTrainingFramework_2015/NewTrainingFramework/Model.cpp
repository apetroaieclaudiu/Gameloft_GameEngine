#include "stdafx.h"
#include "Model.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

Model::Model(const char* c)
{
	std::string		aux;
	unsigned int	ind;
	float			vertex;
	std::ifstream	f(c);

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

		std::getline(f, aux);
	}

	f >> aux;
	f >> aux;
	nr_index = atoi(aux.c_str());

	for (int i = 0; i < nr_index/3; i++)
	{
		f >> aux;
		f >> aux;
		ind = atoi(aux.c_str());
		indices.push_back(ind);
		f >> aux;
		ind = atoi(aux.c_str());
		indices.push_back(ind);
		f >> aux;
		ind = atoi(aux.c_str());
		indices.push_back(ind);
	}
}

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