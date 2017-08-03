#include "b2RaycastCallbackHit.h"



b2RayCastCallbackHit::b2RayCastCallbackHit() : did_hit(false), ignore_fixture(nullptr)
{
	
}

void b2RayCastCallbackHit::reset()
{
	did_hit = false;
	ignore_fixture = nullptr;
}

b2RayCastCallbackHit::~b2RayCastCallbackHit()
{
}


float32 b2RayCastCallbackHit::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2&normal, float32 fraction)
{
	b2Fixture* ignore_itr = ignore_fixture;
	while (ignore_itr) {
		if (ignore_itr == fixture)
			return -1;

		ignore_itr = ignore_itr->GetNext();
	}

	did_hit = true;
	return 0.f;
}

void b2RayCastCallbackHit::setFixtureToIgnore(b2Fixture* _ignore_fixture) {
	ignore_fixture = _ignore_fixture;
}
