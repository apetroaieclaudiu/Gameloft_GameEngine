#pragma once
#include "../Utilities/utilities.h"

class Camera
{
public:
	Camera();
	~Camera();
	void	moveOx(int);
	void	moveOy(int);
	void	moveOz(int);
	void	rotateOx(int);
	void	rotateOy(int);
	void	rotateOz(int);
	void	updateWorldView();
	void	setDeltaTime(float);
	GLfloat	getFar();
	GLfloat getNear();
	GLfloat	getFOV();
	Matrix	getViewMatrix();

private:
	Vector3 pos;
	Vector3 target;
	Vector3	up;
	Vector3 xAxis, yAxis, zAxis;
	GLfloat moveSpeed;
	GLfloat rotateSpeed;
	GLfloat Near;
	GLfloat Far;
	GLfloat fov;
	GLfloat deltaTime;
	Matrix	viewMatrix;
	Matrix	worldMatrix;
};
