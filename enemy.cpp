#include "stdafx.h"
#include "enemy.h"
#include"player.h"

enemy* enemy::create()
{
	enemy* e = new enemy();
	e->createMonster();

	return e;
}

void enemy::createMonster()
{
	int rx,ry;
	rx = RND->getFromIntTo(1300, 1500);
	ry = RND->getFromIntTo(200, 700);
	_monster.center.x = rx;
	_monster.center.y = ry;
	_monster.img = IMAGEMANAGER->findImage("¸÷¾ÆÀÌµé");
	_monster.img->setFrameX(4);
	_monster.img->setFrameY(1);
	_monster.live = true;
	_monster.rc.set(_monster.center.x - (_monster.img->getFrameWidth() / 2),
		_monster.center.y - (_monster.img->getFrameHeight() / 2),
		_monster.center.x + (_monster.img->getFrameWidth() / 2),
		_monster.center.y + (_monster.img->getFrameHeight() / 2));

	_isActive = false;
}

void enemy::moveMonster()
{
	if (!_isActive)_monster.rc.set(-555, -555, -555, -555);


	if (_monster.rc.bottom < 868)
	{
		_monster.state = MOBSTATE::IDLE;
		
	}
	else if(_monster.state!=MOBSTATE::HIT&& _monster.state != MOBSTATE::DIE)
	{
		_monster.state = MOBSTATE::RUN;
		
	}

	if (isCollision(_monster.rc, _player->getSlaRect()) || isCollision(_monster.rc, _player->getSla1Rect()) || isCollision(_monster.rc, _player->getSla2Rect()))
	{
		_monster.state = MOBSTATE::HIT;
	}

	mobState();

	_monster.rc.set(_monster.center.x - (_monster.img->getFrameWidth() / 2),
		_monster.center.y - (_monster.img->getFrameHeight() / 2),
		_monster.center.x + (_monster.img->getFrameWidth() / 2),
		_monster.center.y + (_monster.img->getFrameHeight() / 2));
}

void enemy::mobState()
{
	switch (_monster.state)
	{
	case MOBSTATE::IDLE:
		_monster.center.y += 8;
		_monster.img = IMAGEMANAGER->findImage("¸÷¾ÆÀÌµé");
		_monster.count++;
		if (_monster.count % 20 == 0)
		{
			if (_monster.index < 0)_monster.index = 4;
			_monster.img->setFrameX(_monster.index);
			_monster.index--;
		}
		break;
	

	case MOBSTATE::RUN:
		_monster.center.x -= 10;
		_monster.img = IMAGEMANAGER->findImage("¸÷·±");
		_monster.img->setFrameY(1);
		_monster.count++;
		if (_monster.count % 5 == 0)
		{
			if (_monster.index < 0)_monster.index = 7;
			_monster.img->setFrameX(_monster.index);
			_monster.index--;
			_monster.count = 0;
		}
		break;


	case MOBSTATE::HIT:
		_monster.center.x += 1;
		_monster.img = IMAGEMANAGER->findImage("¸÷ÇÇ°Ý");
		_monster.img->setFrameY(0);
		_monster.count++;

		if (_monster.count % 10 == 0)
		{
			if (_monster.index < 0)
			{
				_monster.state = MOBSTATE::DIE;
				
			}
			_monster.img->setFrameX(_monster.index);
			_monster.index--;
			_monster.count = 0;
			
		}
		break;

	case MOBSTATE::DIE:
		_monster.img = IMAGEMANAGER->findImage("¸÷»ç¸Á");
		if(!SOUNDMANAGER->isPlaySound("¸÷¼Ò¸®"))SOUNDMANAGER->play("¸÷¼Ò¸®", 1.0f);
		_barrier++;
		_monster.img->setFrameY(0);
		_monster.count++;
		_monster.img->setFrameX(0);
		enemyDeactive();
		cout << _isActive << endl;
		cout << "»ç¸Á" << endl;
		
		
		break;


	default:
		break;
	}
}

void enemy::update()
{
	if (_isActive)
	{
		moveMonster();
	}

	
}

void enemy::render()
{
	if (!_isActive) return;

	//CAMERA->rectangle(getMemDC(), _monster.rc);
	CAMERA->frameRender(getMemDC(), _monster.img, _monster.rc.left, _monster.rc.top);
	

}

void enemy::enemyActive()
{
	_isActive = true;

}

void enemy::enemyDeactive()
{
	_isActive = false;
	int rx, ry;
	rx = RND->getFromIntTo(1300, 1500);
	ry = RND->getFromIntTo(200, 700);
	_monster.center.x = rx;
	_monster.center.y = ry;
	_monster.img = IMAGEMANAGER->findImage("¸÷¾ÆÀÌµé");
	_monster.img->setFrameX(4);
	_monster.img->setFrameY(1);
	_monster.rc.set(_monster.center.x - (_monster.img->getFrameWidth() / 2),
		_monster.center.y - (_monster.img->getFrameHeight() / 2),
		_monster.center.x + (_monster.img->getFrameWidth() / 2),
		_monster.center.y + (_monster.img->getFrameHeight() / 2));

	//¶³¾îÁ®¾ß ÇÒ ÁÂÇ¥·Î ÃÊ±âÈ­


}
