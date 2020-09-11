#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	_player.center.x = WINSIZEX/2;
	_player.center.y = 840;
	_player.rc.set(_player.center.x - 10, _player.center.y - 45, _player.center.x + 10, _player.center.y + 45);
	_player.speed = 5;
	_player.gravite = 0.0f;
	_player.jump = 10;
	_player.maxJump = 0;
	_player.right = true;
	_player.image = IMAGEMANAGER->findImage("플레이어아이들");
	_player.state = STATE::IDLE;
	_player.now_Image = "플레이어아이들";
	_slashImage = IMAGEMANAGER->findImage("플레이어검기");

	_shadow.state = SHASTATE::NON;
	for (int i = 0; i < 10; ++i)
	{
		_place[i].count = 0;
	}
	anisetting();
	stateACT(_player.state);
	idle->start();
	
	



	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2048-WINSIZEX, 968-WINSIZEY);
	return S_OK;
}

void player::release()
{
}

void player::update()
{

	updateShadow();



	if (_player.state != STATE::ATTACK)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_player.gravite += 15;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_player.right = false;
			if (_player.right)
			{
				_player.center.x += _player.speed;
			}
			else _player.center.x -= _player.speed;
			if (_player.state == STATE::IDLE)
			{
				_player.state = STATE::IDLE_TO_RUN;
				stateACT(_player.state);
			}

		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_player.right = false;
			if (_player.state != STATE::ATTACK && _player.state != STATE::JUMP&&_player.state != STATE::FALL)
			{
				_player.state = STATE::RUN_TO_IDLE;
			}
			stateACT(_player.state);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_player.right = true;
			_player.center.x += _player.speed;
			if (_player.state == STATE::IDLE)
			{
				_player.state = STATE::IDLE_TO_RUN;
				stateACT(_player.state);
			}
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_player.right = true;
			if (_player.state != STATE::ATTACK&&_player.state != STATE::JUMP&&_player.state != STATE::FALL)
			{
				_player.state = STATE::RUN_TO_IDLE;
			}
			stateACT(_player.state);
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_player.state = STATE::JUMP;
			stateACT(_player.state);
		}
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			if (_player.state != STATE::ATTACK)
			{
				_player.state = STATE::ATTACK;
				SOUNDMANAGER->play("칼소리", 0.5f);
				stateACT(_player.state);
			}
		}
	}

	//if (_player.gravite > 1)_player.state = STATE::FALL;

	
	idle->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
	idleToRun->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
	jump->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
	fall->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
	run->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
	runToIdle->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
	attack->frameUpdate(TIMEMANAGER->getElapsedTime() * 50);
	die->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
	slash->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);

	
	//CAMERA->setX(2048);
	//CAMERA->setY(965);
	if (_player.rc.right < 1500)
	{
		CAMERA->setX(_player.center.x);
		CAMERA->setY(_player.center.y);
	}
	

	stateProsses();
	if (_player.gravite >= 15)_player.gravite = 50;
	_player.center.y += _player.gravite;
	_player.gravite += 0.1f;

	_player.rc.set(_player.center.x - (IMAGEMANAGER->findImage(_player.now_Image)->getFrameWidth() / 2)
		, _player.center.y - (IMAGEMANAGER->findImage(_player.now_Image)->getFrameHeight() / 2),
		_player.center.x + (IMAGEMANAGER->findImage(_player.now_Image)->getFrameWidth() / 2)
		, _player.center.y + (IMAGEMANAGER->findImage(_player.now_Image)->getFrameHeight() / 2));
	//플레이어업데이트정보
   
	if (_player.right)
	{
		_sla.set(_slashRc.left, _slashRc.top, _slashRc.right + 150, _slashRc.bottom);
		_sla1.set(_slashRc1.left, _slashRc1.top, _slashRc1.right + 150, _slashRc1.bottom);
		_sla2.set(_slashRc2.left, _slashRc2.top, _slashRc2.right + 150, _slashRc2.bottom);
	}
	if (!_player.right)
	{
		_sla.set(_slashRc.left - 200, _slashRc.top, _slashRc.right - 50, _slashRc.bottom);
		_sla1.set(_slashRc1.left - 200, _slashRc1.top, _slashRc1.right - 50, _slashRc1.bottom);
		_sla2.set(_slashRc2.left - 200, _slashRc2.top, _slashRc2.right - 50, _slashRc2.bottom);
	}
	//공격판정렉트
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		//cout << IMAGEMANAGER->findImage("플레이어착지")->getFrameWidth() << endl;
		//cout << IMAGEMANAGER->findImage("플레이어착지")->getFrameHeight() << endl;
		//cout << (int) _shadow.state << endl;
		//cout << fall->getFrameHeight() << endl;
		//cout << _player.now_Image << endl;
	}

	//잔상업데이트
	if (_shadow.state == SHASTATE::ATTACK)
	{
		//cout << (int)_shadow.state << endl;
		if (_player.state!=STATE::ATTACK)_shadow.state = SHASTATE::NON;
	}
	if (_shadow.state == SHASTATE::FALL)
	{
		//cout << (int)_shadow.state << endl;
		if (_player.state!=STATE::FALL)_shadow.state = SHASTATE::NON;
	}
	if (_shadow.state == SHASTATE::RUN)
	{
		//cout << (int)_shadow.state << endl;
		if (_player.state!=STATE::RUN)_shadow.state = SHASTATE::NON;
	}
	{
		_place[0].count++;
		if (_place[0].count % 10 == 0 && _place[0].count != 0)
		{
			for (int i = 0; i < 10; ++i)
			{
				_place[0].LT.x = _player.rc.left;
				_place[0].LT.y = _player.rc.top;
			}
			_place[0].count = 0;
		}
		_place[1].count++;
		if (_place[1].count % 20 == 0 && _place[1].count != 0)
		{
			_place[1].LT.x = _player.rc.left;
			_place[1].LT.y = _player.rc.top;

			_place[1].count = 0;
		}
		/*_place[2].count++;
		if (_place[2].count % 30 == 0 && _place[2].count != 0)
		{
			_place[2].LT.x = _player.rc.left;
			_place[2].LT.y = _player.rc.top;

			_place[2].count = 0;
		}
		_place[3].count++;
		if (_place[3].count % 40 == 0 && _place[3].count != 0)
		{
			_place[3].LT.x = _player.rc.left;
			_place[3].LT.y = _player.rc.top;

			_place[3].count = 0;
		}
		_place[4].count++;
		if (_place[4].count % 50 == 0 && _place[4].count != 0)
		{
			_place[4].LT.x = _player.rc.left;
			_place[4].LT.y = _player.rc.top;

			_place[4].count = 0;
		}
		_place[5].count++;
		if (_place[5].count % 55 == 0 && _place[5].count != 0)
		{
			_place[5].LT.x = _player.rc.left;
			_place[5].LT.y = _player.rc.top;

			_place[5].count = 0;
		}
		_place[6].count++;
		if (_place[6].count % 60 == 0 && _place[6].count != 0)
		{
			_place[6].LT.x = _player.rc.left;
			_place[6].LT.y = _player.rc.top;

			_place[6].count = 0;
		}
		_place[7].count++;
		if (_place[7].count % 65 == 0 && _place[7].count != 0)
		{
			_place[7].LT.x = _player.rc.left;
			_place[7].LT.y = _player.rc.top;

			_place[7].count = 0;
		}
		_place[8].count++;
		if (_place[8].count % 70 == 0 && _place[8].count != 0)
		{
			_place[8].LT.x = _player.rc.left;
			_place[8].LT.y = _player.rc.top;

			_place[8].count = 0;
		}
		_place[9].count++;
		if (_place[9].count % 75 == 0 && _place[9].count != 0)
		{
			_place[9].LT.x = _player.rc.left;
			_place[9].LT.y = _player.rc.top;

			_place[9].count = 0;
		}
		*/
	}
	_alpha -= 1;
	for (int i = 0; i < 10; ++i)
	{
		if (_place[i].LT.x == 0 || _place[i].LT.y == 0)
		{
			_place[i].LT.x = -500;
			_place[i].LT.y = -500;
		}
	}
	shaAttack->frameUpdate(TIMEMANAGER->getElapsedTime() *500);
	shaFall->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
	shaRun->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
	//잔상업데이트
}

