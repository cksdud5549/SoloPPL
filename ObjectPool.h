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
	vector<T> _objects;		// 미리 maxSize만큼의 메모리를 잡음
	list<int> _usingIndex; // 사용중인 인덱스, 삽입 삭제를 빠르게 하기 위해 list
	queue<int> _waitingIndex; // 대기중인 인덱스, 하나씩 빠르게 꺼내쓰기 위해 큐

	//vector<T> _objects; -> 벡터를 쓴 이유는 메모리를 연속적으로 잡기에 메모리 파편화나 낭비 신경 쓸 필요 x
	//_usingIndex -> 사용중(쏘고 있는, 삭제'할', 생성'된')인 인덱스를 잡는 리스트
	//사용중인 인덱스는 중간에 삽입이나 삭제가 일어날 수 있기 때문에 값을 삭제해도 남아있는 포인터만 변경해주면 편한 리스트로 만들어짐
	//_waitingIndex -> 사용중인 usingIndex백터를 제외한 vector<T> _objects; 전체 벡터중에 나머지 인덱스. 
	//새로운 탄환을 생성하고 삭제하려면 이곳에서 인덱스를 가져오면 된다.
	//선입선출이 쉽게 하려고 큐로 만듬->중간에서 삽입 삭제가 일어나지 않기 때문에 -> 설계이념? 설계구조

	//생성자					   : 바로 인자로 들어간다. -> 생성할 때 매개변수가 바로 안에 있는 변수값으로 대입된다.
	objectPooling(int maxSize) : _maxSize(maxSize) //, b(maxSize) ->이런 식으로 더 붙일 수 있다.
	{
		//오브젝트 최대크기 maxSize만큼 조정
		_objects.resize(maxSize);

		//생성될 때 maxSize만큼 _waitingIndex를 잡는다.
		for (int i = 0; i < maxSize; i++)
		{
			_waitingIndex.push(i);
		}
	}

	//사용중인 리스트의 인덱스를 지우고, 
	void clear()
	{
		queue<int> empty;
		swap(_waitingIndex, empty); //비어있는 큐로 교체하고

		for (int i = 0; i < _maxSize; i++)
		{
			//함수를 사용하면 _maxSize만큼 다시 삽입
			_waitingIndex.push(i);
		}
		//사용중인 인덱스를 전부 지운다
		//clear() -> 리스트 기본함수
		_usingIndex.clear();
	}
};
