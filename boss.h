#pragma once
#include"gameNode.h"
#include"bullet.h"
#include"player.h"


class main;
class objects;

enum class BOSSPAT
{
	ATT1,
	ATT2,
	ATT3,
	HIT,
	SUMMON
};
struct tagBoss
{
	image* img;
	animation* ani;
	MYRECT rc;
	BOSSPAT pat;
};

class boss : public gameNode

{
private:
	tagBoss _boss;
	tagBoss _water;
	main* _main;

	float _fTimer;

	int _fireCount;
	int _rndFireCount;
public:

	boss() {};
	~boss() {};

	HRESULT init();
	void release();
	void update();
	void render();
	void bossAniSetting();

	void setBossState(BOSSPAT pat) { _boss.pat = pat; }
	BOSSPAT getBossState() { _boss.pat; }
	
	MYRECT getRect() { return _boss.rc; }


	bool isBossHumming();
	//보스의 탄환 발사 유무확인
	bool bulletCountFire();
	//탄환 각
	void attBullet(player* player, bullet* bullet);
	void attBulletObj(objects* obj, bullet* bullet);
	void setMainMemoryAddressLink(main* main) { _main = main; }
};

