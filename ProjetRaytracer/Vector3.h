#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	//Getter and Setter
	float getX();
	void setX(float valX);
	float getY();
	void setY(float valY);
	float getZ();
	void setZ(float valZ);

	void operator=(const Vector3& v);
	float operator[] (int i) const { return m_x; };
	float& operator[] (int i) { return m_x; };

	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(const Vector3& v);
	Vector3& operator/=(const Vector3& v);
	Vector3& operator*=(const float t);
	Vector3& operator/=(const float t);

	friend Vector3 operator+(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator-(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator*(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator/(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator*(const Vector3& v1, float t);
	friend Vector3 operator/(const Vector3& v1, float t);
	friend Vector3 operator*(float t, const Vector3& v1);
	friend Vector3 operator/(float t, const Vector3& v1);

	float lenght() const;
	float squared_length() const;
	void make_unit_vector();
	Vector3 unit_vector(const Vector3 v);
	float ProduitScalaire(const Vector3& v1, const Vector3& v2);
	Vector3 ProduitVectoriel(const Vector3& v1, const Vector3& v2);

protected:
	float m_x;
	float m_y; 
	float m_z;
};

#endif // !VECTOR3_H