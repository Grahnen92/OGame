#pragma once

#ifndef STATICMESHCOMPONENT_H
#define STATICMESHCOMPONENT_H



#include "MeshComponent.h"

namespace OG {
	class StaticMeshComponent :
		public MeshComponent
	{
	public:
		StaticMeshComponent();
		virtual ~StaticMeshComponent();

		void registerComponent() {}
	protected: 

		void update() {}
	};
}

#endif // !STATICMESHCOMPONENT_H
