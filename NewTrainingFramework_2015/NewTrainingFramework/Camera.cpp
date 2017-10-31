#include "stdafx.h"
#include "Camera.h"

void	Camera::moveOz(int directie)
{
	Vector3 forward = -(target - pos).Normalize() * directie;
	Vector3 deplasare = forward * moveSpeed * deltaTime;
	pos += deplasare;
	target += deplasare;
	updateWorldView();
}

Camera::Camera()
{
	pos = Vector3(0.0f, 0.0f, -1.0f);
	target = Vector3(0.0f, 0.0f, 0.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);
	fov = 45.0f;
	Near = 0.2f;
	Far = 5000.0f;
	moveSpeed = 1.0f;
	rotateSpeed = 0.4f;
	updateWorldView();
}

void Camera::updateWorldView()
{
	Matrix R;
	Matrix T;

	zAxis = -(target - pos).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();

	R.m[0][0] = xAxis.x; R.m[0][1] = xAxis.y; R.m[0][2] = xAxis.z; R.m[0][3] = 0;
	R.m[1][0] = yAxis.x; R.m[1][1] = yAxis.y; R.m[1][2] = yAxis.z; R.m[1][3] = 0;
	R.m[2][0] = zAxis.x; R.m[2][1] = zAxis.y; R.m[2][2] = zAxis.z; R.m[2][3] = 0;
	R.m[3][0] = 0;		 R.m[3][1] = 0;		  R.m[3][2] = 0;	   R.m[3][3] = 1;

	T.SetTranslation(pos.x, pos.y, pos.z);
	worldMatrix = R*T;
	T.SetTranslation(-pos.x, -pos.y, -pos.z);
	R.Transpose();
	viewMatrix = T * R;
}

Camera::~Camera()
{

}

void	Camera::moveOx(int directie)
{
	Vector3 forward = Vector3(1.0f, 0.0f, 0.0f);
	Vector3 deplasare = forward * moveSpeed * deltaTime * directie;
	pos += deplasare;
	target += deplasare;
	updateWorldView();
}

void	Camera::moveOy(int directie)
{

}

void	Camera::rotateOx(int directie)
{

}

void	Camera::rotateOy(int directie)
{

}

void	Camera::rotateOz(int directie)
{

}

void	Camera::setDeltaTime(float deltaTime)
{
	this->deltaTime = deltaTime;
}

GLfloat	Camera::getFar()
{
	return Far;
}

GLfloat Camera::getNear()
{
	return Near;
}

GLfloat Camera::getFOV()
{
	return fov;
}

Matrix Camera::getViewMatrix()
{
	return viewMatrix;
}