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

	NodeType<ItemType>* next;	// ����� ���� ������ Node's next address
	NodeType<ItemType>* prev;	// ����� ���� ������ Node's previous address
};


template <class ItemType>
class SortedListType
{

private:

	NodeType<ItemType>* header;
	NodeType<ItemType>* tailer;

	NodeType<ItemType>* currentPos;  // ���� ��ü ���

	int length;		// ��ũ�� ����

public:

	/*====================================================================================
	// Function : ������
	// Pre		: None
	// Post		: �� ���� �ʱ�ȭ
	=====================================================================================*/
	SortedListType();  

	/*====================================================================================
	// Function	: �Ҹ���
	// Pre		: None
	// Post		: None
	=====================================================================================*/
	~SortedListType();  

	/*====================================================================================
	// Function : �Լ��� ���ִ��� Ȯ���ϴ� �Լ�
	// Pre : None
	// Post : �� �������� 1 ����, ������ ������ 0 ����
	=====================================================================================*/
	bool IsFull() const;

	/*====================================================================================
	// Function : ��ũ�� ���̸� ��ȯ�ϴ� �Լ�
	// Pre : None
	// Post : ��ũ�� ���� ��ȯ
	=====================================================================================*/
	int  LengthIs() const;

	/*====================================================================================
	// Function : ����Ʈ�� empty���·� �ʱ�ȭ �Ѵ�.
	// Pre		: None
	// Post		: ��� ����Ʈ�� ��尡 �����ǰ� ����Ʈ�� �ʱ�ȭ��.
	=====================================================================================*/
	void MakeEmpty();

	/*====================================================================================
	// Function : part number�� ���� ������������ ���ο� �ڷḦ ����Ʈ�� ����
	// Pre		: item�� ����Ʈ�� ���Ե��� ���� ����
	// Post		: item�� ���������� ���� ����Ʈ�� ���Ե�.
	=====================================================================================*/
	int InsertItem(ItemType& item); 

	/*====================================================================================
	// Function : item�� �ش��ϴ� ��带 �����Ѵ�
	// Pre		: ����Ʈ�� item�� ��ġ�ϴ� �����Ͱ� �����Ѵ�.
	// Post		: item�� �ش��ϴ� ��尡 ������ �� ����Ʈ�� item�� ��ġ�ϴ� ������ �������� ����
	=====================================================================================*/
	int DeleteItem(ItemType item);

	/*====================================================================================
	// Function : ����Ʈ�� �ʱ�ȭ �Ѵ�.
	// Pre		: None
	// Post		: currentPos�� header�� ����Ű�� �Ѵ�.
	=====================================================================================*/
	void ResetList();


	/*====================================================================================
	// Fuction : ���ڵ带 �����Ѵ�.
	// Pre : ItemType�� ������
	// Post : ���ڵ带 �����Ѵ�.
	=====================================================================================*/
	int PushData(ItemType& item);

	/*====================================================================================
	// Function : element�� �Է��� ������ Update �Ѵ�.
	// Pre:  �Է��� element�� �����Ͽ��� �Ѵ�. 
	// Post: element �� �Է��� �Է��� ������ ���Ѵ�. 
	=====================================================================================*/
	void Update(ItemType& item);

	int GetNextItem(ItemType& item);

};


/*====================================================================================
// Function : ������
// Pre		: None
// Post		: �� ���� �ʱ�ȭ
=====================================================================================*/
template <class ItemType>
SortedListType<ItemType>::SortedListType()  // Class constructor
{
	length=0;   // ���̸� 0���� ����
	header=new NodeType<ItemType>;  // header�� ��� ����
	tailer=new NodeType<ItemType>;  // tailer�� ��� ����
	header->prev=NULL;
	header->next=tailer;
	tailer->prev=header;
	tailer->next=NULL;	// header�� tailer�� doubly linked�� ����
	currentPos=header;		// currentPos�� header�� ����

}

/*====================================================================================
// Function	: �Ҹ���
// Pre		: None
// Post		: None
=====================================================================================*/
template <class ItemType>
SortedListType<ItemType>::~SortedListType()
{
	MakeEmpty();  // ��� ������ ����
}


/*====================================================================================
// Function : �Լ��� ���ִ��� Ȯ���ϴ� �Լ�
// Pre : None
// Post : �� �������� 1 ����, ������ ������ 0 ����
=====================================================================================*/
template<class ItemType>
bool SortedListType<ItemType>::IsFull() const
{
	NodeType<ItemType> *location;
	try
	{
		location = new NodeType<ItemType>;  // �޸� �Ҵ� �õ�
		delete location;
		return false;   // ������ �� false ���
	}
	catch(bad_alloc exception)  // ������ �� true ���
	{
		return true;
	}
}
/*====================================================================================
// Function : ��ũ�� ���̸� ��ȯ�ϴ� �Լ�
// Pre : None
// Post : ��ũ�� ���� ��ȯ
=====================================================================================*/
template <class ItemType>
int SortedListType<ItemType>::LengthIs() const
{
	return length;  // ���� ��ȯ
}


