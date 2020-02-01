#pragma once
#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H



#include "Ogame/Game/GameInstance.h"
class OGameInstance : public GameInstance
{
public:
	OGameInstance();
	~OGameInstance();

	void createGame();
	void createLevels();

protected:


private:
};

#endif // !1