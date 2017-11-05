#pragma once
#include <vector>

class Model
{
	std::vector<unsigned int>	indices;
	std::vector<float>			points;

public:
	Model();
	~Model();
	std::vector<unsigned int>	getIndices();
	std::vector<float>			getPoints();
	void						setAll();
};

