#include "Vector3.h"
#include "math.h"

Vector3::Vector3() : m_x(0),m_y(0),m_z(0) {}

Vector3::Vector3(float x, float y, float z)
	: m_x(x),m_y(y),m_z(z) {}

Vector3::~Vector3() {}

// Getter and Setter
float Vector3::getX()
{
	return m_x;
}

void Vector3::setX(float valX)
{
	m_x = valX;
}

float Vector3::getY()
{
	return m_y;
}

void Vector3::setY(float valY)
{
	m_y = valY;
}

float Vector3::getZ()
{
	return m_z;
}

void Vector3::setZ(float valZ)
{
	m_z = valZ;
}

void Vector3::operator=(const Vector3& v) {
	m_x = v.m_x;
	m_y = v.m_y;
	m_z = v.m_z;
}

float Vector3::lenght() const
{
	return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

float Vector3::squared_length() const
{
	return m_x * m_x + m_y * m_y + m_z * m_z;
}

void Vector3::make_unit_vector()
{
	float k = 1.0 / sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	m_x *= k;
	m_y *= k;
	m_z *= k;
}

Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.m_x + v2.m_x, v1.m_y + v2.m_y, v1.m_z + v2.m_z);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.m_x - v2.m_x, v1.m_y - v2.m_y, v1.m_z - v2.m_z);
}

Vector3 operator*(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.m_x * v2.m_x, v1.m_y * v2.m_y, v1.m_z * v2.m_z);
}

Vector3 operator/(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.m_x / v2.m_x, v1.m_y / v2.m_y, v1.m_z / v2.m_z);
}

Vector3 operator*(const Vector3& v, float t)
{
	return Vector3(v.m_x * t, v.m_y * t, v.m_z * t);
}

Vector3 operator/(const Vector3& v, float t)
{
	return Vector3(v.m_x / t, v.m_y / t, v.m_z / t);
}

Vector3 operator*(float t, const Vector3& v1)
{
	return Vector3(t * v1.m_x, t * v1.m_y, t * v1.m_z);
}

Vector3 operator/(float t, const Vector3& v)
{
	return Vector3(t / v.m_x, t / v.m_y, t / v.m_z);
}

float Vector3::ProduitScalaire(const Vector3& v1, const Vector3& v2)
{
	return v1.m_x * v2.m_x + v1.m_y * v2.m_y + v1.m_z * v2.m_z;
}

Vector3 Vector3::ProduitVectoriel(const Vector3& v1, const Vector3& v2)
{
	return Vector3((v1.m_y * v2.m_z - v1.m_z * v2.m_y),
					(-(v1.m_x*v2.m_z - v1.m_z*v2.m_x)),
					(v1.m_x*v2.m_y - v1.m_y*v2.m_x));
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	m_x -= v.m_x;
	m_y -= v.m_y;
	m_z -= v.m_z;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
	m_x *= v.m_x;
	m_y *= v.m_y;
	m_z *= v.m_z;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
	m_x /= v.m_x;
	m_y /= v.m_y;
	m_z /= v.m_z;
	return *this;
}

Vector3& Vector3::operator*=(const float t)
{
	m_x += t;
	m_y += t;
	m_z += t;
	return *this;
}

Vector3& Vector3::operator/=(const float t)
{
	float k = 1.0 / t;
	m_x += k;
	m_y += k;
	m_z += k;
	return *this;
}

Vector3 Vector3::unit_vector(const Vector3 v)
{
	return v / v.lenght();
}