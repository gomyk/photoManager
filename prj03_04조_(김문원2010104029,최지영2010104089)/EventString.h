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
	bool operator>(StringRecord &);		// > 연산자 재정의
	bool operator==(StringRecord&);		// == 연산자 재정의
	bool operator<(StringRecord&);		// < 연산자 재정의

	StringRecord operator=(StringRecord &);	// = 연산자 재정의
private :
	string PhotoName;
	
	
};
