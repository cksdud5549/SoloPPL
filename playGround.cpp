#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init(true);
	imageSound();
	mapstate = MAP::START;
	
	_pilani = new animation;
	_pilani->init(IMAGEMANAGER->findImage("�ʻ��")->getWidth(),
		IMAGEMANAGER->findImage("�ʻ��")->getHeight(),
		IMAGEMANAGER->findImage("�ʻ��")->getFrameWidth(),
		IMAGEMANAGER->findImage("�ʻ��")->getFrameHeight());
	_pilani->setDefPlayFrame(false, false);
	_pilani->setFPS(1);

	return S_OK;
}

//�޸� ����
void playGround::release()
{
	
	
}

//����
void playGround::update()
{
	gameNode::update();
	
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_pil = true;
	
		SOUNDMANAGER->play("�ʻ��",1.0f);
		SOUNDMANAGER->stop("���κ��");
		SOUNDMANAGER->play("�ʻ������",0.3f);
		
		_pilani->start();
	}
	if (_pil && !SOUNDMANAGER->isPlaySound("�ʻ������")&&!Tlqkf)
	{
		SOUNDMANAGER->play("�ʻ������",0.3f);
		Tlqkf = true;
	}
	cout << _pil << endl;
	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		_end = true;
		SOUNDMANAGER->stop("���κ��");
		SOUNDMANAGER->play("��");
	}
		
		
	_pilani->frameUpdate(TIMEMANAGER->getElapsedTime() );
	
	
		
	
	if (!_pil&&!_end)
	{
		if (mapstate == MAP::START && KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			SOUNDMANAGER->play("���κ��", 0.5f);
			mapstate = MAP::MAIN_MAP;
			_main = new main;
			_main->init();
		}

		if (mapstate == MAP::MAIN_MAP)
		{
			_main->update();
		}
		if (mapstate == MAP::DUNGEON)
		{
			_dungeon->update();
		}
		//if (!_main->getMapOnOff())mapstate = MAP::DUNGEON;
	}
}

//�׸��� ����
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	if (!_pil&&!_end)
	{
		if (mapstate == MAP::MAIN_MAP)
		{
			_main->render();
		}

		if (mapstate == MAP::DUNGEON)
		{
			_dungeon->render();
		}
		if (mapstate == MAP::START)
		{
			IMAGEMANAGER->findImage("����")->render(getMemDC());
		}
	}
	if (_end)
	{
		IMAGEMANAGER->findImage("��")->render(getMemDC(), 0, 0);
	}
	if (_pil)
	{
		_main->render();
		IMAGEMANAGER->findImage("�ʻ��")->aniRender(getMemDC(), 0, 0, _pilani);
	}
	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}


void playGround::imageSound()
{
	IMAGEMANAGER->addFrameImage("�Ѿ�", "img/boss_dote/MMD_BULLET_6LR.bmp", 198, 60, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ѿ�1", "img/boss_dote/bullet_4.bmp", 192, 48,4,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ѿ�����Ʈ", "img/boss_dote/MMD_EFFECT_9.bmp", 729, 160, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ĵ�", "img/boss_dote/MMD_WATER_8.bmp", 1952, 100, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������̵�", "img/boss_dote/MMD_IDLE_20.bmp", 6600, 400, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����ǰ�", "img/boss_dote/MMD_HIT_3.bmp", 1116, 400, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų", "img/boss_dote/MMD_SKILL_7.bmp", 3374, 400, 7, 1, true, RGB(255, 0, 255));

	//����

	IMAGEMANAGER->addImage("�����", "img/main/morning_back.bmp", 2048, 968, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "img/main/night_back.bmp", 2048, 968, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ٴ�", "img/main/main_floor.bmp", 1500, 105, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ǯ", "img/main/main_background.bmp", 1024, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�踮��", "img/main/main_barrier.bmp", 1446, 1011, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ǹ�1", "img/main/main_obj1.bmp", 195, 147, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ǹ�2", "img/main/main_obj2.bmp", 150, 288, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����", "img/main/main_mob_death_1.bmp", 144, 34, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ǰ�", "img/main/main_mob_hit_2.bmp", 340, 240, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����̵�", "img/main/main_mob_idle_5.bmp", 860, 240, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "img/main/main_mob_run_8.bmp", 1376, 240, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "img/main/start.bmp", 1200, 900,false,RGB(0,0,0));
	IMAGEMANAGER->addFrameImage("�ʻ��", "img/main/�ʻ��.bmp", 6000, 900, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��", "img/main/��.bmp", 1200, 900, false, RGB(0, 0, 0));

	SOUNDMANAGER->addSound("��", "img/main/��.mp3", true, true);
	SOUNDMANAGER->addSound("�ʻ��", "img/main/�ʻ��.wav", false, false);
	SOUNDMANAGER->addSound("�ʻ������", "img/main/����.mp3", false, false);
	SOUNDMANAGER->addSound("�ʻ������", "img/main/��.mp3", false, false);
	SOUNDMANAGER->addSound("���Ҹ�", "img/main/mobSound.wav", false, false);
	SOUNDMANAGER->addSound("���κ��", "img/main/8��Ʈ ��Ÿ��.mp3", true, true);


	//����

	IMAGEMANAGER->addImage("�������", "img/dungeon/Rhythm_backGround.bmp", 800, 448, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("�����Ѿ�", "img/dungeon/dungeon_bullet_6.bmp", 196, 60, 6, 2, true, RGB(255, 0, 255));
	SOUNDMANAGER->addSound("��������", "img/dungeon/dungeon_BGM.mp3", true, false);

	//����

	IMAGEMANAGER->addFrameImage("�÷��̾���̵�", "img/player/player_idle_11x2.bmp", 770, 140, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾����", "img/player/player_attack_7x2.bmp", 840, 164, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾�����ܻ�", "img/player/player_attack_shadow_7x2.bmp", 840, 164, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾�����", "img/player/player_fall_4x2.bmp", 328, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾������ܻ�", "img/player/player_fall_shadow_4x2.bmp", 328, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾�����", "img/player/player_jump_4x2.bmp", 240, 168, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾����", "img/player/player_idle_to_run_4x2.bmp", 336, 128, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾", "img/player/player_run_10x2.bmp", 880, 128, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾����", "img/player/player_landdust_8x1.bmp", 660, 16, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾�ܻ�", "img/player/player_run_shadow_10x2.bmp", 880, 128, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��", "img/player/player_run_to_idle_5x2.bmp", 400, 140, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾���", "img/player/player_hurtground_6x2.bmp", 684, 92, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾���������", "img/player/player_jumpdust_5x1.bmp", 210, 80, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾�˱�", "img/player/player_slash_basic_6x2.bmp", 1260, 120, 6, 2, true, RGB(255, 0, 255));
	SOUNDMANAGER->addSound("�üҸ�", "img/player/��!.wav", false, false);
	SOUNDMANAGER->addSound("Į�Ҹ�", "img/player/Į�Ҹ�.wav", false, false);
	//�÷��̾�

}