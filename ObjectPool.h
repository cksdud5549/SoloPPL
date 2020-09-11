#pragma once
#include <vector>
#include <queue>
#include <list>

using namespace std;
template <typename T>
class objectPooling
{
private:

public:
	int _maxSize;
	//int b;
	vector<T> _objects;		// �̸� maxSize��ŭ�� �޸𸮸� ����
	list<int> _usingIndex; // ������� �ε���, ���� ������ ������ �ϱ� ���� list
	queue<int> _waitingIndex; // ������� �ε���, �ϳ��� ������ �������� ���� ť

	//vector<T> _objects; -> ���͸� �� ������ �޸𸮸� ���������� ��⿡ �޸� ����ȭ�� ���� �Ű� �� �ʿ� x
	//_usingIndex -> �����(��� �ִ�, ����'��', ����'��')�� �ε����� ��� ����Ʈ
	//������� �ε����� �߰��� �����̳� ������ �Ͼ �� �ֱ� ������ ���� �����ص� �����ִ� �����͸� �������ָ� ���� ����Ʈ�� �������
	//_waitingIndex -> ������� usingIndex���͸� ������ vector<T> _objects; ��ü �����߿� ������ �ε���. 
	//���ο� źȯ�� �����ϰ� �����Ϸ��� �̰����� �ε����� �������� �ȴ�.
	//���Լ����� ���� �Ϸ��� ť�� ����->�߰����� ���� ������ �Ͼ�� �ʱ� ������ -> �����̳�? ���豸��

	//������					   : �ٷ� ���ڷ� ����. -> ������ �� �Ű������� �ٷ� �ȿ� �ִ� ���������� ���Եȴ�.
	objectPooling(int maxSize) : _maxSize(maxSize) //, b(maxSize) ->�̷� ������ �� ���� �� �ִ�.
	{
		//������Ʈ �ִ�ũ�� maxSize��ŭ ����
		_objects.resize(maxSize);

		//������ �� maxSize��ŭ _waitingIndex�� ��´�.
		for (int i = 0; i < maxSize; i++)
		{
			_waitingIndex.push(i);
		}
	}

	//������� ����Ʈ�� �ε����� �����, 
	void clear()
	{
		queue<int> empty;
		swap(_waitingIndex, empty); //����ִ� ť�� ��ü�ϰ�

		for (int i = 0; i < _maxSize; i++)
		{
			//�Լ��� ����ϸ� _maxSize��ŭ �ٽ� ����
			_waitingIndex.push(i);
		}
		//������� �ε����� ���� �����
		//clear() -> ����Ʈ �⺻�Լ�
		_usingIndex.clear();
	}
};
