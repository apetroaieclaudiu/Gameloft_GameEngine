#include "stdafx.h"
#include "Terrain.h"


Terrain::Terrain()
{
}

Terrain::Terrain(unsigned int nr_celule, float dimensiune_celula, float offsetY):nr_celule(nr_celule), dimensiune_celula(dimensiune_celula), offsetY(offsetY)
{
	for (float i = 0; i < 1; i += 1 / 5)
		for (float j = 0; j < 1; j += 1 / 5)
			coordonate.push_back(Vector2(i, j));
}
Terrain::~Terrain()
{
}