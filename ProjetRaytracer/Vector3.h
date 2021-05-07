#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
	Vector3();
	Vector3(double x, double y, double z);
	~Vector3();

	//Getter and Setter
	double getX();
	void setX(double valX);
	double getY();
	void setY(double valY);
	double getZ();
	void setZ(double valZ);

	void operator=(const Vector3& v);
	double operator[] (int i) const { return m_X; };
	double& operator[] (int i) { return m_X; };

	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(const Vector3& v);
	Vector3& operator/=(const Vector3& v);
	Vector3& operator*=(const double t);
	Vector3& operator/=(const double t);

	friend Vector3 operator+(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator-(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator*(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator/(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator*(const Vector3& v1, double t);
	friend Vector3 operator/(const Vector3& v1, double t);
	friend Vector3 operator*(double t, const Vector3& v1);
	friend Vector3 operator/(double t, const Vector3& v1);

	double Magnitude() const;
	double squared_length() const;
	void make_unit_vector();
	Vector3 lenght(const Vector3 v);
	Vector3 Negative();
	double ProduitScalaire(const Vector3& v1, const Vector3& v2);
	Vector3 ProduitVectoriel(const Vector3& v1, const Vector3& v2);
	Vector3 vectAdd(const Vector3& v1);
	Vector3 vectMult(double t);
	Vector3 Normalize();
	double dotProduct(const Vector3& v1);
	Vector3 crossProduct(const Vector3& v1);

private:
	double m_X;
	double m_Y; 
	double m_Z;
};

#endif // !VECTOR3_H