void player::render()
{
	//IMAGEMANAGER->findImage("플레이어런")->frameRender(getMemDC(), 100, 100,2,0);
	//CAMERA->rectangle(getMemDC(), _player.rc);
	renderShadow();
	switch (_player.state)
	{
	case STATE::IDLE:
		CAMERA->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.image, idle);
		break;

	case STATE::JUMP:
		CAMERA->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.image, jump);
		break;

	case STATE::ATTACK:
		CAMERA->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.image, attack);

		break;

	case STATE::DIE:
		CAMERA->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.image, die);
		break;

	case STATE::FALL:
		CAMERA->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.image, fall);
		break;

	case STATE::IDLE_TO_RUN:
		CAMERA->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.image, idleToRun);
		break;

	case STATE::RUN:
		CAMERA->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.image, run);
		break;

	case STATE::RUN_TO_IDLE:
		CAMERA->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.image, runToIdle);
		break;
	default:
		break;
	}
	
	//CAMERA->rectangle(getMemDC(),_sla );
	
	if (_player.right)
	{
		CAMERA->aniRender(getMemDC(), _slashRc.left, _slashRc.top, _slashImage, slash);
		CAMERA->aniRender(getMemDC(), _slashRc1.left, _slashRc1.top, _slashImage, slash);
		CAMERA->aniRender(getMemDC(), _slashRc2.left, _slashRc2.top, _slashImage, slash);
	}
	if (!_player.right)
	{
		CAMERA->aniRender(getMemDC(), _slashRc.left - IMAGEMANAGER->findImage("플레이어검기")->getFrameWidth(), _slashRc.top, _slashImage, slash);
		CAMERA->aniRender(getMemDC(), _slashRc1.left - IMAGEMANAGER->findImage("플레이어검기")->getFrameWidth(), _slashRc2.top, _slashImage, slash);
		CAMERA->aniRender(getMemDC(), _slashRc1.left - IMAGEMANAGER->findImage("플레이어검기")->getFrameWidth(), _slashRc2.top, _slashImage, slash);
	}
	
}

