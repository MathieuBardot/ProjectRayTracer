#ifndef HITABLE_H
#define HITABLE_H

#include "Ray.h"

struct hit_record
{
	double t;
	class Vector3 p;
	class Vector3 normal;
};

class hitable
{
public:
	hitable() = default;
	~hitable() = default;
	virtual bool hit(const Ray &r, double t_min, double tmax, hit_record &rec) const = 0;
};

#endif // !HITABLE_H

