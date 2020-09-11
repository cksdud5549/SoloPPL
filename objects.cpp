#include "stdafx.h"
#include "objects.h"
#include"bullet.h"
#include"enemyManager.h"
#include"player.h"


HRESULT objects::init()
{
	{
		_backMorning = IMAGEMANAGER->findImage("낮배경");
		_backNight = IMAGEMANAGER->findImage("밤배경");
		_floor = IMAGEMANAGER->findImage("바닥");
		_forest = IMAGEMANAGER->findImage("수풀");
		_barrier = IMAGEMANAGER->findImage("배리어");
		_obj1 = IMAGEMANAGER->findImage("건물1");
		_obj2 = IMAGEMANAGER->findImage("건물2");
		_tree = IMAGEMANAGER->findImage("배리어");

		_obj1rc.set(190, 826, 10 + IMAGEMANAGER->findImage("건물1")->getWidth(), 726 + IMAGEMANAGER->findImage("건물1")->getHeight());
		_obj2rc.set(470, 785, 350 + IMAGEMANAGER->findImage("건물2")->getWidth(), 585 + IMAGEMANAGER->findImage("건물2")->getHeight());
		_deathZone.set(190, 500, 550, 868);
	}

	return S_OK;
}

void objects::release()
{
}

void objects::update()
{
	_bullet->setBulletColl(_treerc);
	
	if (isCollision(_player->getRect(), _obj2rc) && KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_dungeon = true;
	}//플레이어와 던전포탈 상호작용

	if (_enemyManager->getBarrier() >= 20 && isCollision(_player->getRect(), _obj1rc) && KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_shop = true;
	}//플레이어와 상점상호작용

	cout << _enemyManager->getBarrier() << endl;
	if (_shop)
	{
		
		_treerc.set(1300, 968 - 1011, 1400, 900);
		_treeCount++;
		if (_treeCount % 360 == 0)
		{
			_treerc.set(-500, -500, -500, -500);
			_treeCount = 0;
			_enemyManager->setBarrier(-_enemyManager->getBarrier());
			_shop = false;
		}

	}
}

void objects::render()
{
	if (_shop)
	{
		CAMERA->render(getMemDC(), _tree, 600, 968 - 1011);
	}
	

	CAMERA->render(getMemDC(), _forest, 0, 673);
	CAMERA->render(getMemDC(), _floor, 0, 868);
	CAMERA->render(getMemDC(), _obj1, 100, 726);
	CAMERA->render(getMemDC(), _obj2, 400, 585);
	
	if (KEYMANAGER->isStayKeyDown('M'))
	{
		
		CAMERA->rectangle(getMemDC(), _treerc);
		CAMERA->rectangle(getMemDC(), _deathZone);
		CAMERA->rectangle(getMemDC(), _obj1rc);
		CAMERA->rectangle(getMemDC(), _obj2rc);
	}
}
