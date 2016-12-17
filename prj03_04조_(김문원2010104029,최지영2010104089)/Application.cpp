#include "Application.h"

Application::Application(void)
{
	curCommand = 0;	// curCommand를 0으로 초기화
}


Application::~Application(void)
{
}

/*====================================================================================
// Function: Programv driver
// Pre: none
// Post : none
// =====================================================================================*/
void Application::Run01()
{
	//PhotoRecord item;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	while(1)
	{
		curCommand=GetCommand();
		system("cls");
		cout <<endl;
		switch(curCommand)
		{
		case 2:		// read a record and add to list
			{
				PhotoRecord newData;	// PhotoRecord클래스 객체 생성
				newData.GetRecordFromKB();	// 사진 정보들을 입력받음.
				AddPhoto(newData);	// 입력받은 정보로 사진 추가
				DisplayAllPhotos();	// 사진추가가 완료된 후 모든 사진 출력
				break;
			}
		case 3:		// load the list from file
			{
				ReadPhotoListFromFile();
				break;
			}
		case 4:		// save the list on the disk
			{
				WriteToPhotoListToFile();

				break;
			}
		case 5 :	// retrieves list element its photo name matches item's photo name(if present)
			{
				RetreiveRecordByPhotoName();
				break;
			}
		case 6:		// 사진보기 메뉴 출력
			{
				Run03();
				break;
			}
		case 7:
			{
				return;
			}
		}
	}

}

/*====================================================================================
// Function: Program driver
// Pre: none
// Post : none
// =====================================================================================*/
void Application::Run03()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int loop = 1;	// while문 제어 변수 선언
	while(loop)
	{
		switch(GetCommand3())
		{
		case 2 :		// 기간별로 보기
			RetreiveRecordByEventTime();
			break;
		case 3 :		// event name으로 보기
			RetreiveRecordByEventName();
			break;
		case 4 :		// 사진내용으로 보기
			RetreiveRecordByEventContent();
			break;
		case 5 :		// 촬영된 순서대로 보기
			DisplyByShootingOrder();
			break;
		case 6 :		// 모든 사진 출력
			DisplayAllPhotos();
			break;
		case 7 :
			loop = 0;	// while문 종료
			break;
		default:
			SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_INTENSITY);
			cout << "\tIllegal sellection...\n";
			SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
			break;
		}
	}
}
int Application::GetCursor(int max)
{
	int x = 11;
	int y = 2;
	int command;

	while(1)
	{
		gotoxy(x,y);
		cout<<"▶";

		command =_getch();
		switch(command)
		{
			//위쪽
		case 72:
			{
				if(y>1 && y<max+1)
				{
					gotoxy(x,y);
					cout<<"  ";	// 공간 지우기
				}
				y--;// 커서 위로
				if(y<2)
				{y=max;}
				break;
			}
			//아래쪽
		case 80:
			{
				if(y>1 && y<max+1)
				{
					gotoxy(x,y);
					cout<<"  ";	// 공간 지우기
				}
				y++;	// 커서 아래로
				if(y>max)	// 로테이션 효과
				{y=2;}
				break;
			}
		case 13:
			{
				return y;
			}
		case 8:
			{
				return max+1;
			}
		}
	}
}
/*====================================================================================
// Function: Display command on screen and get a input from keyboard
// Pre: 
// Post : get command number.
// =====================================================================================*/
int Application::GetCommand()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	system("cls");
	cout <<endl;
	cout << "\t       ====== Main ======"<<endl;
	cout << "\t       Add Photo "<<endl;
	cout << "\t       GetFromFile "<<endl; 
	cout << "\t       PutToFile "<<endl; 
	cout << "\t       Serch Photo "<<endl; 
	cout << "\t       Display Photo "<<endl; 
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_INTENSITY);
	cout << "\t     ♬Quit the Program(BackSpace)♬ "<<endl;  
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	return GetCursor(6);//커서이동을 위한 함수 
}

