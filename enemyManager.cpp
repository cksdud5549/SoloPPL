#include "stdafx.h"
#include "enemyManager.h"
#include"player.h"
HRESULT enemyManager::init()
{
	_boss = new boss;
	_boss->init();
	_bullet = new bullet(5000);
	_bullet->init("ÃÑ¾Ë1",1500);
	setBulletLink(_player);
	for (int i = 0; i < 10; ++i)
	{
		auto e = enemy::create();

		e->setPlayerMemoryAddressLink(_player);

		_vEnemy.push_back(e);
	}

	return S_OK;
}

void enemyManager::release()
{
	

}

void enemyManager::update()
{
	//cout << _bullet->getMoney() << endl;;
	
	_boss->update();
	bossBulletFire();
	_bullet->update();
	if (_bullet->getMoney() > 100)
	{
		_boss->setBossState(BOSSPAT::SUMMON);
		for (int i = 0; i < 10; ++i)
		{
			_vEnemy[i]->enemyActive();
		}
		_bullet->setMoney(0);
	}


	for (auto e : _vEnemy)
	{
		e->update();
		setBarrier(e->getBarrCount());
		e->setBarrCount(0);
	}
	
}

void enemyManager::render()
{
	_boss->render();

	_bullet->render();

	for (auto e : _vEnemy)
		e->render();
}

void enemyManager::bossBulletFire()
{
	int i;
	i = RND->getInt(2);
	if (_boss->bulletCountFire())
	{
		if(i==0)_boss->attBulletObj(_ob, _bullet);
		if(i==1)_boss->attBullet(_player, _bullet);
	}

	if (_boss->isBossHumming())
	{
		_bullet->fire(_boss->getRect().left, _boss->getRect().top, getAngle(_boss->getRect().left, _boss->getRect().top, _player->getRect().left, _player->getRect().top), 1.4f);
	}
}
