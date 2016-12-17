#pragma once
#include <iostream>
#include "DoublySortedClass.h"
#include "EventString.h"
#include "EventClass.h"
#include <fstream>
#include <string>

using namespace std;

class EventRecord
{
private :
	string EventName;		// event name
	SortedListType<StringRecord> stringList;

public:
	EventRecord(void);		// ������
	~EventRecord(void);	// �Ҹ���
	void addEvent(StringRecord& inData);
	string displayEvent(StringRecord&,int count);
	bool isEmpty()
	{
		if(stringList.LengthIs() == 0)
			return true;
		return false;
	};
	string GetEventName() {return EventName;};	// get event name
	void PutEventName(string inEventName) {EventName = inEventName;};	// put event name
	void Delete(string temp);
	int GetLength(){return stringList.LengthIs();};

	/*===================================================================================
	// Function: Disply event name on screen
	// Pre : none
	// Post: event name on screen
	=====================================================================================*/
	void PutEventNameOnScreen()
	{
		cout << "\tEvent Name : "<< EventName << endl; 
	};
	/*===================================================================================
	// Function: Read event name from keyboard
	// Pre: none
	// Post: event name holds new event name form keyboard.
	//       if invalid event name, the return 0. Otherwise return 1
	=====================================================================================*/
	int GetEventNameFromKB();

	/*===================================================================================
	// Function: �ϳ��� ���ڵ带 file�κ��� �о� ���δ�.
	// Pre		: file�� open�ǰ� file pointer�� �о���� ���ڵ��� ��ġ�� 
	// Post		: photo name, event name, event time, event content�� ��� ����, file pointer�� �ǵڷ� �Ű���  
	=====================================================================================*/
	int GetRecordFromFile(ifstream& fin);

	/*===================================================================================
	// Function : �ϳ��� ���ڵ带 file�� ����
	// Pre		: file�� open�ǰ� file pointer�� ���ڵ尡 �� ��ġ��
	//			  photo name, event name, event time, event content���� ��µ� �ڷᰡ ����
	// Post		: ���Ͽ� ����ǰ� file pointer�� �� �ڷ� �Ű��� 
	=====================================================================================*/
	int PutRecordToFile(ofstream& fout);

	bool operator>(EventRecord &);		// > ������ ������
	bool operator==(EventRecord&);		// == ������ ������
	bool operator<(EventRecord&);		// < ������ ������

	void operator=(EventRecord &);	// = ������ ������

};