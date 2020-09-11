#pragma once
#include"gameNode.h"



class player;

enum class MOBSTATE
{
	IDLE,
	RUN,
	HIT,
	DIE
};
struct tagMonster
{
	MYRECT rc;
	POINTFLOAT center;
	image* img;
	int count=0, index=0;
	bool live;
	MOBSTATE state;
};

class enemy:public gameNode
{
private:
	
	tagMonster _monster;

	bool _isActive;

	int _barrier=0;
	player* _player;


public:
	enemy() {}
	virtual ~enemy() {};
	static enemy* create();
	void createMonster();
	void moveMonster();
	void mobState();

	int getBarrCount() { return _barrier; }
	void setBarrCount(int count) { _barrier = count; }

	virtual void update();
	virtual void render();
	
	void enemyActive();

	void enemyDeactive();

	void setPlayerMemoryAddressLink(player* play) { _player = play; }

};

