#pragma once
#include "../Utilities/utilities.h"
#include <map>
#include "ShaderResource.h"
#include "ModelResource.h"
#include "TextureResource.h"

class resourceManager
{
private:
	std::map <int, ModelResource>				model;
	std::map <int, ShaderResource>				shader;
	std::map <int, TextureResource>				textures;
	static	resourceManager*					spInstance;
	resourceManager();
public:
	~resourceManager();
	static resourceManager*			getInstance();
	void							Init();
};