#pragma once
#include"gameNode.h"


enum class SHASTATE
{
	ATTACK,
	FALL,
	RUN,
	NON
};

enum class STATE
{
	IDLE,
	JUMP,
	FALL,
	IDLE_TO_RUN,
	RUN,
	RUN_TO_IDLE,
	ATTACK,
	DIE
};
struct PLAYER
{
	image* image;
	STATE state;
	POINTFLOAT center;
	MYRECT rc;
	
	
	float jump;
	float maxJump;
	float gravite;
	float speed;
	bool right;
	string now_Image;
};
struct tagShadow
{
	image* img[10];
	SHASTATE state;


};
struct tagPlay
{
	POINT LT;
	int count;
	POINTFLOAT XY;
};

class player: public gameNode
{
private:
	tagShadow _shadow;
	tagPlay _place[10];
	int _alpha;
	int _test;
	animation* shaAttack;
	animation* shaFall;
	animation* shaRun;

	
	PLAYER _player;

	RECT _floor;

	
	animation* idle;
	animation* jump;
	animation* fall;
	animation* idleToRun;
	animation* run;
	animation* runToIdle;
	animation* attack;
	animation* die;

	animation* slash;
	RECT _slashRc;
	RECT _slashRc1;
	RECT _slashRc2;
	MYRECT _sla;
	MYRECT _sla1;
	MYRECT _sla2;
	image* _slashImage;

	
	
public:
	player() {};
	~player() {};
	HRESULT init();
	void release();
	void update();
	void render();

	void updateShadow();
	void renderShadow();

	void anisetting();
	void stateACT(STATE state);
	void stateProsses();

	MYRECT getRect() { return _player.rc; }
	MYRECT getSlaRect() { return _sla; }
	MYRECT getSla1Rect() { return _sla1; }
	MYRECT getSla2Rect() { return _sla2; }
	void setRectX(float X) {
		_player.center.x = X - (_player.image->getFrameWidth()/2);
		//_player.rc.left = _player.rc.right - IMAGEMANAGER->findImage(_player.now_Image)->getFrameWidth();
	}
	
	void setRectY(float Y) { 
		_player.center.y = Y-(_player.image->getFrameHeight()/2);
		//_player.rc.top = _player.rc.bottom - IMAGEMANAGER->findImage(_player.now_Image)->getFrameHeight();
	}
	
	void setGravite(float gravite) {
		_player.gravite = gravite;
	}

};

