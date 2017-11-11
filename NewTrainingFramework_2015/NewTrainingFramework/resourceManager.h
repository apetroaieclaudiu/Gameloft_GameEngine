#pragma once
#include <vector>
#include "Shaders.h"
#include "Models.h"
#include "Textures.h"

class resourceManager
{
private:
	std::vector<Models>				model;
	std::vector<Shaders>			shader;
	std::vector<Textures>			textures;
	static	resourceManager*		spInstance;
	resourceManager();
public:
	~resourceManager();
	static resourceManager*			getInstance();
	void							parsare();
};