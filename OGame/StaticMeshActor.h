#pragma once

#ifndef STATICMESHACTOR_H
#define STATICMESHACTOR_H

#include "Actor.h"

namespace OG {
	class MeshComponent;
}

class StaticMeshActor :
	public OG::Actor
{
public:
	StaticMeshActor();
	StaticMeshActor(GameInstance* _gi);
	~StaticMeshActor();

	OG::MeshComponent* mesh;

protected:

	void update(float delta_time) final;
};

#endif // !STATICMESHACTOR_H