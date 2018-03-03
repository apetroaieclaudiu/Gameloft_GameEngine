#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "../Utilities/utilities.h"

extern Camera cam;

class SceneObject
{
protected:


public:
	Matrix m;
	SceneObject(Vector3, Vector3, Vector3, bool);
	SceneObject();
	virtual						~SceneObject();
	void						setModel(Model*);
	void						setShader(Shader*);
	void						addTexture(Texture*);
	virtual void				Draw();
	void						SendCommonData();
	virtual	void				Update();
	Vector3						position;
	Vector3						rotation;
	Vector3						scale;
	Model*						model;
	std::vector<Texture*>		textures;
	Shader*						shader;
	Matrix						mvp;
	bool						depthTest;
};