void player::updateShadow()
{
	for (int i = 0; i < 10; ++i)
	{
		_place[i].XY.x = _place[i].LT.x + 30;
		_place[i].XY.y = _place[i].LT.y + 30;
	}
	if (_shadow.state == SHASTATE::ATTACK)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (_player.right)
			{
				
				_shadow.img[i] = IMAGEMANAGER->findImage("플레이어공격잔상");
				shaAttack->setPlayFrame(0, 6, false, false);
				_alpha = 255;
				shaAttack->start();
			}

			else
			{
				
				_shadow.img[i] = IMAGEMANAGER->findImage("플레이어공격잔상");
				shaAttack->setPlayFrame(13, 7, false, false);
				_alpha = 255;
				shaAttack->start();
			}
		}
		if (!shaAttack->isPlay())shaAttack->stop();
	}
	if (_shadow.state == SHASTATE::FALL)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (_player.right)
			{
				
				_shadow.img[i] = IMAGEMANAGER->findImage("플레이어착지잔상");
				shaFall->setPlayFrame(0, 3, false, false);
				_alpha = 255;
				shaFall->start();
			}

			else
			{
				
				_shadow.img[i] = IMAGEMANAGER->findImage("플레이어착지잔상");
				shaFall->setPlayFrame(7, 4, false, false);
				_alpha = 255;
				shaFall->start();
			}
		}
	}
	if (_shadow.state == SHASTATE::RUN)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (_player.right)
			{
				//cout << "1" << endl;
				_shadow.img[i] = IMAGEMANAGER->findImage("플레이어런잔상");
				shaRun->setPlayFrame(0, 9, false, false);
				_alpha = 255;
				shaRun->start();
			}

			else
			{
				//cout << "2" << endl;
				_shadow.img[i] = IMAGEMANAGER->findImage("플레이어런잔상");
				shaRun->setPlayFrame(19, 10, false, false);
				_alpha = 255;
				shaRun->start();
			}

			if (!shaRun->isPlay())shaRun->stop();
		}
	}
	
	
	
}

