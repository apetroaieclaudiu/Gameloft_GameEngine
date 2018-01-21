#include "stdafx.h"
#include "Terrain.h"


Terrain::Terrain()
{
}

Terrain::Terrain(int nr_celule, float dimensiune_celula, float offsetY, std::string model):nr_celule(nr_celule), dimensiune_celula(dimensiune_celula), offsetY(offsetY), model(model)
{
	Vector3 centru = cam.getPos();

	if (model == "generated")
	{
		for (int i = nr_celule / 2, uv_i = 0; i > -nr_celule / 2; i--, uv_i++)
			for (int j = -nr_celule / 2, uv_j = 0; j <= +nr_celule / 2; j++, uv_j++)
			{
				Vertex *coord = new Vertex();
				coord->pos = Vector3(centru.x + j * dimensiune_celula, offsetY, centru.z + i * dimensiune_celula);
				coord->norm = Vector3(0.0f, 1.0f, 0.0f);
				coord->binorm = Vector3(0.0f, 1.0f, 0.0f);
				coord->tgt = Vector3(0.0f, 1.0f, 0.0f);
				coord->uv = Vector2(uv_i, uv_j);
				coord->uv_blend = Vector2((float) uv_i / nr_celule, (float) uv_j / nr_celule);
				vertexi.push_back(coord);
			}

		for (unsigned int i = 1; i < nr_celule * nr_celule + nr_celule; i++)
		{
			indici.push_back(i);
			indici.push_back(i + nr_celule + 1);
			i++;

			indici.push_back(i);
			indici.push_back(i + nr_celule);

			indici.push_back(i);
			indici.push_back(i + nr_celule + 1);
			i--;
		}
	}
}
Terrain::~Terrain()
{
	for (int i = 0; i < vertexi.size(); i++)
		delete vertexi.at(i);
	vertexi.clear();
}

void		Terrain::Draw()
{
}