/*====================================================================================
// Function: Display command on screen and get a input from keyboard
// Pre: 
// Post : get command number.
// =====================================================================================*/
int Application::GetCommand2()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");

	cout << endl ;
	cout << "\t       ====== File ======"<<endl;
	cout << "\t       Modify Photo "<<endl;
	cout << "\t       History of Modifying "<<endl;
	cout << "\t       Delete Photo "<<endl;
	cout << "\t       View Photo "<<endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_INTENSITY);
	cout << "\t     ♬Go to Menu(BackSpace)♬ "<<endl; 
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	return GetCursor(5);//커서이동을 위한 함수
}

/*====================================================================================
// Function: Display command on screen and get a input from keyboard
// Pre: 
// Post : get command number.
// =====================================================================================*/
int Application::GetCommand3()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	cout << endl ;
	cout << "\t       ====== View ======"<<endl;
	cout << "\t       View by Period "<<endl;
	cout << "\t       View by Event "<<endl;
	cout << "\t       View by Photo Content "<<endl; 
	cout << "\t       View by Shooting Order "<<endl;
	cout << "\t       Display All " << endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_INTENSITY);
	cout << "\t     ♬Go to Menu(BackSpace)♬ "<<endl; 
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	return GetCursor(6);//커서이동을 위한 함수
}
/*====================================================================================
// Function: Add new photo record to list
// Pre: 
// Post : list is added new photo record.
// =====================================================================================*/
int Application::AddPhoto(PhotoRecord& newData) 
{
	bool check = false;	// bool형 변수 선언하고 false로 초기화
	EventRecord newData_E;	// EventRecord클래스 객체 선언
	EventRecord temp;	// EventRecord클래스 객체 선언
	newData_E.PutEventName(newData.GetEventName());	// 이벤트 이름을 대입

	EventList.ResetList();	// 이벤트 리스트를 초기화하고

	if(!photoList.IsFull())	// 입력받은 레코드를 리스트에 add, 리스트가 full일 경우는 add하지 않고 0을 리턴
	{
		photoList.InsertItem(newData);	// photo리스트 추가
		for(int i=0;i<EventList.LengthIs();i++)	// 새로운 데이타의 이벤트명이 이벤트 리스트에 존재하는지 찾아주는 반복문
		{
			EventList.GetNextItem(temp);
			if(temp.GetEventName() == newData_E.GetEventName())	// 같은 이름이 존재할 경우
			{
				newData_E = temp;
				StringRecord inData;
				inData.PutRecord(newData.GetPhotoName());	// 사진이름을 대입
				newData_E.addEvent(inData);	// 해당 이벤트 리스트의 노드에 사진 이름 추가
				EventList.Update(newData_E);	// 이벤트 리스트 업데이트
				check = true;
			}
		}

		if(!check)
		{
			EventList.InsertItem(newData_E);// Event리스트 추가
			StringRecord inData;
			inData.PutRecord(newData.GetPhotoName());	// 사진이름을 대입
			newData_E.addEvent(inData);	// 해당 이벤트 리스트의 노드에 사진 이름 추가
			EventList.Update(newData_E);	// 이벤트 리스트 업데이트
		}

	}
	else	return 0;
	// 현재 list 출력
	return 1;
}

/*====================================================================================
// Function: Delete a photo record in list
// Pre: 
// Post : list is deleted a photo record.
// =====================================================================================*/
int Application::DeletePhoto(PhotoRecord& target)
{

	EventRecord target_E;	// EventRecord클래스 객체 생성
	EventRecord temp;	// EventRecord클래스 객체 생성
	target_E.PutEventName(target.GetEventName());	// 이벤트 이름을 대입
	EventList.ResetList();
	for(int i=0;i<EventList.LengthIs();i++)	// 해당 이벤트 노드를 찾는 반복문
	{
		EventList.GetNextItem(temp);
		if(temp.GetEventName() == target_E.GetEventName())
		{
			target_E = temp;
			break;
		}
	}

	target_E.Delete(target.GetPhotoName());
	if(target_E.isEmpty())
		EventList.DeleteItem(target_E);


	photoList.DeleteItem(target);	// photo 레코드 삭제

	// 현재 list 출력
	DisplayAllPhotos();
	return 1;
}