void player::renderShadow()
{
	switch (_shadow.state)
	{
	case SHASTATE::ATTACK:
		
		for (int i = 0; i < 10; ++i)
		{
			//CAMERA->alphaFrameRender(getMemDC(), _place[i].LT.x, _place[i].LT.y, attack->getFramePos().x, attack->getFramePos().y, _shadow.img[i], _alpha);
			CAMERA->aniRender(getMemDC(), _place[i].LT.x, _place[i].LT.y, _shadow.img[i], attack);
		}
		break;

	case SHASTATE::FALL:
		//cout << "시발" << endl;
		for (int i = 0; i < 10; ++i)
		{
			CAMERA->aniRender(getMemDC(), _place[i].LT.x, _place[i].LT.y, _shadow.img[i], fall);
		}

		break;

	case SHASTATE::RUN:
		//cout << "좆같네" << endl;
		for (int i = 0; i < 10; ++i)
		{
			CAMERA->aniRender(getMemDC(), _place[i].LT.x, _place[i].LT.y, _shadow.img[i], run);
		}
		break;


	default:
		break;
	}
	
	//if (_player.state == STATE::ATTACK)
	//{
	//	CAMERA->aniRender(getMemDC(), _player.rc.left-50, _player.rc.top + 30, _shadow.img, attack);
	//}
}

void player::anisetting()
{
	idle		=new animation;
	jump		=new animation;
	fall		=new animation;
	idleToRun	=new animation;
	run			=new animation;
	runToIdle	=new animation;
	attack		=new animation;
	die			=new animation;
	slash		=new animation;

	idle->init(IMAGEMANAGER->findImage("플레이어아이들")->getWidth() , IMAGEMANAGER->findImage("플레이어아이들")->getHeight(),
		IMAGEMANAGER->findImage("플레이어아이들")->getFrameWidth(), IMAGEMANAGER->findImage("플레이어아이들")->getFrameHeight());
	idle->setDefPlayFrame(false, true);
	idle->setFPS(1);

	jump->init(IMAGEMANAGER->findImage("플레이어점프")->getWidth(), IMAGEMANAGER->findImage("플레이어점프")->getHeight(), 
		IMAGEMANAGER->findImage("플레이어점프")->getFrameWidth(), IMAGEMANAGER->findImage("플레이어점프")->getFrameHeight());
	jump->setDefPlayFrame(false, false);
	jump->setFPS(1);

	fall->init(IMAGEMANAGER->findImage("플레이어착지")->getWidth(), IMAGEMANAGER->findImage("플레이어착지")->getHeight(),
		IMAGEMANAGER->findImage("플레이어착지")->getFrameWidth(), IMAGEMANAGER->findImage("플레이어착지")->getFrameHeight());
	fall->setDefPlayFrame(false, false);
	fall->setFPS(1);

	idleToRun->init(IMAGEMANAGER->findImage("플레이어런시작")->getWidth(), IMAGEMANAGER->findImage("플레이어런시작")->getHeight(),
		IMAGEMANAGER->findImage("플레이어런시작")->getFrameWidth(), IMAGEMANAGER->findImage("플레이어런시작")->getFrameHeight());
	idleToRun->setDefPlayFrame(false, false);
	idleToRun->setFPS(1);

	run->init(IMAGEMANAGER->findImage("플레이어런")->getWidth() , IMAGEMANAGER->findImage("플레이어런")->getHeight(),
		IMAGEMANAGER->findImage("플레이어런")->getFrameWidth(), IMAGEMANAGER->findImage("플레이어런")->getFrameHeight());
	run->setDefPlayFrame(false, true);
	run->setFPS(1);

	runToIdle->init(IMAGEMANAGER->findImage("플레이어런끝")->getWidth(), IMAGEMANAGER->findImage("플레이어런끝")->getHeight(),
		IMAGEMANAGER->findImage("플레이어런끝")->getFrameWidth(), IMAGEMANAGER->findImage("플레이어런끝")->getFrameHeight());
	runToIdle->setDefPlayFrame(false, false);
	runToIdle->setFPS(1);

	attack->init(IMAGEMANAGER->findImage("플레이어공격")->getWidth(), IMAGEMANAGER->findImage("플레이어공격")->getHeight(),
		IMAGEMANAGER->findImage("플레이어공격")->getFrameWidth(), IMAGEMANAGER->findImage("플레이어공격")->getFrameHeight());
	attack->setDefPlayFrame(false, false);
	attack->setFPS(1);

	die->init(IMAGEMANAGER->findImage("플레이어사망")->getWidth(), IMAGEMANAGER->findImage("플레이어사망")->getHeight(),
		IMAGEMANAGER->findImage("플레이어사망")->getFrameWidth(), IMAGEMANAGER->findImage("플레이어사망")->getFrameHeight());
	die->setDefPlayFrame(false, false);
	die->setFPS(1);

	slash->init(IMAGEMANAGER->findImage("플레이어검기")->getWidth(), IMAGEMANAGER->findImage("플레이어검기")->getHeight(),
		IMAGEMANAGER->findImage("플레이어검기")->getFrameWidth(), IMAGEMANAGER->findImage("플레이어검기")->getFrameHeight());
	slash->setDefPlayFrame(false, false);
	slash->setFPS(1);


	shaAttack = new animation;
	shaRun = new animation;
	shaFall = new animation;

	shaAttack->init(IMAGEMANAGER->findImage("플레이어공격잔상")->getWidth(), IMAGEMANAGER->findImage("플레이어공격잔상")->getHeight(),
		IMAGEMANAGER->findImage("플레이어공격잔상")->getFrameWidth(), IMAGEMANAGER->findImage("플레이어공격잔상")->getFrameHeight());
	shaAttack->setDefPlayFrame(true, true);
	shaAttack->setFPS(1);

	shaFall->init(IMAGEMANAGER->findImage("플레이어착지잔상")->getWidth(), IMAGEMANAGER->findImage("플레이어착지잔상")->getHeight(),
		IMAGEMANAGER->findImage("플레이어착지잔상")->getFrameWidth(), IMAGEMANAGER->findImage("플레이어착지잔상")->getFrameHeight());
	shaFall->setDefPlayFrame(true, true);
	shaFall->setFPS(1);

	shaRun->init(IMAGEMANAGER->findImage("플레이어런잔상")->getWidth(), IMAGEMANAGER->findImage("플레이어런잔상")->getHeight(),
		IMAGEMANAGER->findImage("플레이어런잔상")->getFrameWidth(), IMAGEMANAGER->findImage("플레이어런잔상")->getFrameHeight());
	shaRun->setDefPlayFrame(true, true);
	shaRun->setFPS(1);

	_alpha = 255;
}

