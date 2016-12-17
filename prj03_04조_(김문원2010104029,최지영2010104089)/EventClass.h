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
	EventRecord(void);		// 생성자
	~EventRecord(void);	// 소멸자
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
	// Function: 하나의 레코드를 file로부터 읽어 들인다.
	// Pre		: file이 open되고 file pointer는 읽어들일 레코드의 위치에 
	// Post		: photo name, event name, event time, event content에 결과 저장, file pointer는 맨뒤로 옮겨짐  
	=====================================================================================*/
	int GetRecordFromFile(ifstream& fin);

	/*===================================================================================
	// Function : 하나의 레코드를 file에 저장
	// Pre		: file이 open되고 file pointer는 레코드가 들어갈 위치에
	//			  photo name, event name, event time, event content에는 출력될 자료가 저장
	// Post		: 파일에 저장되고 file pointer는 맨 뒤로 옮겨짐 
	=====================================================================================*/
	int PutRecordToFile(ofstream& fout);

	bool operator>(EventRecord &);		// > 연산자 재정의
	bool operator==(EventRecord&);		// == 연산자 재정의
	bool operator<(EventRecord&);		// < 연산자 재정의

	void operator=(EventRecord &);	// = 연산자 재정의

};