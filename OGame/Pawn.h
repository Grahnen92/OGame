#pragma once

#ifndef PAWN_H
#define PAWN_H

#include "Actor.h"

class PlayerController;
class InputComponent;

namespace OG {
	class Pawn : public Actor
	{

		friend PlayerController;

	public:
		
		Pawn(GameInstance* _gi);

		virtual ~Pawn();



		PlayerController* getOwningPlayer() { return owning_player; }

	protected:
		Pawn();
		void becomeHost(PlayerController* _player);

		void createPlayerInputComponent();
		virtual void SetupPlayerInputComponent() = 0;
		void destroyPlayerInputComponent() { delete input_component; }

		PlayerController* owning_player = nullptr;
		InputComponent* input_component = nullptr;

		virtual void update(float delta_time);
	};

}

#endif