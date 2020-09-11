#pragma once
#include "gameNode.h"
#include"boss.h"
#include"enemy.h"
#include"bullet.h"
#include"objects.h"

class player;


class enemyManager : public gameNode
{
private:
	boss* _boss;
	objects* _ob;
	player* _player;
	bullet* _bullet;
	vector<enemy*> _vEnemy;
	int _barrier = 0;
	int _count=0;

public:
	enemyManager() {};
	~enemyManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void setBarrier(int barr) { _barrier += barr; }
	int getBarrier() { return _barrier; }

	void bossBulletFire();

	void setPlayerMemoryAddressLink(player* play) { _player = play;}
	void setBulletLink(player* play) {
		_bullet->setPlayerMemoryAddressLink(play);
	}

	void setObjMemoryAddressLink(objects* obj) { _ob = obj; }
	boss* getBossMemoryAddressLink() { return _boss; }
	bullet* getBulletMemoryAddressLink() { return _bullet; }
	
};

