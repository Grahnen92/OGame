#pragma once

#include "Box2D.h"

class b2RayCastCallbackHit : public b2RayCastCallback
{
public:
	b2RayCastCallbackHit();
	virtual ~b2RayCastCallbackHit();

	virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2&normal, float32 fraction);
	
	virtual void reset();

	bool didHit() { return did_hit; }

	void setFixtureToIgnore(b2Fixture* _ignore_fixture);

protected:

	b2Fixture* ignore_fixture;

	bool did_hit;
};

