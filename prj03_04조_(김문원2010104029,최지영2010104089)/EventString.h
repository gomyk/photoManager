#pragma once
#include <string>
#include <iostream>

using namespace std;


class StringRecord
{
public:
	StringRecord(void);
	~StringRecord(void);
	string GetPhotoName() {return PhotoName;};

	void PutRecord(string temp)
	{
		PhotoName = temp;
	}
	void PutPhotoNameOnScreen()
	{
		cout <<"\t"<<PhotoName<<endl;
	}
	bool operator>(StringRecord &);		// > ������ ������
	bool operator==(StringRecord&);		// == ������ ������
	bool operator<(StringRecord&);		// < ������ ������

	StringRecord operator=(StringRecord &);	// = ������ ������
private :
	string PhotoName;
	
	
};