/*====================================================================================
// Function: Search a photo by photoname
// Pre: inData contains the name to be searched
// Post : inData holds the record matched with input photoname. If found, return 1. Otherwise 0
// =====================================================================================*/
int Application::SearchListByPhotoName(PhotoRecord& inData)
{
	PhotoRecord data2;	// 비교를 위해 list pointer의 값을 저장하는 변수

	photoList.ResetList();	// list 포인터를 초기화

	while(photoList.GetNextItem(data2))	// 이름이 같은 레코드가 존재하면 그 레코드를 복사하고 1을 리턴
	{
		if(data2.GetPhotoName() == inData.GetPhotoName())
		{
			inData = data2;
			return 1;
		}
	}
	return 0;
}


/*====================================================================================
// Function: 해당 이벤트의 내용을 찾아 출력
// Pre: photolist가 존재함.
// Post : 이벤트 내용이 출력됨.
// =====================================================================================*/
int Application::SearchByName(string inData)
{
	PhotoRecord data;
	photoList.ResetList();
	while(photoList.GetNextItem(data))	// 이름이 같은 레코드가 존재하면 그 레코드를 복사하고 1을 리턴
	{
		if(data.GetPhotoName() == inData)
		{
			data.PutRecordOnScreen();
			return 1;
		}
	}
	return 0;
}


/*====================================================================================
// Function: Read in a photo name from keyboard, search the record by photo name, and display on the screen
// Pre: none
// Post : record on screen. 
// =====================================================================================*/
int Application::RetreiveRecordByEventName()
{
	system("cls"); cout <<endl;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	EventRecord target;
	string temp;
	EventRecord data;
	int in;
	char tem;
	bool check = true;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	cout <<"\tinput_EventName : ";
	while(check)
	{
		in = _getch();
		if(in == 13)
		{
			break;
		}
		else if(in == 8)
		{
			if(temp.length() !=0)
			{
				string reg = temp;
				temp = "";
				for(int l=0;l < reg.length()-1;l++)
				{
					temp += reg[l];
				}

				system("cls");
				cout <<endl;
				SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				cout <<"\tinput_EventName : ";
				cout << temp<<endl;
				SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
				EventList.ResetList();	// list 포인터를 초기화
				while(EventList.GetNextItem(data))	// 이름이 같은 레코드가 존재하면 그 레코드를 복사하고 1을 리턴
				{
					if(data.GetEventName().find(temp) != -1)
					{
						cout<<"\t\t"<<data.GetEventName()<<endl; 
					}
				}
				cout <<endl;
			}
		}
		else if(in == 80)
		{

		}
		else
		{
			tem = in;

			temp = temp+tem;
			system("cls");
			cout <<endl;
			SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
			cout <<"\tinput_EventName : "<< temp<<endl;
			SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
			EventList.ResetList();	// list 포인터를 초기화
			while(EventList.GetNextItem(data))	// 이름이 같은 레코드가 존재하면 그 레코드를 복사하고 1을 리턴
			{
				if(data.GetEventName().find(temp) != -1)
				{
					cout<<"\t\t"<<data.GetEventName()<<endl; 
				}
			}
			cout <<endl;
		}
	}
	target.PutEventName(temp);
	EventList.ResetList();
	for(int i=0;i<EventList.LengthIs();i++)
	{
		EventList.GetNextItem(data);
		if(target.GetEventName() == data.GetEventName())
			break;
	}
	string temp_1;
	StringRecord inData;
	int count = data.GetLength();
	photoList.ResetList();
	PhotoRecord Temp;
	while(photoList.GetNextItem(Temp))
	{
		if(Temp.GetEventName() == target.GetEventName())
		{
			break;
		}
	}
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	cout << "\t\tEvent list" << endl;cout <<endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	for(int i=0;i< count;count--)
	{
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_BLUE);
		cout << "\t==============================================" << endl;
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
		temp_1 = data.displayEvent(inData,count);
		SearchByName(temp_1);

	}
	system("pause");

	return 0;
}
/*====================================================================================
// Function: Search a photo by event time
// Pre: inData contains the time to be searched (from, to)
// Post : inData holds the record matched with input time.
If found, print photo record and return 1. Otherwise 0
// =====================================================================================*/
int Application::SearchListByEventTime(PhotoRecord& inData_01, PhotoRecord& inData_02)
{
	PhotoRecord data;	// 비교를 위해 list pointer의 값을 저장하는 변수
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	photoList.ResetList();	// list 포인터를 초기화
	int count = 0;
	while(photoList.GetNextItem(data))	// list의 모든 데이터를 파일에 쓰기
	{
		// 기간 내의 레코드가 존재하면 그 레코드를 복사하고 1을 리턴
		if(inData_01.GetEventTime() <= data.GetEventTime() && data.GetEventTime() <= inData_02.GetEventTime())
		{		
			data.PutRecordOnScreen();
			SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_BLUE);
			cout <<"\t==========================================="<<endl;
			SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
			count = 1;
		}
	}
	system("pause");
	return count;
}

