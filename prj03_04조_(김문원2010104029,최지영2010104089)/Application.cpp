#include "Application.h"

Application::Application(void)
{
	curCommand = 0;	// curCommand�� 0���� �ʱ�ȭ
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
				PhotoRecord newData;	// PhotoRecordŬ���� ��ü ����
				newData.GetRecordFromKB();	// ���� �������� �Է¹���.
				AddPhoto(newData);	// �Է¹��� ������ ���� �߰�
				DisplayAllPhotos();	// �����߰��� �Ϸ�� �� ��� ���� ���
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
		case 6:		// �������� �޴� ���
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
	int loop = 1;	// while�� ���� ���� ����
	while(loop)
	{
		switch(GetCommand3())
		{
		case 2 :		// �Ⱓ���� ����
			RetreiveRecordByEventTime();
			break;
		case 3 :		// event name���� ����
			RetreiveRecordByEventName();
			break;
		case 4 :		// ������������ ����
			RetreiveRecordByEventContent();
			break;
		case 5 :		// �Կ��� ������� ����
			DisplyByShootingOrder();
			break;
		case 6 :		// ��� ���� ���
			DisplayAllPhotos();
			break;
		case 7 :
			loop = 0;	// while�� ����
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
		cout<<"��";

		command =_getch();
		switch(command)
		{
			//����
		case 72:
			{
				if(y>1 && y<max+1)
				{
					gotoxy(x,y);
					cout<<"  ";	// ���� �����
				}
				y--;// Ŀ�� ����
				if(y<2)
				{y=max;}
				break;
			}
			//�Ʒ���
		case 80:
			{
				if(y>1 && y<max+1)
				{
					gotoxy(x,y);
					cout<<"  ";	// ���� �����
				}
				y++;	// Ŀ�� �Ʒ���
				if(y>max)	// �����̼� ȿ��
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
	cout << "\t     ��Quit the Program(BackSpace)�� "<<endl;  
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	return GetCursor(6);//Ŀ���̵��� ���� �Լ� 
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
	cout << "\t     ��Go to Menu(BackSpace)�� "<<endl; 
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	return GetCursor(5);//Ŀ���̵��� ���� �Լ�
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
	cout << "\t     ��Go to Menu(BackSpace)�� "<<endl; 
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	return GetCursor(6);//Ŀ���̵��� ���� �Լ�
}
/*====================================================================================
// Function: Add new photo record to list
// Pre: 
// Post : list is added new photo record.
// =====================================================================================*/
int Application::AddPhoto(PhotoRecord& newData) 
{
	bool check = false;	// bool�� ���� �����ϰ� false�� �ʱ�ȭ
	EventRecord newData_E;	// EventRecordŬ���� ��ü ����
	EventRecord temp;	// EventRecordŬ���� ��ü ����
	newData_E.PutEventName(newData.GetEventName());	// �̺�Ʈ �̸��� ����

	EventList.ResetList();	// �̺�Ʈ ����Ʈ�� �ʱ�ȭ�ϰ�

	if(!photoList.IsFull())	// �Է¹��� ���ڵ带 ����Ʈ�� add, ����Ʈ�� full�� ���� add���� �ʰ� 0�� ����
	{
		photoList.InsertItem(newData);	// photo����Ʈ �߰�
		for(int i=0;i<EventList.LengthIs();i++)	// ���ο� ����Ÿ�� �̺�Ʈ���� �̺�Ʈ ����Ʈ�� �����ϴ��� ã���ִ� �ݺ���
		{
			EventList.GetNextItem(temp);
			if(temp.GetEventName() == newData_E.GetEventName())	// ���� �̸��� ������ ���
			{
				newData_E = temp;
				StringRecord inData;
				inData.PutRecord(newData.GetPhotoName());	// �����̸��� ����
				newData_E.addEvent(inData);	// �ش� �̺�Ʈ ����Ʈ�� ��忡 ���� �̸� �߰�
				EventList.Update(newData_E);	// �̺�Ʈ ����Ʈ ������Ʈ
				check = true;
			}
		}

		if(!check)
		{
			EventList.InsertItem(newData_E);// Event����Ʈ �߰�
			StringRecord inData;
			inData.PutRecord(newData.GetPhotoName());	// �����̸��� ����
			newData_E.addEvent(inData);	// �ش� �̺�Ʈ ����Ʈ�� ��忡 ���� �̸� �߰�
			EventList.Update(newData_E);	// �̺�Ʈ ����Ʈ ������Ʈ
		}

	}
	else	return 0;
	// ���� list ���
	return 1;
}

/*====================================================================================
// Function: Delete a photo record in list
// Pre: 
// Post : list is deleted a photo record.
// =====================================================================================*/
int Application::DeletePhoto(PhotoRecord& target)
{

	EventRecord target_E;	// EventRecordŬ���� ��ü ����
	EventRecord temp;	// EventRecordŬ���� ��ü ����
	target_E.PutEventName(target.GetEventName());	// �̺�Ʈ �̸��� ����
	EventList.ResetList();
	for(int i=0;i<EventList.LengthIs();i++)	// �ش� �̺�Ʈ ��带 ã�� �ݺ���
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


	photoList.DeleteItem(target);	// photo ���ڵ� ����

	// ���� list ���
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
	PhotoRecord data2;	// �񱳸� ���� list pointer�� ���� �����ϴ� ����

	photoList.ResetList();	// list �����͸� �ʱ�ȭ

	while(photoList.GetNextItem(data2))	// �̸��� ���� ���ڵ尡 �����ϸ� �� ���ڵ带 �����ϰ� 1�� ����
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
// Function: �ش� �̺�Ʈ�� ������ ã�� ���
// Pre: photolist�� ������.
// Post : �̺�Ʈ ������ ��µ�.
// =====================================================================================*/
int Application::SearchByName(string inData)
{
	PhotoRecord data;
	photoList.ResetList();
	while(photoList.GetNextItem(data))	// �̸��� ���� ���ڵ尡 �����ϸ� �� ���ڵ带 �����ϰ� 1�� ����
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
				EventList.ResetList();	// list �����͸� �ʱ�ȭ
				while(EventList.GetNextItem(data))	// �̸��� ���� ���ڵ尡 �����ϸ� �� ���ڵ带 �����ϰ� 1�� ����
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
			EventList.ResetList();	// list �����͸� �ʱ�ȭ
			while(EventList.GetNextItem(data))	// �̸��� ���� ���ڵ尡 �����ϸ� �� ���ڵ带 �����ϰ� 1�� ����
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
	PhotoRecord data;	// �񱳸� ���� list pointer�� ���� �����ϴ� ����
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	photoList.ResetList();	// list �����͸� �ʱ�ȭ
	int count = 0;
	while(photoList.GetNextItem(data))	// list�� ��� �����͸� ���Ͽ� ����
	{
		// �Ⱓ ���� ���ڵ尡 �����ϸ� �� ���ڵ带 �����ϰ� 1�� ����
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
	PhotoRecord data;	// �񱳸� ���� list pointer�� ���� �����ϴ� ����
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	photoList.ResetList();	// list �����͸� �ʱ�ȭ
	int count = 0;
	while(photoList.GetNextItem(data))	// list�� ��� �����͸� ���Ͽ� ����
	{
		// �̸��� ���� ���ڵ尡 �����ϸ� �� ���ڵ带 ����ϰ� 1�� ����
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
					photoList.ResetList();	// list �����͸� �ʱ�ȭ
					while(photoList.GetNextItem(data))	// �̸��� ���� ���ڵ尡 �����ϸ� �� ���ڵ带 �����ϰ� 1�� ����
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
				photoList.ResetList();	// list �����͸� �ʱ�ȭ
				while(photoList.GetNextItem(data))	// �̸��� ���� ���ڵ尡 �����ϸ� �� ���ڵ带 �����ϰ� 1�� ����
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
	// ã���� �ϴ� ���ڵ尡 ����Ʈ�� ������ ȭ�鿡 ���, Run02�Լ� ����ϰ� 1�� ����, ������ 0�� ����
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
	int loop = 1;	// while�� ���� ���� ����
	while(loop)
	{

		switch(GetCommand2())
		{
		case 2 :		// ������� ����
			ModifyPhoto(target);
			break;
		case 3 :		// ������� ����
			ViewHistory(target);
			break;
		case 4 :		// photo ���ڵ� ����
			DeletePhoto(target);
			loop = 0;
			break;
		case 5 :
			target.PutPictureOnScreen();
			break;
		case 6:
			loop = 0;	// while�� ����
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
// Pre: ������ �˻��ȴ�.
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
// Function: ���� ���� ����� ������
// Pre: ������ �˻��ȴ�
// Post : �˻��� ������ ��������� �����ش�
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
	PhotoRecord target_from;	// �˻� �Ⱓ�� ������ �Է¹��� ���� ����
	PhotoRecord target_to;		// �˻� �Ⱓ�� ���� �Է¹��� ���� ����
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\t\tFrom " << endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);

	target_from.GetEventTimeFromKB();
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\t\tTo " << endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	target_to.GetEventTimeFromKB();

	// ã���� �ϴ� ���ڵ尡 ����Ʈ�� ������ ȭ�鿡 ����ϰ� 1�� ����, ������ 0�� ����
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

	// ã���� �ϴ� ���ڵ尡 ����Ʈ�� ������ ȭ�鿡 ����ϰ� 1�� ����, ������ 0�� ����
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
		string tem_ev;//�ӽ÷� ������ ���ڿ� 
		photoList.ResetList();
		PhotoRecord data;
		for(int i=0;i < photoList.LengthIs() ;i++)
		{
			photoList.GetNextItem(data);
			PhotoRecord newData; //�ӽ� ��ü����
			newData.PutRecord(data.GetEventTime(), data.GetEventName(), data.GetPhotoName(), data.GetEventContent()); // ���� �������� �Է¹���.
			// �Է¹��� ���ڵ带 ����Ʈ�� add, ����Ʈ�� full�� ���� add���� �ʰ� 0�� ����
			if(!showList.IsFull()) 
			{
				showList.InsertItem(newData); // photo����Ʈ �߰�
			}
		}
		showList.ResetList();
		for(int i=0;i < showList.LengthIs() ;i++)
		{
			PhotoRecord newData;
			showList.GetNextItem(newData);
			tem_ev = newData.GetPhotoName();//���� �̸��� �ִ� ���̹Ƿ� �����δ� ��¥ ������ ����.
			newData.PutPhotoName(newData.GetEventTime());
			newData.PutEvnetTime(tem_ev);
			showList.PushData(newData);
		}
	}

	//�߰�
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << endl << endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	cout << "\t\tShooting Order list" << endl;
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	PhotoRecord temp;

	showList.ResetList();
	for(int i=0; i<showList.LengthIs();i++)//������ִ� ����Ʈ ���̸�ŭ �̵��ϸ鼭 
	{
		showList.GetNextItem(temp);//�������� �޾ƿ´�
		temp.PutRecordOnScreen();//���
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_BLUE);
		cout <<"\t==========================================="<<endl;
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	}
	cout <<"\t\tComplete..."<<endl;
	system("pause");//������ ����ȭ������ �Ѿ��
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
	PhotoRecord data;	// �б�� �ӽ� ����

	char filename[80];
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\t\tEnter Input file Name (photoList) : ";
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if(!OpenInFile(filename))
		return 0;

	// ������ ��� ������ �о� list�� �߰�
	while(!inFile.eof())
	{
		// array�� �������� ������ ����ִ� structure ����
		data.GetRecordFromFile(inFile);
		AddPhoto(data);	

		//	AddEvent(data);	// ���ÿ� �̺�Ʈ ����Ʈ�� �߰��Ѵ�.
	}

	inFile.close();	// file close

	// ���� list ���
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
	PhotoRecord data;	// ����� �ӽ� ����

	char filename[80];
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout << "\t\tEnter Output file Name (photoList): ";
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if(!OpenOutFile(filename))
		return 0;

	// list �����͸� �ʱ�ȭ
	photoList.ResetList();

	// list�� ��� �����͸� ���Ͽ� ����
	while(photoList.GetNextItem(data))
	{
		data.PutRecordToFile(outFile);
	}
	outFile.close();	// file close

	return 1;
}