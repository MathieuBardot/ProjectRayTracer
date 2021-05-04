#ifndef HITABLELIST_H
#define HITABLELIST_H

#include "hitable.h"

class hitable_list : public hitable
{
public:
	hitable_list() = default;
	hitable_list(std::vector<std::shared_ptr<hitable>> l) { m_list = l; };
	~hitable_list() = default;
	virtual bool hit(const Ray &r, double tmin, double tmax, hit_record &rec) const;

	void AddElement(std::shared_ptr<hitable> hit)
	{
		m_list.push_back(hit);
	}
	void Clear()
	{
		m_list.clear();
	}

	std::vector<std::shared_ptr<hitable>> m_list;
};

inline bool hitable_list::hit(const Ray &r, double tmin, double tmax, hit_record &rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	double closet_so_far = tmax;
	for (auto i = 0; i < m_list.size(); i++)
	{
		if (m_list.at(i)->hit(r, tmin, closet_so_far, temp_rec))
		{
			hit_anything = true;
			closet_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}

#endif // !HITABLELIST_H
