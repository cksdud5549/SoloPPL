#include "stdafx.h"
#include "bullet.h"
#include "player.h"
#include "objects.h"



bullet::bullet(int missileMax)
	:_bulletMax(missileMax)
{
	_opBullet = new objectPooling<tagBullet>(missileMax);
	_ani2 = new animation;
	_ani2->init(IMAGEMANAGER->findImage("�Ѿ�����Ʈ")->getWidth(), IMAGEMANAGER->findImage("�Ѿ�����Ʈ")->getHeight(),
		IMAGEMANAGER->findImage("�Ѿ�����Ʈ")->getFrameWidth(), IMAGEMANAGER->findImage("�Ѿ�����Ʈ")->getFrameHeight());
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
	vector<tagBullet> bullets = _opBullet->_objects;		//������Ʈ Ǯ�� maxsize ���ͷ� ��´�.
	list<int> usingIndex = _opBullet->_usingIndex;			//������� ����Ʈ�� ��´�.
	set<pair<int, int>> sets;								//�簢���� Left, Top�� ������ set�����̳�
	//��������Ʈ�� �ڷ� ���� ���� = set

	//����Ʈ�� ���۰�����-> ���尪�� ���� ������-> It �� ����
	for (auto it = usingIndex.begin(); it != usingIndex.end(); it++)
	{
		//������ ���� -> �ε���
		int index = *it;
		//pair�� -> utillity�� ���ǵǾ� �ִ� ����ü, �� 2���� ������ �� �ִ�.
		//make_pair() -> utillity �Լ� 
		//����� currentLT�� �簢���� Left��, Top���� ����
		pair<int, int> currentLT = make_pair(static_cast<int> (bullets[index].rc.left),
			static_cast<int>(bullets[index].rc.top));

		//set.find()�Լ� -> ���Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ, ���ٸ� set.end()�� ���� �ݺ��ڸ� ��ȯ�Ѵ�.
		//�ݺ��� �ߴܿ� -> set�����̳��� ����� �簢���� Left��, Top ���� ���尪�̶� ���� ������ continue
		if (sets.find(currentLT) != sets.end()) continue;

		else
		{
			// �ƴϸ� �������̳ʿ� �簢���� left, top ���� ������ �ִ´�.
			sets.insert(currentLT);
		}
	}

	//�� ũ�⸸ŭ �ݺ�
	for (auto it = sets.begin(); it != sets.end(); it++)
	{
		//����� 
		pair<int, int> LT = *it;
		//bullets[0].img->render(getMemDC(), LT.first, LT.second);
		CAMERA->aniRender(getMemDC(), LT.first, LT.second, bullets[0].img, _ani);
		//CAMERA->rectangle(getMemDC(), _opBullet->_objects[0].rc);
		//CAMERA->render(getMemDC(), bullets[0].img, LT.first, LT.second);
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{
	//���ͻ������ ������� ����Ʈ�� ����� ũ�� ����
	if (_opBullet->_maxSize <= _opBullet->_usingIndex.size())return;

	//������� ť�� ó������
	int newIndex = _opBullet->_waitingIndex.front();

	//ť���ִ� ���� ���� (�Ǿ�)
	_opBullet->_waitingIndex.pop();

	//����߿��ִ�ť�� ������ ���ҿ� ����������
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
	//���ͻ������ ������� ����Ʈ�� ����� ũ�� ����
	if (_opBullet->_maxSize <= _opBullet->_usingIndex.size())return;

	//������� ť�� ó������
	int newIndex = _opBullet->_waitingIndex.front();

	//ť���ִ� ���� ���� (�Ǿ�)
	_opBullet->_waitingIndex.pop();

	//����߿��ִ�ť�� ������ ���ҿ� ����������
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
	//������� ����Ʈ
	list<int> usingIndex = _opBullet->_usingIndex;

	//������� ����Ʈ�� ���̸�ŭ �ݺ��ض�
	for (auto it = usingIndex.begin(); it != usingIndex.end(); it++)
	{
		//����Ʈ���ִ� ���� �ε����� �Ҵ��ض�
		int index = *it;

		//������� �ε����� �����ض�
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
			SOUNDMANAGER->play("�üҸ�", 0.3f);
			_money++;
			removeBullet(index);
		}
	
	}

}

void bullet::setBulletColl(MYRECT rc)
{
	//������� ����Ʈ
	list<int> usingIndex = _opBullet->_usingIndex;

	//������� ����Ʈ�� ���̸�ŭ �ݺ��ض�
	for (auto it = usingIndex.begin(); it != usingIndex.end(); it++)
	{
		//����Ʈ���ִ� ���� �ε����� �Ҵ��ض�
		int index = *it;

		//������� �ε����� �����ض�
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
