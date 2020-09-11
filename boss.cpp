#include "stdafx.h"
#include "boss.h"
#include"main.h"

HRESULT boss::init()
{
	_boss.img = IMAGEMANAGER->findImage("�������̵�");
	_boss.rc.set(1600,600, 1900, 960);
	
	
	_water.img = IMAGEMANAGER->findImage("�ĵ�");
	
	_fTimer = 0;
	bossAniSetting();
	_boss.ani->start();
	
	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	
	isBossHumming();

	switch (_boss.pat)
	{
	case BOSSPAT::ATT1:
		if (_boss.img != IMAGEMANAGER->findImage("�������̵�"))
		{
			_boss.img = IMAGEMANAGER->findImage("�������̵�");
			_boss.ani = new animation;
			_boss.ani->init(IMAGEMANAGER->findImage("�������̵�")->getWidth(), IMAGEMANAGER->findImage("�������̵�")->getHeight(),
				IMAGEMANAGER->findImage("�������̵�")->getFrameWidth(), IMAGEMANAGER->findImage("�������̵�")->getFrameHeight());
			_boss.ani->setDefPlayFrame(false, true);
			_boss.ani->setFPS(1);
			_boss.ani->start();
		}

		break;
		
	case BOSSPAT::ATT2:
		if (_boss.img != IMAGEMANAGER->findImage("�������̵�"))
		{
			_boss.img = IMAGEMANAGER->findImage("�������̵�");
			_boss.ani = new animation;
			_boss.ani->init(IMAGEMANAGER->findImage("�������̵�")->getWidth(), IMAGEMANAGER->findImage("�������̵�")->getHeight(),
				IMAGEMANAGER->findImage("�������̵�")->getFrameWidth(), IMAGEMANAGER->findImage("�������̵�")->getFrameHeight());
			_boss.ani->setDefPlayFrame(false, true);
			_boss.ani->setFPS(1);
			_boss.ani->start();
		}

		break;
		
	case BOSSPAT::ATT3:
		if (_boss.img != IMAGEMANAGER->findImage("�������̵�"))
		{
			_boss.img = IMAGEMANAGER->findImage("�������̵�");
			_boss.ani = new animation;
			_boss.ani->init(IMAGEMANAGER->findImage("�������̵�")->getWidth(), IMAGEMANAGER->findImage("�������̵�")->getHeight(),
				IMAGEMANAGER->findImage("�������̵�")->getFrameWidth(), IMAGEMANAGER->findImage("�������̵�")->getFrameHeight());
			_boss.ani->setDefPlayFrame(false, true);
			_boss.ani->setFPS(1);
			_boss.ani->start();
		}

		break;
		
	case BOSSPAT::HIT:
		if (_boss.img != IMAGEMANAGER->findImage("�����ǰ�"))
		{
			_boss.img = IMAGEMANAGER->findImage("�����ǰ�");
			_boss.ani = new animation;
			_boss.ani->init(IMAGEMANAGER->findImage("�����ǰ�")->getWidth(), IMAGEMANAGER->findImage("�����ǰ�")->getHeight(),
				IMAGEMANAGER->findImage("�����ǰ�")->getFrameWidth(), IMAGEMANAGER->findImage("�����ǰ�")->getFrameHeight());
			_boss.ani->setDefPlayFrame(false, false);
			_boss.ani->setFPS(1);
			_boss.ani->start();
		}
		if (!_boss.ani->isPlay())
		{
			_boss.pat = BOSSPAT::ATT1;
		}

		break;
		
	case BOSSPAT::SUMMON:
		if (_boss.img != IMAGEMANAGER->findImage("������ų"))
		{
			_boss.img = IMAGEMANAGER->findImage("������ų");
			_boss.ani = new animation;
			_boss.ani->init(IMAGEMANAGER->findImage("������ų")->getWidth(), IMAGEMANAGER->findImage("������ų")->getHeight(),
				IMAGEMANAGER->findImage("������ų")->getFrameWidth(), IMAGEMANAGER->findImage("������ų")->getFrameHeight());
			_boss.ani->setDefPlayFrame(false, false);
			_boss.ani->setFPS(1);
			_boss.ani->start();
			
			
		}
		if (!_boss.ani->isPlay())
		{
			_boss.pat = BOSSPAT::ATT1;
		}
		break;

	default:
		break;
	}
	
	
	
	_boss.ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	
	
}

void boss::render()
{

	//CAMERA->rectangle(getMemDC(), _boss.rc);
	CAMERA->aniRender(getMemDC(),_boss.rc.left, _boss.rc.top, _boss.img, _boss.ani);
	//CAMERA->aniRender(getMemDC(), _water.rc.left, _water.rc.top, _water.img, _water.ani);
	
}

void boss::bossAniSetting()
{
	_boss.ani = new animation;
	_boss.ani->init(IMAGEMANAGER->findImage("�������̵�")->getWidth(), IMAGEMANAGER->findImage("�������̵�")->getHeight(),
		IMAGEMANAGER->findImage("�������̵�")->getFrameWidth(), IMAGEMANAGER->findImage("�������̵�")->getFrameHeight());
	_boss.ani->setDefPlayFrame(false, true);
	_boss.ani->setFPS(1);

	//_water.ani = new animation;
	//_water.ani->init(IMAGEMANAGER->findImage("�ĵ�")->getWidth(), IMAGEMANAGER->findImage("�ĵ�")->getHeight(),
	//	IMAGEMANAGER->findImage("�ĵ�")->getFrameWidth(), IMAGEMANAGER->findImage("�ĵ�")->getFrameHeight());
	//_water.ani->setDefPlayFrame(false, true);
	//_water.ani->setFPS(1);
}

bool boss::isBossHumming()
{

	_fTimer += TIMEMANAGER->getElapsedTime();

	if (_fTimer >= 1.f)
	{
		_fTimer = 0;

		return true;
	}
	return false;
}

bool boss::bulletCountFire()
{
	_fireCount++;
	if (_fireCount % 3 == 0)
	{
		_fireCount = 0;
		return true;
	}
	return false;
}

void boss::attBullet(player * player, bullet * bullet)
{
	int Y;
	Y = RND->getFromFloatTo(_boss.rc.top-30, _boss.rc.top + 50);
	bullet->fire((_boss.rc.left+_boss.rc.right)/2,Y,
		getAngle((_boss.rc.left + _boss.rc.right) / 2, Y, player->getRect().right, player->getRect().bottom),
		2.0f);
}

void boss::attBulletObj(objects* obj, bullet * bullet)
{
	int Y;
	Y = RND->getFromFloatTo(_boss.rc.top - 50, _boss.rc.top + 50);
	bullet->fire((_boss.rc.left + _boss.rc.right) / 2, Y,
		getAngle((_boss.rc.left + _boss.rc.right) / 2, Y, obj->getObj2().right,obj->getObj2().top),2.0f);
}

