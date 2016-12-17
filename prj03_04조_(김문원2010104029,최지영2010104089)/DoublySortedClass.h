#ifndef DOUBLYLINKED_H
#define DOUBLYLINKED_H
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


template <class ItemType>
struct NodeType
{
	ItemType info;				// Node's real data

	NodeType<ItemType>* next;	// 노드의 다음 포인터 Node's next address
	NodeType<ItemType>* prev;	// 노드의 이전 포인터 Node's previous address
};


template <class ItemType>
class SortedListType
{

private:

	NodeType<ItemType>* header;
	NodeType<ItemType>* tailer;

	NodeType<ItemType>* currentPos;  // 현재 객체 노드

	int length;		// 링크의 길이

public:

	/*====================================================================================
	// Function : 생성자
	// Pre		: None
	// Post		: 각 노드들 초기화
	=====================================================================================*/
	SortedListType();  

	/*====================================================================================
	// Function	: 소멸자
	// Pre		: None
	// Post		: None
	=====================================================================================*/
	~SortedListType();  

	/*====================================================================================
	// Function : 함수가 차있는지 확인하는 함수
	// Pre : None
	// Post : 다 차있으면 1 리턴, 차있지 않으면 0 리턴
	=====================================================================================*/
	bool IsFull() const;

	/*====================================================================================
	// Function : 링크의 길이를 반환하는 함수
	// Pre : None
	// Post : 링크의 길이 반환
	=====================================================================================*/
	int  LengthIs() const;

	/*====================================================================================
	// Function : 리스트를 empty상태로 초기화 한다.
	// Pre		: None
	// Post		: 모든 리스트의 노드가 삭제되고 리스트는 초기화됨.
	=====================================================================================*/
	void MakeEmpty();

	/*====================================================================================
	// Function : part number에 따라 오름차순으로 새로운 자료를 리스트에 삽입
	// Pre		: item이 리스트에 삽입되지 않은 상태
	// Post		: item이 오름차순에 맞춰 리스트에 삽입됨.
	=====================================================================================*/
	int InsertItem(ItemType& item); 

	/*====================================================================================
	// Function : item에 해당하는 노드를 삭제한다
	// Pre		: 리스트에 item과 일치하는 데이터가 존재한다.
	// Post		: item에 해당하는 노드가 삭제된 후 리스트에 item과 일치하는 데이터 존재하지 않음
	=====================================================================================*/
	int DeleteItem(ItemType item);

	/*====================================================================================
	// Function : 리스트를 초기화 한다.
	// Pre		: None
	// Post		: currentPos가 header를 가리키게 한다.
	=====================================================================================*/
	void ResetList();


	/*====================================================================================
	// Fuction : 레코드를 복사한다.
	// Pre : ItemType의 데이터
	// Post : 레코드를 복사한다.
	=====================================================================================*/
	int PushData(ItemType& item);

	/*====================================================================================
	// Function : element를 입력한 것으로 Update 한다.
	// Pre:  입력할 element가 존재하여야 한다. 
	// Post: element 가 입력한 입력한 것으로 변한다. 
	=====================================================================================*/
	void Update(ItemType& item);

	int GetNextItem(ItemType& item);

};


/*====================================================================================
// Function : 생성자
// Pre		: None
// Post		: 각 노드들 초기화
=====================================================================================*/
template <class ItemType>
SortedListType<ItemType>::SortedListType()  // Class constructor
{
	length=0;   // 길이를 0으로 설정
	header=new NodeType<ItemType>;  // header의 노드 설정
	tailer=new NodeType<ItemType>;  // tailer의 노드 설정
	header->prev=NULL;
	header->next=tailer;
	tailer->prev=header;
	tailer->next=NULL;	// header와 tailer를 doubly linked로 연결
	currentPos=header;		// currentPos를 header로 지정

}

/*====================================================================================
// Function	: 소멸자
// Pre		: None
// Post		: None
=====================================================================================*/
template <class ItemType>
SortedListType<ItemType>::~SortedListType()
{
	MakeEmpty();  // 모든 정보를 삭제
}


/*====================================================================================
// Function : 함수가 차있는지 확인하는 함수
// Pre : None
// Post : 다 차있으면 1 리턴, 차있지 않으면 0 리턴
=====================================================================================*/
template<class ItemType>
bool SortedListType<ItemType>::IsFull() const
{
	NodeType<ItemType> *location;
	try
	{
		location = new NodeType<ItemType>;  // 메모리 할당 시도
		delete location;
		return false;   // 성공할 시 false 출력
	}
	catch(bad_alloc exception)  // 실패할 시 true 출력
	{
		return true;
	}
}
/*====================================================================================
// Function : 링크의 길이를 반환하는 함수
// Pre : None
// Post : 링크의 길이 반환
=====================================================================================*/
template <class ItemType>
int SortedListType<ItemType>::LengthIs() const
{
	return length;  // 길이 반환
}


