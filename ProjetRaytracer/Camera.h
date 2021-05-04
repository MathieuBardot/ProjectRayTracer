#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

class Camera
{
public:
	Camera();
	Camera(const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d);

	//Gette and Setter
	void setCameraPosition(Vector3 v1);
	void setCameraDirection(Vector3 v1);
	void setCameraRight(Vector3 v1);
	void setCameraDown(Vector3 v1);

	Vector3 CameraPosition() const;
	Vector3 CameraDirection() const;
	Vector3 CameraRight() const;
	Vector3 CameraDown() const;

private:
	Vector3 m_CameraPosition;
	Vector3 m_CameraDirection;
	Vector3 m_CameraRight;
	Vector3 m_CameraDown;
};

#endif // !CAMERA_H