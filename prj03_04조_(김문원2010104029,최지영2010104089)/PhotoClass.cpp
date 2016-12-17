#include "PhotoClass.h"

using namespace std;


PhotoRecord::PhotoRecord(void)
{
	PhotoName = "";	
	EventName = "";		
	EventTime = "";
	EventContent = "";
}


PhotoRecord::~PhotoRecord(void)
{
}

/*===================================================================================
// Function: Disply photo name on screen
// Pre : none
// Post: photo name on screen
=====================================================================================*/
int PhotoRecord::GetPhotoNameFromKB()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\tPhoto Name : ";
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	cin >> PhotoName;
	return 1;
}

/*===================================================================================
// Function: Disply event name on screen
// Pre : none
// Post: event name on screen
=====================================================================================*/
int PhotoRecord::GetEventNameFromKB()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\tEvent Name : ";
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	cin >> EventName;
	return 1;
}

/*===================================================================================
// Function: Disply event time on screen
// Pre : none
// Post: event time on screen
=====================================================================================*/
int PhotoRecord::GetEventTimeFromKB()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\tEvent Time(년, 월, 일, 시, 분, 초) : ";
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	cin >> EventTime;

	return 1;
}

/*===================================================================================
// Function: Disply event content on screen
// Pre : none
// Post: event content on screen
=====================================================================================*/
int PhotoRecord::GetEventContentFromKB()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\tEvent Content : ";
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	cin.ignore();
	cin.clear();
	getline(cin,EventContent);

	return 1;
}

/*===================================================================================
// Function: Read a record from keyboard
// Pre: none
// Post: this holds new record form keyboard.
//       if invalid record, then return 0. Otherwise return 1
=====================================================================================*/
int PhotoRecord::GetRecordFromKB()
{
	GetPhotoNameFromKB();
	GetEventNameFromKB();
	GetEventTimeFromKB();
	GetEventContentFromKB();

	return 1;
}

/*===================================================================================
// Function: 하나의 레코드를 file로부터 읽어 들인다.
// Pre		: file이 open되고 file pointer는 읽어들일 레코드의 위치에 
// Post		: photo name, event name, event time, event content에 결과 저장, file pointer는 맨뒤로 옮겨짐  
=====================================================================================*/
int PhotoRecord::GetRecordFromFile(ifstream& fin)
{
	fin >> PhotoName;
	fin >> EventName;
	fin >> EventTime;
	getline(fin, EventContent);
	HistoryRecord temp;
	string A;
	historyList.ResetList();
	for(int i=0; i<historyList.LengthIs();i++)
	{
		historyList.GetNextItem(temp);
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
int PhotoRecord::PutRecordToFile(ofstream& fout)
{
	fout << endl;
	fout << PhotoName << " ";
	fout << EventName << " ";
	fout << EventTime << " ";
	fout << EventContent <<endl;

	HistoryRecord temp;
	historyList.ResetList();
	for(int i=0; i<historyList.LengthIs();i++)
	{
		historyList.GetNextItem(temp);
		fout << temp.GetEventContent() <<endl;
	}
	return 1;
}


// '==' operator overloading
bool PhotoRecord::operator==(PhotoRecord &part1)
{	
	if(part1.PhotoName == this->PhotoName)	// 사진이름 비교
		return true;
	else 
		return false;
}

// '>' operator overloading
bool PhotoRecord::operator>(PhotoRecord &part1)
{
	if(this->PhotoName > part1.PhotoName)		// 사진이름 비교
		return true;
	else 
		return false;
}

// '<' operator overloading
bool PhotoRecord::operator <(PhotoRecord &part1)
{
	if(this->PhotoName < part1.PhotoName)		// 사진이름 비교
		return true;
	else 
		return false;
}

// '=' operator overloading
void PhotoRecord::operator =(PhotoRecord &part2)
{
	HistoryRecord temp;
	this->PhotoName = part2.PhotoName;			// 사진 이름확인
	this->EventName = part2.EventName;			// 행사명 확인
	this->EventTime = part2.EventTime;			// 행사시간확인
	this->EventContent = part2.EventContent;		// 행사 내용 확인
	part2.historyList.ResetList();
	this->historyList.MakeEmpty();
	this->historyList.ResetList();
	for(int i=0;i < part2.historyList.LengthIs();i++)
	{
		part2.historyList.GetNextItem(temp);
		this->historyList.InsertItem(temp);
	}
	

}

void PhotoRecord::addHistory(HistoryRecord& inData)
{
	historyList.InsertItem(inData);	// photo리스트 추가	
}

void PhotoRecord::displayHistory(HistoryRecord& inData)
{
	cout << endl << endl;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	cout << "\t\tHistory list" << endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);

	historyList.ResetList();

	for(int i=0; i<historyList.LengthIs();i++)
	{
		historyList.GetNextItem(inData);
		inData.PutEventContentOnScreen();
		cout << endl;
	}
}