void player::stateACT(STATE state)
{
	
	switch (state)
	{
	case STATE::IDLE:
		
		if (_player.right)	  
		{
			_player.image = IMAGEMANAGER->findImage("플레이어아이들");
			_player.now_Image = "플레이어아이들";
			idle->setPlayFrame(0, 10, false, true);
			idle->start();
			
		}
		else
		{
			_player.image = IMAGEMANAGER->findImage("플레이어아이들");
			_player.now_Image = "플레이어아이들";
			idle->setPlayFrame(21, 11, false, true);
			idle->start();
		}

		break;
	case STATE::JUMP:
		if (_player.right)
		{
			_player.image = IMAGEMANAGER->findImage("플레이어점프");
			_player.now_Image = "플레이어점프";
			jump->setPlayFrame(0, 4, false, false);
			jump->start();
		}
		else
		{
			_player.image = IMAGEMANAGER->findImage("플레이어점프");
			_player.now_Image = "플레이어점프";
			jump->setPlayFrame(7, 4, false, false);
			jump->start();
		}

		break;
	case STATE::FALL:
		
		_shadow.state = SHASTATE::FALL;
		if (_player.right)
		{
			_player.image = IMAGEMANAGER->findImage("플레이어착지");
			_player.now_Image = "플레이어착지";
			fall->setPlayFrame(0, 3, false, false);
			fall->start();
		}
		else
		{
			_player.image = IMAGEMANAGER->findImage("플레이어착지");
			_player.now_Image = "플레이어착지";
			fall->setPlayFrame(7, 4, false, false);
			fall->start();
		}

		break;
	case STATE::IDLE_TO_RUN:
		
		if (_player.right)
		{
			_player.image = IMAGEMANAGER->findImage("플레이어런시작");
			_player.now_Image = "플레이어런시작";
			idleToRun->setPlayFrame(0, 3, false, false);
			idleToRun->start();
		
		}
		else
		{
			_player.now_Image = "플레이어런시작"; 
			_player.image = IMAGEMANAGER->findImage("플레이어런시작");
			idleToRun->setPlayFrame(7, 4, false, false);
			idleToRun->start();
			
		}

		break;
	case STATE::RUN:
		
		_shadow.state = SHASTATE::RUN;
		if (_player.right)
		{
			_player.image = IMAGEMANAGER->findImage("플레이어런");
			_player.now_Image = "플레이어런";
			run->setPlayFrame(0, 9, false, true);
			run->start();
		}
		else
		{
			_player.image = IMAGEMANAGER->findImage("플레이어런");
			_player.now_Image = "플레이어런";
			run->setPlayFrame(19, 10, false, true);
			run->start();
			
		}

		break;
	case STATE::RUN_TO_IDLE:
		if (_player.right)
		{
			_player.image = IMAGEMANAGER->findImage("플레이어런끝");
			_player.now_Image = "플레이어런끝";
			runToIdle->setPlayFrame(0, 4, false, false);
			runToIdle->start();
		}
		else
		{
			_player.image = IMAGEMANAGER->findImage("플레이어런끝");
			_player.now_Image = "플레이어런끝";
			runToIdle->setPlayFrame(9, 5, false, false);
			runToIdle->start();
		}

		break;
	case STATE::ATTACK:
		
		if (_player.right)
		{
			_player.gravite = 3;
			_player.center.x += 100;
			//_player.center.y -= 100;
			_player.image = IMAGEMANAGER->findImage("플레이어공격");
			_player.now_Image = "플레이어공격";
			attack->setPlayFrame(0, 6, false, false);
			attack->start();
			
			slash->setPlayFrame(0, 5, false, false);
			slash->start();
			_slashRc = RectMakeCenter(_player.center.x - 100, _player.center.y, 50, IMAGEMANAGER->findImage("플레이어검기")->getFrameHeight());
			_slashRc1 = RectMakeCenter(_place[0].XY.x - 100, _place[0].XY.y, 50, IMAGEMANAGER->findImage("플레이어검기")->getFrameHeight());
			_slashRc2 = RectMakeCenter(_place[1].XY.x - 100, _place[1].XY.y, 50, IMAGEMANAGER->findImage("플레이어검기")->getFrameHeight());
		}
		else
		{
			_player.gravite = 3;
			_player.center.x -= 100;
			//_player.center.y -= 100;
			_player.image = IMAGEMANAGER->findImage("플레이어공격");
			_player.now_Image = "플레이어공격";
			attack->setPlayFrame(13, 7, false, false);
			attack->start();

			slash->setPlayFrame(11, 6, false, false);
			slash->start();
			_slashRc = RectMakeCenter(_player.center.x+100, _player.center.y, 50, IMAGEMANAGER->findImage("플레이어검기")->getFrameHeight());
			_slashRc1 = RectMakeCenter(_place[0].XY.x + 100, _place[0].XY.y, 50, IMAGEMANAGER->findImage("플레이어검기")->getFrameHeight());
			_slashRc2 = RectMakeCenter(_place[1].XY.x + 100, _place[1].XY.y, 50, IMAGEMANAGER->findImage("플레이어검기")->getFrameHeight());
		}
		_shadow.state = SHASTATE::ATTACK;
		

		break;
	case STATE::DIE:
		if (_player.right)
		{

		}
		else
		{

		}

		break;
			
	default:
		break;
	}
}

