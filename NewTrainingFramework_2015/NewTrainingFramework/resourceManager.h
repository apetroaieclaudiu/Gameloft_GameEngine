#pragma once
#include <map>
#include <vector>
#include "ModelResource.h"
#include "ShaderResource.h"
#include "TextureResource.h"
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "fmod.h"

class resourceManager
{
private:
	std::map<unsigned int, ModelResource*>		models;
	std::map<unsigned int, ShaderResource*>		shaders;
	std::map<unsigned int, TextureResource*>	textures;
	std::map<unsigned int, Model*>				loadedModels;
	std::map<unsigned int, Texture*>			loadedTextures;
	std::map<unsigned int, Shader*>				loadedShaders;
	static	resourceManager*					spInstance;
	resourceManager();
public:
	~resourceManager();
	static resourceManager*			getInstance();
	void							Init();
	Model*							loadModel(unsigned int);
	Texture*						loadTexture(unsigned int);
	Shader*							loadShader(unsigned int);
};