#pragma once

#ifndef PHYSICALCOMPONENT_H
#define PHYSICALCOMPONENT_H


#include "OGame/Entity/SpatialComponent.h"
#include "Box2D.h"

namespace OG {
	class PhysicalComponent : public SpatialComponent
	{
	public:
		PhysicalComponent(Actor* _owner);
		
		virtual ~PhysicalComponent();
		virtual void registerComponent();


		b2Body* getCollider();
		void createCollider(b2BodyDef* _body_def, b2FixtureDef* _fix_def, b2World*  _world);

		b2BodyDef* getBodyDef() { return &body_def; }
		b2PolygonShape* getBodyShape() { return &body_shape; }
		b2FixtureDef* getFixtureyDef() { return &fixture_def; }

		void setPosition(const glm::vec3& _Position) override;
		void setRotation(const glm::mat3& _rotation) override;
		void setTransform(const glm::mat4& _transform) override;



	protected:
		PhysicalComponent();

		virtual void update();

		b2Body* collider = nullptr;
		b2BodyDef body_def;
		b2FixtureDef fixture_def;
		b2PolygonShape body_shape;
		
	private:
		
	};
}


#endif // !1