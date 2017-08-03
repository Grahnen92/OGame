#pragma once

#ifndef ENTITY_H
#define ENTITY_H

class GameInstance;
class Level;

namespace OG {
	class Entity
	{
	public:
		Entity();
		virtual ~Entity() = 0;

		Level* getLevel();
		GameInstance* getGameInstance();

	protected:
		virtual void update(float delta_time) = 0;

		GameInstance* game_instance;
	};
}

#endif // !ENTITY_H
