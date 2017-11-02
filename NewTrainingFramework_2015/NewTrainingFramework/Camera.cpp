#include "stdafx.h"
#include "Camera.h"

void Camera::moveOz(float directie) {
	Vector4 forward = -(target - position).Normalize()*directie;
	Vector4 vectorDeplasare = forward*moveSpeed*deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	update();
}
void Camera::moveOy(float directie) {
	Vector4 forward = up.Normalize();
	Vector4 vectorDeplasare = forward*moveSpeed*deltaTime*directie;
	position += vectorDeplasare;
	target += vectorDeplasare;
	update();
}
void Camera::moveOx(float directie) {
	Vector4 forward = Vector4(1.0f, 0.0f, 0.0f, 1.0f);//= .Cross(up).Normalize()*directie;
	Vector4 vectorDeplasare = forward*moveSpeed*deltaTime*directie;
	position += vectorDeplasare;
	target += vectorDeplasare;
	update();
}
void Camera::RotateOy(float dir) {
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Matrix mRotateOy;
	mRotateOy.SetRotationY(rotateSpeed*deltaTime*dir);
	Vector4 rotatedTarget = localTarget*mRotateOy;
	target = rotatedTarget*worldMatrix;
	update();
}
void Camera::RotateOx(float dir) {
	Matrix mRotateOx;
	mRotateOx.SetRotationX(rotateSpeed*deltaTime*dir);
	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 rotatedLocalUp = localUp*mRotateOx;
	up = rotatedLocalUp*worldMatrix;
	up = up.Normalize();
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget*mRotateOx;
	target = rotatedTarget*worldMatrix;
	update();
}
void Camera::RotateOz(float dir) {
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Matrix mRotateOz;
	mRotateOz.SetRotationZ(rotateSpeed*deltaTime*dir);
	Vector4 rotatedTarget = localTarget*mRotateOz;
	target = rotatedTarget*worldMatrix;
	update();
}
Matrix Camera::getRotation() {
	Matrix R;
	R.m[0][0] = xAxis.x; R.m[0][1] = xAxis.y; R.m[0][2] = xAxis.z; R.m[0][3] = 0;
	R.m[1][0] = yAxis.x; R.m[1][1] = yAxis.y; R.m[1][2] = yAxis.z; R.m[1][3] = 0;
	R.m[2][0] = zAxis.x; R.m[2][1] = zAxis.y; R.m[2][2] = zAxis.z; R.m[2][3] = 0;
	R.m[3][0] = 0; R.m[3][1] = 0; R.m[3][2] = 0; R.m[3][3] = 1;
	return R;
}
Matrix Camera::getTranspose() {
	Matrix T;
	T.SetTranslation(position.x, position.y, position.z);
	return T;
}
void Camera::UpdateAxis() {
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	GLfloat wx = xAxis.w; GLfloat wy = yAxis.w; GLfloat wz = zAxis.w;
	Vector3 auxz = Vector3(zAxis.x, zAxis.y, zAxis.z);
	Vector3 auxy = Vector3(yAxis.x, yAxis.y, yAxis.z);
	Vector3 auxx = Vector3(xAxis.x, xAxis.y, xAxis.z);
	auxx = auxz.Cross(auxy).Normalize();
	xAxis = Vector4(auxx, wx);
	yAxis = Vector4(auxy, wy);
	zAxis = Vector4(auxz, wz);
}
void Camera::updateWorld() {
	Matrix R = getRotation();
	Matrix T = getTranspose();
	worldMatrix = R*T;
}
void Camera::updateView() {
	Matrix R = getRotation();
	Matrix T;
	T.SetTranslation(-position.x, -position.y, -position.z);
	Matrix Rt = R.Transpose();

	viewMatrix = T * Rt;

}
void Camera::update() {
	UpdateAxis();
	updateView();
	updateWorld();

}

Camera::Camera()
{
	position = Vector4(0.0f, 0.0f, -1.0f, 1.0f);
	target = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	up = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	fov = 45.0f;
	Near = 0.2f;
	Far = 5000.0f;
	moveSpeed = 1.0f;
	rotateSpeed = 0.4f;
	update();
}


Camera::~Camera()
{
}