/*====================================================================================
// Function: Search a photo by event content.
// Pre: inData contains the content to be searched
// Post : inData holds the record matched with input content.
If found, print photo record and return 1. Otherwise 0
// =====================================================================================*/
int Application::SearchListByEventContent(PhotoRecord& inData)
{
	PhotoRecord data;	// 비교를 위해 list pointer의 값을 저장하는 변수
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	photoList.ResetList();	// list 포인터를 초기화
	int count = 0;
	while(photoList.GetNextItem(data))	// list의 모든 데이터를 파일에 쓰기
	{
		// 이름이 같은 레코드가 존재하면 그 레코드를 출력하고 1을 리턴
		if(data.GetEventContent().find(inData.GetEventContent()) != -1)
		{

			data.PutRecordOnScreen();
			SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_BLUE);
			cout <<"\t==========================================="<<endl;
			SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);

			count = 1;
		}
	}
	system("pause");
	return count;
}

/*====================================================================================
// Function: Read in a photo name from keyboard, search the record by photo name, and display on the screen
// Pre: none
// Post : record on screen. If found, run Run02 function and return 1. Otherwise 0
// =====================================================================================*/
int Application::RetreiveRecordByPhotoName()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PhotoRecord target;
	string temp;
	int count=0;
	PhotoRecord data;
	int in;
	char tem;
	bool check = true;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	cout <<"\tinput_FileName : ";
	while(check)
	{
		in = _getch();
		switch(in)
		{
		case 13:
			{	
				int n = GetCursor(count+1);
				if(n == count+2)
				{}
				else
				{
					photoList.ResetList();
					for( int i=0;i<n-1;i++)
					{
						photoList.GetNextItem(data);
					}
					temp = data.GetPhotoName();
					check = false;
					break;
				}
				break;
			}
		case 8:
			{	
				count =0;
				if(temp.length() !=0)
				{
					string reg = temp;
					temp = "";
					for(int l=0;l < (reg.length()-1);l++)
					{
						temp += reg[l];
					}

					system("cls");
					cout <<endl;
					SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
					cout <<"\tinput_FileName : ";
					cout << temp<<"\tPress Enter"<<endl;
					SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
					photoList.ResetList();	// list 포인터를 초기화
					while(photoList.GetNextItem(data))	// 이름이 같은 레코드가 존재하면 그 레코드를 복사하고 1을 리턴
					{
						if(data.GetPhotoName().find(temp) != -1)
						{
							cout<<"\t\t"<<data.GetPhotoName()<<endl; 
							count ++;
						}
					}
					cout <<endl;
				}
				break;
			}
		default:
			{
				count =0;
				tem = in;

				temp = temp+tem;
				system("cls");
				cout <<endl;
				SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				cout <<"\tinput_FileName : "<< temp<<"\tPress Enter"<<endl;
				SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
				photoList.ResetList();	// list 포인터를 초기화
				while(photoList.GetNextItem(data))	// 이름이 같은 레코드가 존재하면 그 레코드를 복사하고 1을 리턴
				{
					if(data.GetPhotoName().find(temp) != -1)
					{
						cout<<"\t\t"<<data.GetPhotoName()<<endl; 
						count ++;
					}
				}
				cout <<endl;
			}
		}
	}
	target.PutPhotoName(temp);
	system("cls");cout <<endl;
	// 찾고자 하는 레코드가 리스트에 있으면 화면에 출력, Run02함수 출력하고 1을 리턴, 없으면 0을 리턴
	if(SearchListByPhotoName(target))
	{
		target.PutRecordOnScreen();
		system("pause");
		Run02(target);

		return 1;
	}
	else
	{
		SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_INTENSITY);
		cout << "\tNo data in the list.." << endl;
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
		return 0;
	}

}


