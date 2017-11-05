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
		f >> aux;
		f >> aux;
		aux.erase(0, 5);
		vertex = atof(aux.c_str());

		if (std::find(points.begin(), points.end(), vertex) == points.end())
			points.push_back(vertex);

		f >> vertex;

		if (std::find(points.begin(), points.end(), vertex) == points.end())
			points.push_back(vertex);

		f >> aux;
		f >> aux;
		vertex = atof(aux.c_str());

		if (std::find(points.begin(), points.end(), vertex) == points.end())
			points.push_back(vertex);

		std::getline(f, aux);
	}

	f >> aux;
	f >> aux;
	nr_vertex = atoi(aux.c_str());
	nr_vertex /= 3;

	for (int i = 0; i < nr_vertex; i++)
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

std::vector<unsigned int>	Model::getIndices()
{
	return (indices);
}

std::vector<float>			Model::getPoints()
{
	return (points);
}

int							Model::getNr()
{
	return (nr_vertex);
}