#include "stdafx.h"
#include "bullet.h"
#include "player.h"
#include "objects.h"



bullet::bullet(int missileMax)
	:_bulletMax(missileMax)
{
	_opBullet = new objectPooling<tagBullet>(missileMax);
	_ani2 = new animation;
	_ani2->init(IMAGEMANAGER->findImage("총알이펙트")->getWidth(), IMAGEMANAGER->findImage("총알이펙트")->getHeight(),
		IMAGEMANAGER->findImage("총알이펙트")->getFrameWidth(), IMAGEMANAGER->findImage("총알이펙트")->getFrameHeight());
	_ani2->setDefPlayFrame(false, false);
	_ani2->setFPS(1);
	_ani2->setPlayFrame(9, 17, false, false);
	_ani2->start();
};

HRESULT bullet::init(string imgName, float range)
{
	_imgName = imgName;
	_range = range;
	
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{

	move();
	if(!_opBullet->_usingIndex.empty())_ani->frameUpdate(TIMEMANAGER->getElapsedTime()*50);
	
}

void bullet::render()
{
	vector<tagBullet> bullets = _opBullet->_objects;		//오브젝트 풀링 maxsize 벡터로 잡는다.
	list<int> usingIndex = _opBullet->_usingIndex;			//사용중인 리스트를 잡는다.
	set<pair<int, int>> sets;								//사각형의 Left, Top을 저장할 set컨테이너
	//균형이진트리 자료 저장 구조 = set

	//리스트의 시작값부터-> 엔드값이 같지 않으면-> It 값 증가
	for (auto it = usingIndex.begin(); it != usingIndex.end(); it++)
	{
		//변수에 대입 -> 인덱스
		int index = *it;
		//pair형 -> utillity에 정의되어 있는 구조체, 값 2개를 저장할 수 있다.
		//make_pair() -> utillity 함수 
		//페어형 currentLT에 사각형의 Left값, Top값을 저장
		pair<int, int> currentLT = make_pair(static_cast<int> (bullets[index].rc.left),
			static_cast<int>(bullets[index].rc.top));

		//set.find()함수 -> 원소를 가리키는 반복자를 반환, 없다면 set.end()와 같은 반복자를 반환한다.
		//반복문 중단용 -> set컨테이너의 저장된 사각형의 Left값, Top 값이 엔드값이랑 같지 않으면 continue
		if (sets.find(currentLT) != sets.end()) continue;

		else
		{
			// 아니면 셋컨테이너에 사각형의 left, top 값을 쌍으로 넣는다.
			sets.insert(currentLT);
		}
	}

	//셋 크기만큼 반복
	for (auto it = sets.begin(); it != sets.end(); it++)
	{
		//페어형 
		pair<int, int> LT = *it;
		//bullets[0].img->render(getMemDC(), LT.first, LT.second);
		CAMERA->aniRender(getMemDC(), LT.first, LT.second, bullets[0].img, _ani);
		//CAMERA->rectangle(getMemDC(), _opBullet->_objects[0].rc);
		//CAMERA->render(getMemDC(), bullets[0].img, LT.first, LT.second);
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{
	//벡터사이즈보다 사용중인 리스트의 사이즈가 크면 리턴
	if (_opBullet->_maxSize <= _opBullet->_usingIndex.size())return;

	//대기중인 큐의 처음원소
	int newIndex = _opBullet->_waitingIndex.front();

	//큐에있는 원소 삭제 (맨앞)
	_opBullet->_waitingIndex.pop();

	//대기중에있는큐에 삭제된 원소에 삽입할정보
	_opBullet->_objects[newIndex].img = IMAGEMANAGER->findImage(_imgName);
	_opBullet->_objects[newIndex].speed = speed;
	_opBullet->_objects[newIndex].radius = _opBullet->_objects[newIndex].img->getFrameWidth() / 2;
	_opBullet->_objects[newIndex].x = _opBullet->_objects[newIndex].fireX = x;
	_opBullet->_objects[newIndex].y = _opBullet->_objects[newIndex].fireY = y;
	_opBullet->_objects[newIndex].angle = angle;

	_ani = new animation;
	_ani->init(IMAGEMANAGER->findImage(_imgName)->getWidth(), IMAGEMANAGER->findImage(_imgName)->getHeight(),
		IMAGEMANAGER->findImage(_imgName)->getFrameWidth(), IMAGEMANAGER->findImage(_imgName)->getFrameHeight());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(1);
	_ani->setPlayFrame(0, 4, false, true);
	_ani->start();

	

	_opBullet->_objects[newIndex].rc.set(_opBullet->_objects[newIndex].x - _opBullet->_objects[newIndex].radius,
		_opBullet->_objects[newIndex].y - _opBullet->_objects[newIndex].radius,
		_opBullet->_objects[newIndex].x + _opBullet->_objects[newIndex].radius,
		_opBullet->_objects[newIndex].y + _opBullet->_objects[newIndex].radius);

	_opBullet->_usingIndex.push_back(newIndex);
	
}

void bullet::fire(POINTFLOAT pos, float angle, float speed)
{
	//벡터사이즈보다 사용중인 리스트의 사이즈가 크면 리턴
	if (_opBullet->_maxSize <= _opBullet->_usingIndex.size())return;

	//대기중인 큐의 처음원소
	int newIndex = _opBullet->_waitingIndex.front();

	//큐에있는 원소 삭제 (맨앞)
	_opBullet->_waitingIndex.pop();

	//대기중에있는큐에 삭제된 원소에 삽입할정보
	_opBullet->_objects[newIndex].img = IMAGEMANAGER->findImage(_imgName);
	_opBullet->_objects[newIndex].speed = speed;
	_opBullet->_objects[newIndex].radius = _opBullet->_objects[newIndex].img->getFrameWidth() / 2;
	_opBullet->_objects[newIndex].x = _opBullet->_objects[newIndex].fireX = pos.x;
	_opBullet->_objects[newIndex].y = _opBullet->_objects[newIndex].fireY = pos.y;
	_opBullet->_objects[newIndex].angle = angle;

	_ani = new animation;
	_ani->init(IMAGEMANAGER->findImage(_imgName)->getWidth(), IMAGEMANAGER->findImage(_imgName)->getHeight(),
		IMAGEMANAGER->findImage(_imgName)->getFrameWidth(), IMAGEMANAGER->findImage(_imgName)->getFrameHeight());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(1);
	_ani->setPlayFrame(0, 4, false, true);
	_ani->start();



	_opBullet->_objects[newIndex].rc.set(_opBullet->_objects[newIndex].x - _opBullet->_objects[newIndex].radius,
		_opBullet->_objects[newIndex].y - _opBullet->_objects[newIndex].radius,
		_opBullet->_objects[newIndex].x + _opBullet->_objects[newIndex].radius,
		_opBullet->_objects[newIndex].y + _opBullet->_objects[newIndex].radius);

	_opBullet->_usingIndex.push_back(newIndex);

}

void bullet::move()
{
	//사용중인 리스트
	list<int> usingIndex = _opBullet->_usingIndex;

	//사용중인 리스트의 길이만큼 반복해라
	for (auto it = usingIndex.begin(); it != usingIndex.end(); it++)
	{
		//리스트에있는 원소 인덱스로 할당해라
		int index = *it;

		//사용중인 인덱스로 연산해라
		_opBullet->_objects[index].x += cosf(_opBullet->_objects[index].angle)*_opBullet->_objects[index].speed;
		_opBullet->_objects[index].y += -sinf(_opBullet->_objects[index].angle) * _opBullet->_objects[index].speed;

		_opBullet->_objects[index].rc.set(_opBullet->_objects[index].x - _opBullet->_objects[index].radius,
			_opBullet->_objects[index].y - _opBullet->_objects[index].radius,
			_opBullet->_objects[index].x + _opBullet->_objects[index].radius,
			_opBullet->_objects[index].y + _opBullet->_objects[index].radius);

		if (_range < getDistance(_opBullet->_objects[index].x, _opBullet->_objects[index].y,
			_opBullet->_objects[index].fireX, _opBullet->_objects[index].fireY))
		{
			removeBullet(index);
		}
		
		if (isCollision(_opBullet->_objects[index].rc, _player->getSlaRect())|| isCollision(_opBullet->_objects[index].rc, _player->getSla1Rect()) || isCollision(_opBullet->_objects[index].rc, _player->getSla2Rect()) )
		{
			SOUNDMANAGER->play("팅소리", 0.3f);
			_money++;
			removeBullet(index);
		}
	
	}

}

void bullet::setBulletColl(MYRECT rc)
{
	//사용중인 리스트
	list<int> usingIndex = _opBullet->_usingIndex;

	//사용중인 리스트의 길이만큼 반복해라
	for (auto it = usingIndex.begin(); it != usingIndex.end(); it++)
	{
		//리스트에있는 원소 인덱스로 할당해라
		int index = *it;

		//사용중인 인덱스로 연산해라
		_opBullet->_objects[index].x += cosf(_opBullet->_objects[index].angle)*_opBullet->_objects[index].speed;
		_opBullet->_objects[index].y += -sinf(_opBullet->_objects[index].angle) * _opBullet->_objects[index].speed;

		_opBullet->_objects[index].rc.set(_opBullet->_objects[index].x - _opBullet->_objects[index].radius,
			_opBullet->_objects[index].y - _opBullet->_objects[index].radius,
			_opBullet->_objects[index].x + _opBullet->_objects[index].radius,
			_opBullet->_objects[index].y + _opBullet->_objects[index].radius);

		if (_range < getDistance(_opBullet->_objects[index].x, _opBullet->_objects[index].y,
			_opBullet->_objects[index].fireX, _opBullet->_objects[index].fireY))
		{
			removeBullet(index);
		}

		if (isCollision(rc, _opBullet->_objects[index].rc))
		{
			removeBullet(index);
		}

	}

}

void bullet::removeBullet(int arrNum)
{
	_opBullet->_usingIndex.remove(arrNum);
	_opBullet->_waitingIndex.push(arrNum);
	
}
