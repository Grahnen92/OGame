#pragma once

#ifndef ACTORCOMPONENT_H
#define ACTORCOMPONENT_H

namespace OG {

	class Actor;

	class ActorComponent
	{
	public:
		
		virtual ~ActorComponent();

		ActorComponent(Actor* _owner);

		virtual void registerComponent();

		bool should_update = false;
		virtual void update();

		void destroy();

	protected:

		ActorComponent();

		Actor* owner;

	private:
		

		

	};
}

#endif // !ACTORCOMPONENT_H





