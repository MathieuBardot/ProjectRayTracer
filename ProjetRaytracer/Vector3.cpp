#include "Vector3.h"
#include "math.h"

Vector3::Vector3() : m_X(0),m_Y(0),m_Z(0) {}

Vector3::Vector3(double x, double y, double z)
	: m_X(x),m_Y(y),m_Z(z) {}

Vector3::~Vector3() {}

// Getter and Setter
double Vector3::getX()
{
	return m_X;
}

void Vector3::setX(double valX)
{
	m_X = valX;
}

double Vector3::getY()
{
	return m_Y;
}

void Vector3::setY(double valY)
{
	m_Y = valY;
}

double Vector3::getZ()
{
	return m_Z;
}

void Vector3::setZ(double valZ)
{
	m_Z = valZ;
}

void Vector3::operator=(const Vector3& v) {
	m_X = v.m_X;
	m_Y = v.m_Y;
	m_Z = v.m_Z;
}

double Vector3::Magnitude() const
{
	return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
}

double Vector3::squared_length() const
{
	return m_X * m_X + m_Y * m_Y + m_Z * m_Z;
}

void Vector3::make_unit_vector()
{
	double k = 1.0 / sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
	m_X *= k;
	m_Y *= k;
	m_Z *= k;
}

Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.m_X + v2.m_X, v1.m_Y + v2.m_Y, v1.m_Z + v2.m_Z);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.m_X - v2.m_X, v1.m_Y - v2.m_Y, v1.m_Z - v2.m_Z);
}

Vector3 operator*(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.m_X * v2.m_X, v1.m_Y * v2.m_Y, v1.m_Z * v2.m_Z);
}

Vector3 operator/(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.m_X / v2.m_X, v1.m_Y / v2.m_Y, v1.m_Z / v2.m_Z);
}

Vector3 operator*(const Vector3& v, double t)
{
	return Vector3(v.m_X * t, v.m_Y * t, v.m_Z * t);
}

Vector3 operator/(const Vector3& v, double t)
{
	return Vector3(v.m_X / t, v.m_Y / t, v.m_Z / t);
}

Vector3 operator*(double t, const Vector3& v1)
{
	return Vector3(t * v1.m_X, t * v1.m_Y, t * v1.m_Z);
}

Vector3 operator/(double t, const Vector3& v)
{
	return Vector3(t / v.m_X, t / v.m_Y, t / v.m_Z);
}

double Vector3::ProduitScalaire(const Vector3& v1, const Vector3& v2)
{
	return v1.m_X * v2.m_X + v1.m_Y * v2.m_Y + v1.m_Z * v2.m_Z;
}

Vector3 Vector3::ProduitVectoriel(const Vector3& v1, const Vector3& v2)
{
	return Vector3((v1.m_Y * v2.m_Z - v1.m_Z * v2.m_Y),
					(-(v1.m_X*v2.m_Z - v1.m_Z*v2.m_X)),
					(v1.m_X*v2.m_Y - v1.m_Y*v2.m_X));
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	m_X += v.m_X;
	m_Y += v.m_Y;
	m_Z += v.m_Z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	m_X -= v.m_X;
	m_Y -= v.m_Y;
	m_Z -= v.m_Z;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
	m_X *= v.m_X;
	m_Y *= v.m_Y;
	m_Z *= v.m_Z;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
	m_X /= v.m_X;
	m_Y /= v.m_Y;
	m_Z /= v.m_Z;
	return *this;
}

Vector3& Vector3::operator*=(const double t)
{
	m_X += t;
	m_Y += t;
	m_Z += t;
	return *this;
}

Vector3& Vector3::operator/=(const double t)
{
	double k = 1.0 / t;
	m_X += k;
	m_Y += k;
	m_Z += k;
	return *this;
}

Vector3 Vector3::lenght(const Vector3 v)
{
	return v / v.Magnitude();
}

Vector3 Vector3::Negative()
{
	return Vector3(-m_X, -m_Y, -m_Z);
}

Vector3 Vector3::vectAdd(const Vector3& v1)
{
	return Vector3(m_X + v1.m_X, m_Y + v1.m_Y, m_Z + v1.m_Z);
}

Vector3 Vector3::vectMult(double t)
{
	return Vector3(m_X * t, m_Y * t, m_Z * t);
}

Vector3 Vector3::Normalize()
{
	double magnitude = sqrt((m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z));
	return Vector3(m_X / magnitude, m_Y / magnitude, m_Z / magnitude);
}

double Vector3::dotProduct(const Vector3& v1)
{
	return m_X * v1.m_X + m_Y * v1.m_Y + m_Z * v1.m_Z;
}

Vector3 Vector3::crossProduct(const Vector3& v1)
{
	return Vector3((m_Y * v1.m_Z - m_Z * v1.m_Y),
		(-(m_X * v1.m_Z - m_Z * v1.m_X)),
		(m_X * v1.m_Y - m_Y * v1.m_X));
}