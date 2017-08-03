#include "b2RayCastCallbackClosestHit.h"



b2RayCastCallbackClosestHit::b2RayCastCallbackClosestHit()
{
	did_hit = false;
	ignore_fixture = nullptr;
}


void b2RayCastCallbackClosestHit::reset()
{
	did_hit = false;
	ignore_fixture = nullptr;
	hits.clear();
}

b2RayCastCallbackClosestHit::~b2RayCastCallbackClosestHit()
{

}


float32 b2RayCastCallbackClosestHit::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2&normal, float32 fraction)
{
	b2Fixture* ignore_itr = ignore_fixture;
	while (ignore_itr) {
		if (ignore_itr == fixture)
			return -1;

		ignore_itr = ignore_itr->GetNext();
	}

	did_hit = true;
	if (hits.size() > 0)
	{
		if (hits.back().fraction > fraction)
		{
			hits.back().blocking_hit = true;
			hits.back().fixture = fixture;
			hits.back().fraction = fraction;
			hits.back().normal = normal;
			hits.back().point = point;
		}
	}
	else {
		
		hits.push_back(HitInfo(true, fixture, point, normal, fraction));
	}

	return fraction;
}

HitInfo* b2RayCastCallbackClosestHit::getClosestHit() {
	if (did_hit)
		return &hits.back();
	else
		nullptr;
}