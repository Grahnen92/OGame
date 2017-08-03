#pragma once
#include "b2RayCastCallbackHit.h"

#include <vector>

struct HitInfo
{
	bool blocking_hit;
	b2Fixture* fixture;
	b2Vec2 point;
	b2Vec2 normal;
	float32 fraction;

	HitInfo(bool _bh, b2Fixture* _fix, const b2Vec2& _p, const b2Vec2& _n, float32 _fr) {
		blocking_hit = _bh;
		fixture = _fix;
		point = _p;
		normal = _n;
		fraction = _fr;
	}
};

class b2RayCastCallbackClosestHit :
	public b2RayCastCallbackHit
{
public:
	b2RayCastCallbackClosestHit();
	~b2RayCastCallbackClosestHit();

	virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2&normal, float32 fraction);

	virtual void reset();

	virtual HitInfo* getClosestHit();
protected:

	std::vector<HitInfo> hits;

};