/*====================================================================================
// Function : 리스트를 empty상태로 초기화 한다.
// Pre		: None
// Post		: 모든 리스트의 노드가 삭제되고 리스트는 초기화됨.
=====================================================================================*/
template <class ItemType>
void SortedListType<ItemType>::MakeEmpty()
{
	NodeType<ItemType>* tempPtr;
	while(header->next != tailer)	// header의 다음 노드가 tailer가 되기 전까지 반복
	{
		tempPtr = header->next;
		header->next = (header->next)->next;
		(header->next)->prev = header;
		delete tempPtr;		// 모든 노드를 삭제
	}

	length = 0;
}

/*====================================================================================
// Function : part number에 따라 오름차순으로 새로운 자료를 리스트에 삽입
// Pre		: item이 리스트에 삽입되지 않은 상태
// Post		: item이 오름차순에 맞춰 리스트에 삽입됨.
=====================================================================================*/
template <class ItemType>
int SortedListType<ItemType>::InsertItem(ItemType& item)
{
	NodeType<ItemType> *temp;
	temp = new NodeType<ItemType>;
	temp->info = item;		// 정보를 임시객체에 저장

	ResetList();

	while( (currentPos->info) < (temp->info) && currentPos->next != tailer
		&&  (currentPos->next->info) < (temp->info) )			    // 오름차순으로 저장하기 위해 tailer가 되기 전,
	{														     	// 더 큰 자료가 나오기 전까지 계속 next함
		currentPos=currentPos->next;
	}

	if( (currentPos->next->info) == (temp->info) )		// 입력받은 객체의 정보와 같은 노드가 존재할 경우 -1 리턴
		return -1;


	currentPos->next->prev=temp;
	temp->next=currentPos->next;
	currentPos->next=temp;
	temp->prev=currentPos;			// 위치를 찾고 그 사이에 노드를 연결


	length++;

	return 1;


}

/*====================================================================================
// Function : item에 해당하는 노드를 삭제한다
// Pre		: 리스트에 item과 일치하는 데이터가 존재한다.
// Post		: item에 해당하는 노드가 삭제된 후 리스트에 item과 일치하는 데이터 존재하지 않음
=====================================================================================*/
template <class ItemType>
int SortedListType<ItemType>::DeleteItem(ItemType item)
{
	int i;
	ResetList();

	for(i=0;i<length;i++)		// 연결리스트의 길이만큼 반복
	{
		currentPos=currentPos->next;		// 다음 노드로 감

		if( (currentPos->info) == (item))	// 객체와 같은 것이 나올 경우 반복문에서 빠져나감
		{
			NodeType<ItemType> *temp;
			temp=currentPos;
			currentPos->prev->next=currentPos->next;
			currentPos->next->prev=currentPos->prev;		// 제거할 노드 앞 뒤를 연결
			delete temp;

			break;
		}
	}

	if( i == length)		// 입력한 객체가 존재하지 않을 경우 -1 리턴
		return -1;

	length--;
	return 0;
}


/*====================================================================================
// Function : 리스트를 초기화 한다.
// Pre		: None
// Post		: currentPos가 header를 가리키게 한다.
=====================================================================================*/
template <class ItemType>
void SortedListType<ItemType>::ResetList()
{
	currentPos =header; 
}

/*====================================================================================
// Fuction : 레코드를 복사한다.
// Pre : ItemType 의 데이터
// Post : 레코드를 복사한다.
=====================================================================================*/
template <class ItemType>
int SortedListType<ItemType>::PushData(ItemType& item)
{
	currentPos->info = item;
	return 0;
}


/*====================================================================================
// Function : element를 입력한 것으로 Update 한다.
// Pre:  입력할 element가 존재하여야 한다. 
// Post: element 가 입력한 입력한 것으로 변한다. 
=====================================================================================*/
template <class ItemType>
void SortedListType<ItemType>::Update(ItemType& item)
{
	ResetList();
	for(int i=0;i<length;i++)
	{
		currentPos=currentPos->next;
		if( (currentPos->info) == item )		// 현재 정보와 객체의 정보가 같을 시 반복문에서 빠져나감
			break;
	}
 currentPos->info=item;		// 객체에 입력한 정보를 Update한다.
}

/*============================================================================
// Gets the next element in list.
// Pre:  Current position is defined.
//       Element at current position is not last in list.
// Post: Current position is updated to next position.
//       item is a copy of element at current position.
=============================================================================*/
template <class ItemType>
int SortedListType<ItemType>::GetNextItem(ItemType& item)
{
	currentPos=currentPos->next;		// 다음 노드로

	if(currentPos==tailer)				// 끝이면 0리턴
		return 0;
	item = currentPos->info;			// currentPos의 정보를 item에 저장

	return 1;
} 



#endif