#pragma once
class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update() = 0;

private:

	class GameInstance* game_instance;

};

