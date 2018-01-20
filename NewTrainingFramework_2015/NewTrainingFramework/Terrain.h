#pragma once
#include "../Utilities/utilities.h"
#include <vector>

class Terrain
{
	unsigned int				nr_celule;
	float						dimensiune_celula;
	float						offsetY;
	std::vector<Vector2>		coordonate;
	std::vector<unsigned int>	indici;

public:
	Terrain();
	Terrain(unsigned int, float, float);
	~Terrain();
};

