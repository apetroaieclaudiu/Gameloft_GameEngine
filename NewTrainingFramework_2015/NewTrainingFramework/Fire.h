#pragma once
#include "SceneObject.h"

extern float uTime;

class Fire: public SceneObject
{
	float dispMax;
public:
	Fire();
	~Fire();
	Fire(float);
	void	Update();
	void	Draw();
};

