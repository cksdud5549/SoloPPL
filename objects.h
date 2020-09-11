#pragma once
#include"gameNode.h"

class bullet;
class enemyManager;
class player;


class objects: public gameNode

{
private:
	image* _backMorning;
	image* _backNight;
	image* _floor;
	image* _forest;
	image* _barrier;
	image* _obj1;
	image* _obj2;


	image* _tree;
	MYRECT _treerc;
	


	MYRECT _obj1rc;
	MYRECT _obj2rc;
	MYRECT _deathZone;

	bool _dungeon=false;
	bool _shop=false;
	int _treeCount=0;
	player* _player;
	bullet* _bullet;
	enemyManager* _enemyManager;
public:

	HRESULT init();
	void release();
	void update();
	void render();


	bool getDungeon() { return _dungeon; }
	bool getShop() { return _shop; }


	MYRECT getObj1() { return _obj1rc; }
	MYRECT getObj2() { return _obj2rc; }
	MYRECT getTree() { return _treerc; }
	void setBulletMemoryAddressLink(bullet* bul) { _bullet = bul; }
	void setEmMemoryAddressLink(enemyManager* enemy) { _enemyManager = enemy; }
	void setPlayerMemoryAddressLink(player* play) { _player = play; }

};

