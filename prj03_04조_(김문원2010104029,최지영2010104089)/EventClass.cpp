#include "EventClass.h"

using namespace std;


EventRecord::EventRecord(void)
{
	EventName = "";		
}


EventRecord::~EventRecord(void)
{
}


/*===================================================================================
// Function: Disply event name on screen
// Pre : none
// Post: event name on screen
=====================================================================================*/
int EventRecord::GetEventNameFromKB()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\tEvent Name : ";
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	cin >> EventName;
	return 1;
}

/*===================================================================================
// Function: 하나의 레코드를 file로부터 읽어 들인다.
// Pre		: file이 open되고 file pointer는 읽어들일 레코드의 위치에 
// Post		: photo name, event name, event time, event content에 결과 저장, file pointer는 맨뒤로 옮겨짐  
=====================================================================================*/
int EventRecord::GetRecordFromFile(ifstream& fin)
{
	
	fin >> EventName;
	
	StringRecord temp;
	string A;
	stringList.ResetList();
	for(int i=0; i<stringList.LengthIs();i++)
	{
		stringList.GetNextItem(temp);
		getline(fin,A);
		temp.PutRecord(A);
	}

	return 1;
}

/*===================================================================================
// Function : 하나의 레코드를 file에 저장
// Pre		: file이 open되고 file pointer는 레코드가 들어갈 위치에
//			  photo name, event name, event time, event content에는 출력될 자료가 저장
// Post		: 파일에 저장되고 file pointer는 맨 뒤로 옮겨짐 
=====================================================================================*/
int EventRecord::PutRecordToFile(ofstream& fout)
{
	fout << endl;
	fout << EventName << " ";

	StringRecord temp;
	stringList.ResetList();
	for(int i=0; i<stringList.LengthIs();i++)
	{
		stringList.GetNextItem(temp);
		fout << temp.GetPhotoName() <<endl;
	}
	return 1;
}


// '==' operator overloading
bool EventRecord::operator==(EventRecord &part1)
{	
	if(part1.EventName == this->EventName)	// 사진이름 비교
		return true;
	else 
		return false;
}

// '>' operator overloading
bool EventRecord::operator>(EventRecord &part1)
{
	if(this->EventName > part1.EventName)		// 사진이름 비교
		return true;
	else 
		return false;
}

// '<' operator overloading
bool EventRecord::operator <(EventRecord &part1)
{
		if(this->EventName < part1.EventName)		// 사진이름 비교
		return true;
	else 
		return false;
}

// '=' operator overloading
void EventRecord::operator =(EventRecord &part2)
{
	StringRecord temp;
	this->EventName = part2.EventName;			// 사진 이름확인

	part2.stringList.ResetList();
	this->stringList.MakeEmpty();
	this->stringList.ResetList();

	for(int i=0;i < part2.stringList.LengthIs();i++)
	{
		part2.stringList.GetNextItem(temp);
		this->stringList.InsertItem(temp);
	}
	//return *this;
}

void EventRecord::addEvent(StringRecord& inData)
{
	stringList.InsertItem(inData);	// photo리스트 추가	

}
void EventRecord::Delete(string temp)
{
	StringRecord tem;
	stringList.ResetList();
	for(int i=0;i<stringList.LengthIs();i++)
	{
		stringList.GetNextItem(tem);
		if(tem.GetPhotoName() == temp)
		{
			stringList.DeleteItem(tem);
		}
	}
}

string EventRecord::displayEvent(StringRecord& inData,int count)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	
	if(count == this->GetLength())
	{
		stringList.ResetList();
		stringList.GetNextItem(inData);
		return inData.GetPhotoName();
	}
	else
	{
		stringList.GetNextItem(inData);
		return inData.GetPhotoName();
	}

	cout << endl;
	return "fail";
}
