#pragma once
#include "gameNode.h"
#include"ObjectPool.h"
#include<set>
using namespace std;

class player;




struct tagBullet
{
	image* img;
	MYRECT rc;
	float x,y;
	float angle;
	float radius;
	float speed;
	float fireX,fireY;
	bool isFire;
};

class bullet: public gameNode
{
private:
	player* _player;
	
	objectPooling<tagBullet>* _opBullet;
	animation* _ani;
	animation* _ani2;
	string _imgName;
	float _range;
	int _bulletMax;
	int _money=0;

public:
	bullet(int missileMax);
	virtual ~bullet() {};

	virtual HRESULT init(string imgName, float range);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float angle, float speed);
	void fire(POINTFLOAT pos, float angle, float speed);

	void move();

	int getMoney() { return _money; }
	void setMoney(int money) { _money = money; }

	void setBulletColl(MYRECT rc);

	void removeBullet(int arrNum);

	//함수를 호출하면 오브젝트 풀링 값을 리턴해준다.
	objectPooling<tagBullet>* getOpBullet() { return _opBullet; }

	void setPlayerMemoryAddressLink(player* play) { _player = play; }
	

};

