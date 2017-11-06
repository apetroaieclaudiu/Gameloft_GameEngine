#pragma once
#include <vector>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"


class Model
{

	int							nr_vertex;
	int							nr_index;

public:
	std::vector<unsigned int>	indices;
	std::vector<Vertex>			points;
	Model(const char*);
	~Model();
	int							getNr();
	int							getInd();
};

