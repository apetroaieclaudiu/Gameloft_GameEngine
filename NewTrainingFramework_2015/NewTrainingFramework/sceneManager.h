#pragma once
#include <vector>
#include <map>
#include "Camera.h"
#include "SceneObject.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "../Utilities/utilities.h"

class sceneManager
{
	static	sceneManager*								spInstance;
	Vector3												backgroundColor;
	std::map<unsigned int, Camera*>						cameras;
	std::map<unsigned int, SceneObject*>				objects;
	sceneManager();
public:
	Vector3												color;
	float												r, R;
	~sceneManager();
	static sceneManager*			getInstance();
	void							Load();
	void							Draw();
	void							Update();
};

