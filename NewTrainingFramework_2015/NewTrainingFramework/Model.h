#pragma once
#include <vector>
#include "ModelResource.h"
#include "Vertex.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class Model
{
	ModelResource				*mr;
	int							nr_vertex;
	int							nr_index;
	int							nr_indici_wired;

public:
	GLuint						iboId;
	GLuint						wiredIboId;
	GLuint						vboId;
	std::vector<unsigned int>	indices;
	std::vector<unsigned int>   windices;
	std::vector<Vertex>			points;
	Model();
	Model(std::vector<Vertex>, std::vector<unsigned int>);
	~Model();
	void						Load();
	void						setMr(ModelResource *);
	int							getNr();
	int							getInd();
	GLuint						getVId();
	GLuint						getWId();
	GLuint						getIId();
};
