#pragma once
#include <string>
#include <iostream>

using namespace std;


class HistoryRecord
{
public:
	HistoryRecord(void);
	~HistoryRecord(void);
	string GetEventContent() {return EventContent;};
	void PutEventContentOnScreen()
	{
		cout << "\t\t" << EventContent <<endl;
	};
	void GetRecordFromKB()
	{
		cin.ignore();
		getline(cin,EventContent);
	}
	void PutRecord(string temp)
	{
		EventContent = temp;
	}

	bool operator>(HistoryRecord &);		// > ������ ������
	bool operator==(HistoryRecord&);		// == ������ ������
	bool operator<(HistoryRecord&);		// < ������ ������

	HistoryRecord operator=(HistoryRecord &);	// = ������ ������
private :
	string EventContent;
	
	
};
