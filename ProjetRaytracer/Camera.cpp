#include "Camera.h"

Camera::Camera()
{
	m_CameraPosition = Vector3(0, 0, 0);
	m_CameraDirection = Vector3(0, 0, 1);
	m_CameraRight = Vector3(0, 0, 0);
	m_CameraDown = Vector3(0, 0, 0);
}

Camera::Camera(const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d)
	: m_CameraPosition(a)
	, m_CameraDirection(b)
	, m_CameraRight(c)
	, m_CameraDown(d)
{}

// Setter
void Camera::setCameraPosition(Vector3 v1)
{
	m_CameraPosition = v1;
}

void Camera::setCameraDirection(Vector3 v1)
{
	m_CameraDirection = v1;
}

void Camera::setCameraRight(Vector3 v1)
{
	m_CameraRight = v1;
}

void Camera::setCameraDown(Vector3 v1)
{
	m_CameraDown = v1;
}

Vector3 Camera::CameraPosition() const
{
	return m_CameraPosition;
}

Vector3 Camera::CameraDirection() const
{
	return m_CameraDirection;
}

Vector3 Camera::CameraRight() const
{
	return m_CameraRight;
}

Vector3 Camera::CameraDown() const
{
	return m_CameraDown;
}