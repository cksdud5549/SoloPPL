#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);
	imageSound();
	mapstate = MAP::START;
	
	_pilani = new animation;
	_pilani->init(IMAGEMANAGER->findImage("필살기")->getWidth(),
		IMAGEMANAGER->findImage("필살기")->getHeight(),
		IMAGEMANAGER->findImage("필살기")->getFrameWidth(),
		IMAGEMANAGER->findImage("필살기")->getFrameHeight());
	_pilani->setDefPlayFrame(false, false);
	_pilani->setFPS(1);

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	
	
}

//연산
void playGround::update()
{
	gameNode::update();
	
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_pil = true;
	
		SOUNDMANAGER->play("필살기",1.0f);
		SOUNDMANAGER->stop("메인브금");
		SOUNDMANAGER->play("필살기전조",0.3f);
		
		_pilani->start();
	}
	if (_pil && !SOUNDMANAGER->isPlaySound("필살기전조")&&!Tlqkf)
	{
		SOUNDMANAGER->play("필살기종말",0.3f);
		Tlqkf = true;
	}
	cout << _pil << endl;
	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		_end = true;
		SOUNDMANAGER->stop("메인브금");
		SOUNDMANAGER->play("끝");
	}
		
		
	_pilani->frameUpdate(TIMEMANAGER->getElapsedTime() );
	
	
		
	
	if (!_pil&&!_end)
	{
		if (mapstate == MAP::START && KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			SOUNDMANAGER->play("메인브금", 0.5f);
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

//그리기 전용
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
			IMAGEMANAGER->findImage("시작")->render(getMemDC());
		}
	}
	if (_end)
	{
		IMAGEMANAGER->findImage("끝")->render(getMemDC(), 0, 0);
	}
	if (_pil)
	{
		_main->render();
		IMAGEMANAGER->findImage("필살기")->aniRender(getMemDC(), 0, 0, _pilani);
	}
	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}


void playGround::imageSound()
{
	IMAGEMANAGER->addFrameImage("총알", "img/boss_dote/MMD_BULLET_6LR.bmp", 198, 60, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("총알1", "img/boss_dote/bullet_4.bmp", 192, 48,4,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("총알이펙트", "img/boss_dote/MMD_EFFECT_9.bmp", 729, 160, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파도", "img/boss_dote/MMD_WATER_8.bmp", 1952, 100, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스아이들", "img/boss_dote/MMD_IDLE_20.bmp", 6600, 400, 20, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스피격", "img/boss_dote/MMD_HIT_3.bmp", 1116, 400, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스스킬", "img/boss_dote/MMD_SKILL_7.bmp", 3374, 400, 7, 1, true, RGB(255, 0, 255));

	//보스

	IMAGEMANAGER->addImage("낮배경", "img/main/morning_back.bmp", 2048, 968, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("밤배경", "img/main/night_back.bmp", 2048, 968, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("바닥", "img/main/main_floor.bmp", 1500, 105, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("수풀", "img/main/main_background.bmp", 1024, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배리어", "img/main/main_barrier.bmp", 1446, 1011, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("건물1", "img/main/main_obj1.bmp", 195, 147, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("건물2", "img/main/main_obj2.bmp", 150, 288, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("몹사망", "img/main/main_mob_death_1.bmp", 144, 34, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("몹피격", "img/main/main_mob_hit_2.bmp", 340, 240, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("몹아이들", "img/main/main_mob_idle_5.bmp", 860, 240, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("몹런", "img/main/main_mob_run_8.bmp", 1376, 240, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("시작", "img/main/start.bmp", 1200, 900,false,RGB(0,0,0));
	IMAGEMANAGER->addFrameImage("필살기", "img/main/필살기.bmp", 6000, 900, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("끝", "img/main/끝.bmp", 1200, 900, false, RGB(0, 0, 0));

	SOUNDMANAGER->addSound("끝", "img/main/끝.mp3", true, true);
	SOUNDMANAGER->addSound("필살기", "img/main/필살기.wav", false, false);
	SOUNDMANAGER->addSound("필살기전조", "img/main/전조.mp3", false, false);
	SOUNDMANAGER->addSound("필살기종말", "img/main/종.mp3", false, false);
	SOUNDMANAGER->addSound("몹소리", "img/main/mobSound.wav", false, false);
	SOUNDMANAGER->addSound("메인브금", "img/main/8비트 얏타맨.mp3", true, true);


	//메인

	IMAGEMANAGER->addImage("던전배경", "img/dungeon/Rhythm_backGround.bmp", 800, 448, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("던전총알", "img/dungeon/dungeon_bullet_6.bmp", 196, 60, 6, 2, true, RGB(255, 0, 255));
	SOUNDMANAGER->addSound("던전음악", "img/dungeon/dungeon_BGM.mp3", true, false);

	//던전

	IMAGEMANAGER->addFrameImage("플레이어아이들", "img/player/player_idle_11x2.bmp", 770, 140, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어공격", "img/player/player_attack_7x2.bmp", 840, 164, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어공격잔상", "img/player/player_attack_shadow_7x2.bmp", 840, 164, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어착지", "img/player/player_fall_4x2.bmp", 328, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어착지잔상", "img/player/player_fall_shadow_4x2.bmp", 328, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어점프", "img/player/player_jump_4x2.bmp", 240, 168, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어런시작", "img/player/player_idle_to_run_4x2.bmp", 336, 128, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어런", "img/player/player_run_10x2.bmp", 880, 128, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어런먼지", "img/player/player_landdust_8x1.bmp", 660, 16, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어런잔상", "img/player/player_run_shadow_10x2.bmp", 880, 128, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어런끝", "img/player/player_run_to_idle_5x2.bmp", 400, 140, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어사망", "img/player/player_hurtground_6x2.bmp", 684, 92, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어점프먼지", "img/player/player_jumpdust_5x1.bmp", 210, 80, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어검기", "img/player/player_slash_basic_6x2.bmp", 1260, 120, 6, 2, true, RGB(255, 0, 255));
	SOUNDMANAGER->addSound("팅소리", "img/player/팅!.wav", false, false);
	SOUNDMANAGER->addSound("칼소리", "img/player/칼소리.wav", false, false);
	//플레이어

}