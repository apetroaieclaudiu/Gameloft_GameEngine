#pragma once
#include <vector>

class Model
{
	std::vector<unsigned int>	indices;
	std::vector<float>			points;
	int							nr_vertex;

public:
	Model(const char*);
	~Model();
	std::vector<unsigned int>	getIndices();
	std::vector<float>			getPoints();
	int							getNr();
};