/*====================================================================================
// Function : ����Ʈ�� empty���·� �ʱ�ȭ �Ѵ�.
// Pre		: None
// Post		: ��� ����Ʈ�� ��尡 �����ǰ� ����Ʈ�� �ʱ�ȭ��.
=====================================================================================*/
template <class ItemType>
void SortedListType<ItemType>::MakeEmpty()
{
	NodeType<ItemType>* tempPtr;
	while(header->next != tailer)	// header�� ���� ��尡 tailer�� �Ǳ� ������ �ݺ�
	{
		tempPtr = header->next;
		header->next = (header->next)->next;
		(header->next)->prev = header;
		delete tempPtr;		// ��� ��带 ����
	}

	length = 0;
}

/*====================================================================================
// Function : part number�� ���� ������������ ���ο� �ڷḦ ����Ʈ�� ����
// Pre		: item�� ����Ʈ�� ���Ե��� ���� ����
// Post		: item�� ���������� ���� ����Ʈ�� ���Ե�.
=====================================================================================*/
template <class ItemType>
int SortedListType<ItemType>::InsertItem(ItemType& item)
{
	NodeType<ItemType> *temp;
	temp = new NodeType<ItemType>;
	temp->info = item;		// ������ �ӽð�ü�� ����

	ResetList();

	while( (currentPos->info) < (temp->info) && currentPos->next != tailer
		&&  (currentPos->next->info) < (temp->info) )			    // ������������ �����ϱ� ���� tailer�� �Ǳ� ��,
	{														     	// �� ū �ڷᰡ ������ ������ ��� next��
		currentPos=currentPos->next;
	}

	if( (currentPos->next->info) == (temp->info) )		// �Է¹��� ��ü�� ������ ���� ��尡 ������ ��� -1 ����
		return -1;


	currentPos->next->prev=temp;
	temp->next=currentPos->next;
	currentPos->next=temp;
	temp->prev=currentPos;			// ��ġ�� ã�� �� ���̿� ��带 ����


	length++;

	return 1;


}

/*====================================================================================
// Function : item�� �ش��ϴ� ��带 �����Ѵ�
// Pre		: ����Ʈ�� item�� ��ġ�ϴ� �����Ͱ� �����Ѵ�.
// Post		: item�� �ش��ϴ� ��尡 ������ �� ����Ʈ�� item�� ��ġ�ϴ� ������ �������� ����
=====================================================================================*/
template <class ItemType>
int SortedListType<ItemType>::DeleteItem(ItemType item)
{
	int i;
	ResetList();

	for(i=0;i<length;i++)		// ���Ḯ��Ʈ�� ���̸�ŭ �ݺ�
	{
		currentPos=currentPos->next;		// ���� ���� ��

		if( (currentPos->info) == (item))	// ��ü�� ���� ���� ���� ��� �ݺ������� ��������
		{
			NodeType<ItemType> *temp;
			temp=currentPos;
			currentPos->prev->next=currentPos->next;
			currentPos->next->prev=currentPos->prev;		// ������ ��� �� �ڸ� ����
			delete temp;

			break;
		}
	}

	if( i == length)		// �Է��� ��ü�� �������� ���� ��� -1 ����
		return -1;

	length--;
	return 0;
}


/*====================================================================================
// Function : ����Ʈ�� �ʱ�ȭ �Ѵ�.
// Pre		: None
// Post		: currentPos�� header�� ����Ű�� �Ѵ�.
=====================================================================================*/
template <class ItemType>
void SortedListType<ItemType>::ResetList()
{
	currentPos =header; 
}

/*====================================================================================
// Fuction : ���ڵ带 �����Ѵ�.
// Pre : ItemType �� ������
// Post : ���ڵ带 �����Ѵ�.
=====================================================================================*/
template <class ItemType>
int SortedListType<ItemType>::PushData(ItemType& item)
{
	currentPos->info = item;
	return 0;
}


/*====================================================================================
// Function : element�� �Է��� ������ Update �Ѵ�.
// Pre:  �Է��� element�� �����Ͽ��� �Ѵ�. 
// Post: element �� �Է��� �Է��� ������ ���Ѵ�. 
=====================================================================================*/
template <class ItemType>
void SortedListType<ItemType>::Update(ItemType& item)
{
	ResetList();
	for(int i=0;i<length;i++)
	{
		currentPos=currentPos->next;
		if( (currentPos->info) == item )		// ���� ������ ��ü�� ������ ���� �� �ݺ������� ��������
			break;
	}
 currentPos->info=item;		// ��ü�� �Է��� ������ Update�Ѵ�.
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
	currentPos=currentPos->next;		// ���� ����

	if(currentPos==tailer)				// ���̸� 0����
		return 0;
	item = currentPos->info;			// currentPos�� ������ item�� ����

	return 1;
} 



#endif