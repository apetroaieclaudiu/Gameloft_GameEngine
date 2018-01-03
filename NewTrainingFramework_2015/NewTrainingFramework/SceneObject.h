#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "../Utilities/utilities.h"

extern Camera cam;

class SceneObject
{
	Vector3						position;
	Vector3						rotation;
	Vector3						scale;
	Model*						model;
	std::vector<Texture*>		textures;
	Shader*						shader;
	bool						depthTest;

public:
	SceneObject(Vector3, Vector3, Vector3, bool);
	SceneObject();
	~SceneObject();
	void	setModel(Model*);
	void	setShader(Shader*);
	void	addTexture(Texture*);
	void	Draw();
};