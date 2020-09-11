#include "stdafx.h"
#include "objects.h"
#include"bullet.h"
#include"enemyManager.h"
#include"player.h"


HRESULT objects::init()
{
	{
		_backMorning = IMAGEMANAGER->findImage("�����");
		_backNight = IMAGEMANAGER->findImage("����");
		_floor = IMAGEMANAGER->findImage("�ٴ�");
		_forest = IMAGEMANAGER->findImage("��Ǯ");
		_barrier = IMAGEMANAGER->findImage("�踮��");
		_obj1 = IMAGEMANAGER->findImage("�ǹ�1");
		_obj2 = IMAGEMANAGER->findImage("�ǹ�2");
		_tree = IMAGEMANAGER->findImage("�踮��");

		_obj1rc.set(190, 826, 10 + IMAGEMANAGER->findImage("�ǹ�1")->getWidth(), 726 + IMAGEMANAGER->findImage("�ǹ�1")->getHeight());
		_obj2rc.set(470, 785, 350 + IMAGEMANAGER->findImage("�ǹ�2")->getWidth(), 585 + IMAGEMANAGER->findImage("�ǹ�2")->getHeight());
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
	}//�÷��̾�� ������Ż ��ȣ�ۿ�

	if (_enemyManager->getBarrier() >= 20 && isCollision(_player->getRect(), _obj1rc) && KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_shop = true;
	}//�÷��̾�� ������ȣ�ۿ�

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
