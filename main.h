#pragma once
#include"gameNode.h"
#include "player.h"
#include"enemyManager.h"
#include"boss.h"
#include"objects.h"

class main:public gameNode
{
private:
	image* _backMorning;
	image* _backNight;
	image* _floor;
	image* _forest;
	image* _barrier;
	image* _obj1;
	image* _obj2;
	MYRECT _floorrc;
	MYRECT _obj1rc;
	MYRECT _obj2rc;
	

	bool _mapOnOff;
	

	int _count;
	bool _nm;
	player* _mainPlayer;
	enemyManager* _enemyManager;
	boss* _boss;
	objects* _objects;
public:

	HRESULT init();
	void release();
	void update();
	void render();
	
	void setMainMemoryAddressLink(main* main) { _boss->setMainMemoryAddressLink(main); }
	void setBossMemoryAddressLink() { _boss = _enemyManager->getBossMemoryAddressLink(); }

	//bool getMapOnOff() { return _mapOnOff; }

	MYRECT getObj1() { return _obj1rc; }
	MYRECT getObj2() { return _obj2rc; }
};

