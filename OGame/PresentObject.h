#pragma once
#include "SpatialObject.h"
#include "Box2D.h"

class PresentObject :
	public virtual SpatialObject
{
public:
	PresentObject();
	virtual ~PresentObject();

	b2Body* getCollider();
	void createCollider(b2BodyDef* _body_def, b2FixtureDef* _fix_def, b2World*  _world);

	b2BodyDef* getBodyDef() { return &body_def; }
	
	b2FixtureDef* getFixtureyDef() { return &fixture_def; }

	void setPosition(const glm::vec3 & _Position) override;

	void update();

protected:
	b2Body* collider = nullptr;
	b2BodyDef body_def;
	b2FixtureDef fixture_def;
};

