#pragma once
#include "gameNode.h"
class dungeon : public gameNode
{


public:

	HRESULT init();
	void release();
	void update();
	void render();

};