/*====================================================================================
// Function: Program driver
// Pre: none
// Post : none
// =====================================================================================*/
void Application::Run02(PhotoRecord& target)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int loop = 1;	// while문 제어 변수 선언
	while(loop)
	{

		switch(GetCommand2())
		{
		case 2 :		// 사진기록 수정
			ModifyPhoto(target);
			break;
		case 3 :		// 수정기록 보기
			ViewHistory(target);
			break;
		case 4 :		// photo 레코드 삭제
			DeletePhoto(target);
			loop = 0;
			break;
		case 5 :
			target.PutPictureOnScreen();
			break;
		case 6:
			loop = 0;	// while문 종료
			break;
		default:
			SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_INTENSITY);
			cout << "\tIllegal sellection...\n";
			SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
			break;
		}
	}
}

/*====================================================================================
// Function: Modify a photo record in list
// Pre: 사진이 검색된다.
// Post : list is modified a photo record.
// =====================================================================================*/
int Application::ModifyPhoto(PhotoRecord& target)
{
	HistoryRecord temp;
	system("cls");
	cout <<endl;
	temp.PutRecord(target.GetEventContent());
	target.addHistory(temp);

	/////////////////
	target.GetEventContentFromKB();
	photoList.Update(target);
	return 1;
}

/*====================================================================================
// Function: 사진 수정 기록을 보여줌
// Pre: 사진이 검색된다
// Post : 검색된 사진의 수정기록을 보여준다
// =====================================================================================*/
void Application::ViewHistory(PhotoRecord& target)
{
	HistoryRecord inData;
	system("cls");
	cout <<endl;
	target.displayHistory(inData);
	system("pause");
}

/*====================================================================================
// Function: Read in two event time from keyboard, search the record by event time, and display on the screen
// Pre: none
// Post : record on screen. If found, return 1. Otherwise 0
// =====================================================================================*/
int Application::RetreiveRecordByEventTime()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	cout <<endl<<endl;
	PhotoRecord target_from;	// 검색 기간의 시작점 입력받을 변수 선언
	PhotoRecord target_to;		// 검색 기간의 끝점 입력받을 변수 선언
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\t\tFrom " << endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);

	target_from.GetEventTimeFromKB();
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\t\tTo " << endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	target_to.GetEventTimeFromKB();

	// 찾고자 하는 레코드가 리스트에 있으면 화면에 출력하고 1을 리턴, 없으면 0을 리턴
	if(SearchListByEventTime(target_from, target_to))
	{
		return 1;
	}
	else
	{
		SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_INTENSITY);
		cout << "\tNo data in the list.." << endl;
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
		system("pause");
		return 0;
	}

	return 0;
}

/*====================================================================================
// Function: Read in a event content from keyboard, search the record by event content, and display on the screen
// Pre: none
// Post : record on screen. If found, return 1. Otherwise 0
// =====================================================================================*/
int Application::RetreiveRecordByEventContent()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PhotoRecord target;
	system("cls");
	cout <<endl<<endl;
	target.GetEventContentFromKB();

	// 찾고자 하는 레코드가 리스트에 있으면 화면에 출력하고 1을 리턴, 없으면 0을 리턴
	if(SearchListByEventContent(target))
	{
		return 1;
	}
	else
	{
		SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_INTENSITY);
		cout << "\tNo data in the list.." << endl;
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
		system("pause");
		return 0;
	}
}

/*====================================================================================
// Function: Display all record in the photo list on screen
// Pre: 
// Post : photo records on screen
// =====================================================================================*/
void Application::DisplayAllPhotos()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << endl << endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	cout << "\t\tCurrent list" << endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);

	PhotoRecord temp;
	photoList.ResetList();
	for(int i=0; i<photoList.LengthIs();i++)
	{
		photoList.GetNextItem(temp);

		temp.PutRecordOnScreen();
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_BLUE);
		cout <<"\t==========================================="<<endl;
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	}
	cout <<"\t\tComplete..."<<endl;
	system("pause");
}

