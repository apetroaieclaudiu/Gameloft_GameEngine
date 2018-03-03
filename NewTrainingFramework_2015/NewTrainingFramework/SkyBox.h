#pragma once
#include "SceneObject.h"

class SkyBox:public SceneObject
{

public:
	void	Update();
	void	Draw();
	SkyBox();
	~SkyBox();
};

