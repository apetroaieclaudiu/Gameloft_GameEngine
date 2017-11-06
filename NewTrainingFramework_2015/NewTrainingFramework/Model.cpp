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
		points[i].color.x = 1.0f;
		f >> vertex;

		points[i].pos.y = (GLfloat)vertex;

		f >> aux;
		f >> aux;
		vertex = atof(aux.c_str());

		points[i].pos.z = (GLfloat)vertex;

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