/*====================================================================================
// Function: Display all record in the photo list by shooting order on screen
// Pre: 
// Post : photo records on screen
// =====================================================================================*/
void Application::DisplyByShootingOrder()
{
	if(showList.LengthIs() == 0)
	{
		string tem_ev;//임시로 저장할 문자열 
		photoList.ResetList();
		PhotoRecord data;
		for(int i=0;i < photoList.LengthIs() ;i++)
		{
			photoList.GetNextItem(data);
			PhotoRecord newData; //임시 객체생성
			newData.PutRecord(data.GetEventTime(), data.GetEventName(), data.GetPhotoName(), data.GetEventContent()); // 사진 정보들을 입력받음.
			// 입력받은 레코드를 리스트에 add, 리스트가 full일 경우는 add하지 않고 0을 리턴
			if(!showList.IsFull()) 
			{
				showList.InsertItem(newData); // photo리스트 추가
			}
		}
		showList.ResetList();
		for(int i=0;i < showList.LengthIs() ;i++)
		{
			PhotoRecord newData;
			showList.GetNextItem(newData);
			tem_ev = newData.GetPhotoName();//현재 이름에 있는 값이므로 실제로는 날짜 정보를 저장.
			newData.PutPhotoName(newData.GetEventTime());
			newData.PutEvnetTime(tem_ev);
			showList.PushData(newData);
		}
	}

	//추가
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << endl << endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	cout << "\t\tShooting Order list" << endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	PhotoRecord temp;

	showList.ResetList();
	for(int i=0; i<showList.LengthIs();i++)//저장되있는 리스트 길이만큼 이동하면서 
	{
		showList.GetNextItem(temp);//다음값을 받아온다
		temp.PutRecordOnScreen();//출력
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_BLUE);
		cout <<"\t==========================================="<<endl;
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	}
	cout <<"\t\tComplete..."<<endl;
	system("pause");//누르면 다음화면으로 넘어가기
}

/*====================================================================================
// Function: Open an input file
// Pre: name should be valid
// Post: inFile holds input file information. 
//       if file open error occur, return 0. Otherwise return 1
// =====================================================================================*/
int Application::OpenInFile(string filename)
{
	inFile.open(filename);	// file open for read

	// if file open error occur, return 0, otherwise return 1
	if(!inFile)		return 0;
	else	return 1;

}

/*====================================================================================
// Function: Open an output file
// Pre: name should be valid
// Post: outFile holds output file information. 
//       if file open error occur, return 0. Otherwise return 1
// =====================================================================================*/
int Application::OpenOutFile(string filename)
{
	outFile.open(filename);	// file open for write

	// if file open error occur, return 0. otherwise return 1
	if(!outFile)	return 0;
	else	return 1;
}

/*====================================================================================
// Function: Open an input file and read all the student record from a file
// Pre: file is not opened
// Post: photoList holds all photo records read from a file. The infile is closed
//       if file open error or file read error occur, return 0. Otherwise return 1
// =====================================================================================*/
int Application::ReadPhotoListFromFile()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int index = 0;
	PhotoRecord data;	// 읽기용 임시 변수

	char filename[80];
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\t\tEnter Input file Name (photoList) : ";
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if(!OpenInFile(filename))
		return 0;

	// 파일의 모든 내용을 읽어 list에 추가
	while(!inFile.eof())
	{
		// array에 사진들의 정보가 들어있는 structure 저장
		data.GetRecordFromFile(inFile);
		AddPhoto(data);	

		//	AddEvent(data);	// 동시에 이벤트 리스트도 추가한다.
	}

	inFile.close();	// file close

	// 현재 list 출력
	DisplayAllPhotos();

	return 1;
}


/*====================================================================================
// Function: Open an output file and write all photo records to the file
// Pre: None
// Post: the photo list is stored in the output file
// =====================================================================================*/
int Application::WriteToPhotoListToFile()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PhotoRecord data;	// 쓰기용 임시 변수

	char filename[80];
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\t\tEnter Output file Name (photoList): ";
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if(!OpenOutFile(filename))
		return 0;

	// list 포인터를 초기화
	photoList.ResetList();

	// list의 모든 데이터를 파일에 쓰기
	while(photoList.GetNextItem(data))
	{
		data.PutRecordToFile(outFile);
	}
	outFile.close();	// file close

	return 1;
}