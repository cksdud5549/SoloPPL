#pragma once
#include "gameNode.h"
#include "main.h"
#include"dungeon.h"
#include"enemyManager.h"
#pragma comment(lib, "dsound.lib")



#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;

enum class MAP
{
	MAIN_MAP,
	DUNGEON,
	END,
	START
};

class playGround : public gameNode
{
private:
	main* _main;
	dungeon* _dungeon;
	bool _pil = false;
	animation* _pilani;
	MAP mapstate;
	bool Tlqkf = false;
	bool _end = false;

public:

	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imageSound();//가독성용 이미지 사운드 생성
	
};

