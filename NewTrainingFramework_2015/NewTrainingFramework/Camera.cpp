#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	position = Vector3(0.0f, 0.0f, -1.0f);
	target = Vector3(0.0f, 0.0f, 0.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);
	moveSpeed = 5.0f;
	rotateSpeed = 0.9f;
	Near = 0.2f;
	Far = 5000.0f;
	FOV = 45.0f;
	update();
}
Camera::Camera(Vector3 pos, Vector3 tar, Vector3 sus, GLfloat ms, GLfloat rs, GLfloat nr, GLfloat fr, GLfloat fv)
{
	position = pos;
	target = tar;
	up = sus;
	moveSpeed = ms;
	rotateSpeed = rs;
	Near = nr;
	Far = fr;
	FOV = fv;
}
Camera::~Camera()
{

}

void	Camera::updateAxis()
{
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();
}

Matrix	Camera::getView()
{
	return (viewMatrix);
}

Matrix	Camera::getWorld()
{
	return (worldMatrix);
}

void	Camera::setDeltaTime(float delta)
{
	deltaTime = delta;
}

void	Camera::update()
{
	updateAxis();
	Matrix R, T;
	R.m[0][0] = xAxis.x; R.m[0][1] = xAxis.y; R.m[0][2] = xAxis.z; R.m[0][3] = 0;
	R.m[1][0] = yAxis.x; R.m[1][1] = yAxis.y; R.m[1][2] = yAxis.z; R.m[1][3] = 0;
	R.m[2][0] = zAxis.x; R.m[2][1] = zAxis.y; R.m[2][2] = zAxis.z; R.m[2][3] = 0;
	R.m[3][0] = 0;		 R.m[3][1] = 0;		  R.m[3][2] = 0;	   R.m[3][3] = 1;
	T.SetTranslation(position);
	worldMatrix = R * T;
	R = R.Transpose();
	T.SetTranslation(-(position));
	viewMatrix = T * R;
}

void	Camera::moveOz(int sens)
{
	Vector3 forward = -(target - position).Normalize() * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	update();
}

void	Camera::moveOy(int sens)
{
	Vector3 forward = up.Normalize() * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	update();
}

void	Camera::moveOx(int sens)
{
	Vector3 forward = up.Cross(-(target - position)).Normalize() * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	update();
}
GLfloat	Camera::getNear()
{
	return (Near);
}
GLfloat	Camera::getFar()
{
	return (Far);
}
GLfloat	Camera::getFOV()
{
	return	(FOV);
}

void	Camera::rotateOx(int sens)
{
	Matrix	m;
	Vector4 rotatedLocalUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f) * m.SetRotationX(rotateSpeed * deltaTime * sens);
	Vector4 u = rotatedLocalUp * worldMatrix;
	up = Vector3(u.x, u.y, u.z).Normalize();
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * m;
	u = rotatedTarget * worldMatrix;
	target = Vector3(u.x, u.y, u.z);
	update();
}

void Camera::rotateOz(int sens)
{
	Matrix	m;
	Vector4 rotatedLocalUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f) * m.SetRotationZ(rotateSpeed * deltaTime * sens);
	Vector4 u = rotatedLocalUp * worldMatrix;
	up = Vector3(u.x, u.y, u.z).Normalize();
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * m;
	u = rotatedTarget * worldMatrix;
	target = Vector3(u.x, u.y, u.z);
	update();
}

void Camera::rotateOy(int sens)
{
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Matrix	m;
	m.SetRotationY(rotateSpeed * deltaTime * sens);
	Vector4 rotatedTarget = localTarget * m;
	Vector4 u = rotatedTarget * worldMatrix;
	target = Vector3(u.x, u.y, u.z);
	update();
}