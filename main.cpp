#include "stdafx.h"
#include "main.h"

HRESULT main::init()
{
	_mapOnOff = true;
	
	{
		_backMorning = IMAGEMANAGER->findImage("³·¹è°æ");
		_backNight = IMAGEMANAGER->findImage("¹ã¹è°æ");
		_floor = IMAGEMANAGER->findImage("¹Ù´Ú");
		_forest = IMAGEMANAGER->findImage("¼öÇ®");
		_barrier = IMAGEMANAGER->findImage("¹è¸®¾î");
		_obj1 = IMAGEMANAGER->findImage("°Ç¹°1");
		_obj2 = IMAGEMANAGER->findImage("°Ç¹°2");

		_floorrc.set(0, 868, 1500, 968);
	}
	_count = 0;
	_nm = false;

	_objects = new objects;
	_objects->init();

	_mainPlayer = new player;
	_mainPlayer->init();

	_enemyManager = new enemyManager;
	_enemyManager->setPlayerMemoryAddressLink(_mainPlayer);
	_enemyManager->init();

	_enemyManager->setObjMemoryAddressLink(_objects);
	_objects->setEmMemoryAddressLink(_enemyManager);
	_objects->setBulletMemoryAddressLink(_enemyManager->getBulletMemoryAddressLink());
	_objects->setPlayerMemoryAddressLink(_mainPlayer);

	setBossMemoryAddressLink();
	

	return S_OK;

}

void main::release()
{
}

void main::update()
{
	_objects->update();
	
	
	{
		_mainPlayer->update();
		if (_mainPlayer->getRect().bottom >= _floorrc.top)
		{
			_mainPlayer->setRectY(_floorrc.top);
			_mainPlayer->setGravite(0.0f);
		}
		if (_mainPlayer->getRect().right > _floorrc.right)
		{
			_mainPlayer->setRectX(_floorrc.right);
		}
	}  
	//¸ŞÀÎÇÃ·¹ÀÌ¾î


	{
		if (_nm)
		{
			_count++;
			if (_count % 30 == 0)
			{
				_nm = false;
				_count = 0;
			}
		}
		if (!_nm)
		{
			_count++;
			if (_count % 30 == 0)
			{
				_nm = true;
				_count = 0;
			}
		}
	}
	//¹è°æ³·¹ã

	_enemyManager->update();

	if (_objects->getDungeon())
	{
		_mapOnOff = false;
	}
	
	
	
	
}

void main::render()
{
	if(_nm)CAMERA->render(getMemDC(), _backMorning, 0, 0);
	if(!_nm)CAMERA->render(getMemDC(), _backNight, 0, 0);
	
	_objects->render();
	
	//CAMERA->rectangle(getMemDC(), _floorrc);
	_mainPlayer->render();
	_enemyManager->render();
}
