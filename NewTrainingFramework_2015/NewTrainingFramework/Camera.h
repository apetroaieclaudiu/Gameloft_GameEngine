#pragma once
#include "../Utilities/utilities.h"
#include <math.h>
class Camera
{
public:
	Vector4 position, target, up;
	Vector4 xAxis, yAxis, zAxis;

	Matrix viewMatrix, worldMatrix;

	GLfloat moveSpeed;
	GLfloat rotateSpeed;
	GLfloat Near, Far, fov, deltaTime;

	void moveOz(float);
	void moveOy(float);
	void moveOx(float);
	void setDeltaTime(float delta) {
		deltaTime = (GLfloat)delta;
	}
	void RotateOx(float);
	void RotateOy(float);
	void RotateOz(float);
	void updateWorld();
	void updateView();
	void update();
	Matrix getRotation();
	Matrix getTranspose();
	void UpdateAxis();
	Camera();
	~Camera();
};