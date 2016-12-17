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
// Function: �ϳ��� ���ڵ带 file�κ��� �о� ���δ�.
// Pre		: file�� open�ǰ� file pointer�� �о���� ���ڵ��� ��ġ�� 
// Post		: photo name, event name, event time, event content�� ��� ����, file pointer�� �ǵڷ� �Ű���  
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
// Function : �ϳ��� ���ڵ带 file�� ����
// Pre		: file�� open�ǰ� file pointer�� ���ڵ尡 �� ��ġ��
//			  photo name, event name, event time, event content���� ��µ� �ڷᰡ ����
// Post		: ���Ͽ� ����ǰ� file pointer�� �� �ڷ� �Ű��� 
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
	if(part1.EventName == this->EventName)	// �����̸� ��
		return true;
	else 
		return false;
}

// '>' operator overloading
bool EventRecord::operator>(EventRecord &part1)
{
	if(this->EventName > part1.EventName)		// �����̸� ��
		return true;
	else 
		return false;
}

// '<' operator overloading
bool EventRecord::operator <(EventRecord &part1)
{
		if(this->EventName < part1.EventName)		// �����̸� ��
		return true;
	else 
		return false;
}

// '=' operator overloading
void EventRecord::operator =(EventRecord &part2)
{
	StringRecord temp;
	this->EventName = part2.EventName;			// ���� �̸�Ȯ��

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
	stringList.InsertItem(inData);	// photo����Ʈ �߰�	

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