void player::stateProsses()
{
	
	switch (_player.state)
	{
	case STATE::IDLE:
		
		break;

	case STATE::JUMP:
		_player.center.y -= 15;
		if (!jump->isPlay())
		{
			_player.state = STATE::FALL;
			stateACT(_player.state);
		}
		break;

	case STATE::ATTACK:
		
		if (!attack->isPlay())
		{
			_player.state = STATE::IDLE;
			stateACT(_player.state);
			_slashRc = RectMake(-500, -500, -500, -500);
			_slashRc1 = RectMake(-500, -500, -500, -500);
			_slashRc2 = RectMake(-500, -500, -500, -500);
		}
		if (attack->isPlay())
		{
			//if (_player.right)_player.right = true;
			//if (!_player.right)_player.right = false;
		}
		break;

	case STATE::DIE:
		
		break;

	case STATE::FALL:
		if (_player.gravite==0)
		{
			_player.state = STATE::IDLE;
			stateACT(_player.state);
		}
		break;

	case STATE::IDLE_TO_RUN:
		if (idleToRun->isPlay() == false)
		{
			_player.state = STATE::RUN;
			stateACT(_player.state);
		}
		
		break;

	case STATE::RUN:
		if (_player.right)
		{
			_player.center.x += _player.speed;
		}
		else _player.center.x -= _player.speed;
		break;

	case STATE::RUN_TO_IDLE:
		if (runToIdle->isPlay() == false)
		{
			_player.state = STATE::IDLE;
			stateACT(_player.state);
		}
		break;


	}

	
}
