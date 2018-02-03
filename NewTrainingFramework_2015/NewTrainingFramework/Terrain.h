#pragma once
#include "SceneObject.h"

extern Camera cam;

class Terrain:public SceneObject
{
	int							nr_celule;
	float						dimensiune_celula;
	float						offsetY;
	std::string					mdl;
	Vector3						centru;
	Vector3						height;

public:
	Terrain();
	Terrain(int, float, float, std::string);
	void	setHeight(Vector3);
	void	Draw();
	~Terrain();
	void Update();
};

