#pragma once
#include "../Utilities/utilities.h"

class Camera
{
	Vector3 position;
	Vector3 target;
	Vector3 up;

	GLfloat moveSpeed;
	GLfloat	rotateSpeed;
	GLfloat Near;
	GLfloat Far;
	GLfloat	FOV;
	GLfloat deltaTime;
	Vector3 xAxis, yAxis, zAxis;
	Matrix	viewMatrix, worldMatrix;

public:
	Camera();
	Camera::Camera(Vector3, Vector3, Vector3, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	~Camera();
	Matrix		getView();
	Matrix		getWorld();
	void		setDeltaTime(float);
	void		updateWorldView();
	void		updateAxis();
	void		update();
	void		moveOz(int);
	void		moveOy(int);
	void		moveOx(int);
	void		rotateOx(int);
	void		rotateOy(int);
	void		rotateOz(int);
	GLfloat		getNear();
	GLfloat		getFar();
	GLfloat		getFOV();
	Vector3&	getPos();
};