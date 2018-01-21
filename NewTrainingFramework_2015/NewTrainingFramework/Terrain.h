#pragma once
#include "SceneObject.h"

extern Camera cam;

class Terrain:public SceneObject
{
	int							nr_celule;
	float						dimensiune_celula;
	float						offsetY;
	std::string					model;
	std::vector<Vertex*>			vertexi;
	std::vector<unsigned int>	indici;

public:
	Terrain();
	Terrain(int, float, float, std::string);
	void	Draw();
	~Terrain();
};

