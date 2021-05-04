#include "Vector3.h"
#include "math.h"

Vector3::Vector3() : m_x(0),m_y(0),m_z(0) {}

Vector3::Vector3(double x, double y, double z)
	: m_x(x),m_y(y),m_z(z) {}

Vector3::~Vector3() {}

// Getter and Setter
double Vector3::getX()
{
	return m_x;
}

void Vector3::setX(double valX)
{
	m_x = valX;
}

double Vector3::getY()
{
	return m_y;
}

void Vector3::setY(double valY)
{
	m_y = valY;
}

double Vector3::getZ()
{
	return m_z;
}

void Vector3::setZ(double valZ)
{
	m_z = valZ;
}

void Vector3::operator=(const Vector3& v) {
	m_x = v.m_x;
	m_y = v.m_y;
	m_z = v.m_z;
}

double Vector3::Magnitude() const
{
	return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

double Vector3::squared_length() const
{
	return m_x * m_x + m_y * m_y + m_z * m_z;
}

void Vector3::make_unit_vector()
{
	double k = 1.0 / sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
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

Vector3 operator*(const Vector3& v, double t)
{
	return Vector3(v.m_x * t, v.m_y * t, v.m_z * t);
}

Vector3 operator/(const Vector3& v, double t)
{
	return Vector3(v.m_x / t, v.m_y / t, v.m_z / t);
}

Vector3 operator*(double t, const Vector3& v1)
{
	return Vector3(t * v1.m_x, t * v1.m_y, t * v1.m_z);
}

Vector3 operator/(double t, const Vector3& v)
{
	return Vector3(t / v.m_x, t / v.m_y, t / v.m_z);
}

double Vector3::ProduitScalaire(const Vector3& v1, const Vector3& v2)
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

Vector3& Vector3::operator*=(const double t)
{
	m_x += t;
	m_y += t;
	m_z += t;
	return *this;
}

Vector3& Vector3::operator/=(const double t)
{
	double k = 1.0 / t;
	m_x += k;
	m_y += k;
	m_z += k;
	return *this;
}

Vector3 Vector3::lenght(const Vector3 v)
{
	return v / v.Magnitude();
}

Vector3 Vector3::Negative()
{
	return Vector3(-m_x, -m_y, -m_z);
}

Vector3 Vector3::vectAdd(const Vector3& v1)
{
	return Vector3(m_x + v1.m_x, m_y + v1.m_y, m_z + v1.m_z);
}

Vector3 Vector3::vectMult(double t)
{
	return Vector3(m_x * t, m_y * t, m_z * t);
}

Vector3 Vector3::Normalize()
{
	double magnitude = sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
	return Vector3(m_x / magnitude, m_y / magnitude, m_z / magnitude);
}

double Vector3::dotProduct(const Vector3& v1)
{
	return m_x * v1.m_x + m_y * v1.m_y + m_z * v1.m_z;
}

Vector3 Vector3::crossProduct(const Vector3& v1)
{
	return Vector3((m_y * v1.m_z - m_z * v1.m_y),
		(-(m_x * v1.m_z - m_z * v1.m_x)),
		(m_x * v1.m_y - m_y * v1.m_x));
}