/* =================================  ItemType Class  ========================================
- ItemType : The class representing a record
=============================================================================================*/

#pragma once
#include <iostream>
#include "DoublySortedClass.h"
#include "HistoryClass.h"
#include "EventClass.h"
#include <fstream>
#include <string>

static HWND  hConWnd;

 HWND BCX_Bitmap(char*,HWND=0,int=0,int=0,int=0,int=0,int=0,int=0,int=0,int=0);
 HWND GetConsoleWndHandle(void);

using namespace std;

class PhotoRecord
{
private :
	string PhotoName;		// photo name
	string EventName;		// event name
	string EventTime;		// event time
	string EventContent;	// event content
	SortedListType<HistoryRecord> historyList;


public:
	PhotoRecord(void);		// 생성자
	~PhotoRecord(void);	// 소멸자
	void addHistory(HistoryRecord& inData);
	void displayHistory(HistoryRecord&);

	string GetPhotoName() {return PhotoName;};	// get photo name
	string GetEventName() {return EventName;};	// get event name
	string GetEventTime() { return EventTime;};	// get event time
	string GetEventContent() {return EventContent;};	// get event content
	void PutPhotoName(string inPhotoName) {PhotoName = inPhotoName;};	// put photo namein
	void PutEventName(string inEventName) {EventName = inEventName;};	// put event name
	void PutEvnetTime(string inEventTime) {EventTime = inEventTime;};	// put event time
	void PutEventContent(string inEventContent) {EventContent = inEventContent;};	// put event content

	void PutRecord(string inPhotoName, string inEventName, string inEventTime, string inEventContent)	// put a record
	{
		PhotoName = inPhotoName;
		EventName = inEventName;
		EventTime = inEventTime;
		EventContent = inEventContent;
	};

	/*===================================================================================
	// Function: Disply photo name on screen
	// Pre : none
	// Post: photo name on screen
	=====================================================================================*/
	void PutPhotoNameOnScreen()
	{
		cout << "\tPhoto Name : "<< PhotoName << endl; 
	};

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
	// Function: Disply event time on screen
	// Pre : none
	// Post: event time on screen
	=====================================================================================*/
	void PutEventTimeOnScreen()
	{
		cout << "\tEvent Time : "<< EventTime << endl; 
	};

	/*===================================================================================
	// Function: Disply event content on screen
	// Pre : none
	// Post: event content on screen
	=====================================================================================*/
	void PutEventContentOnScreen()
	{
		cout << "\tEvent Content : "<< EventContent << endl; 
	};

	/*===================================================================================
	// Function: Display a record on screen
	// Pre : none
	// Post: record on screen
	=====================================================================================*/
	void PutRecordOnScreen()
	{
		PutPhotoNameOnScreen();
		PutEventNameOnScreen();
		PutEventTimeOnScreen();
		PutEventContentOnScreen();
	};
	void PutPictureOnScreen()
	{
		hConWnd = GetConsoleWndHandle();
		system("cls");
		string st(PhotoName);
		char* File;
		File = ((char*)st.c_str());
		if (hConWnd)
		{
			int arrow;
			bool check = true;
			DestroyWindow(hConWnd);
			BCX_Bitmap(File,hConWnd,123,30,30,0,0,0,0,0); 
			// select a bitmap file you have or use one of the files in the Windows folder
			// filename, handle, ID, ulcX, ulcY, width, height   0,0 auto-adjusts
			while(check)
			{
				cout <<"\tGo Back To Menu(BackSpace)"<<endl;
				arrow = _getch();
				if(arrow == 8)
				{
					for(int i=0;i<20;i++)
					{
						cout <<"▶▷▶▷▶▷▶▷▶▷▶▷▶▷▶▷▶▷▶▷▶▷▶▷▶▷▶▷"<<endl;
					}
					check = false;

				}
				system("cls");
			}
		}
		system("cls");
	};



	/*===================================================================================
	// Function: Display a record on screen
	// Pre : none
	// Post: record on screen
	=====================================================================================*/





	/*===================================================================================
	// Function: Read photo name from keyboard
	// Pre: none
	// Post: photo name holds new photo name form keyboard.
	//       if invalid photo name, the return 0. Otherwise return 1
	=====================================================================================*/
	int GetPhotoNameFromKB();

	/*===================================================================================
	// Function: Read event name from keyboard
	// Pre: none
	// Post: event name holds new event name form keyboard.
	//       if invalid event name, the return 0. Otherwise return 1
	=====================================================================================*/
	int GetEventNameFromKB();

	/*===================================================================================
	// Function: Read event time from keyboard
	// Pre: none
	// Post: event time holds new event time form keyboard.
	//       if invalid event time, the return 0. Otherwise return 1
	=====================================================================================*/
	int GetEventTimeFromKB();

	/*===================================================================================
	// Function: Read event content from keyboard
	// Pre: none
	// Post: event content holds new event content form keyboard.
	//       if invalid event content, then return 0. Otherwise return 1
	=====================================================================================*/
	int GetEventContentFromKB();

	/*===================================================================================
	// Function: Read a record from keyboard
	// Pre: none
	// Post: this holds new record form keyboard.
	//       if invalid record, then return 0. Otherwise return 1
	=====================================================================================*/
	int GetRecordFromKB();

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

	bool operator>(PhotoRecord &);		// > 연산자 재정의
	bool operator==(PhotoRecord&);		// == 연산자 재정의
	bool operator<(PhotoRecord&);		// < 연산자 재정의

	void operator=(PhotoRecord &);	// = 연산자 재정의

	HWND BCX_Bitmap(char* Text,HWND hWnd,int id,int X,int Y,int W,int H,int Res,int Style,int Exstyle)
{
	HWND A;
	HBITMAP hBitmap;

	// set default style
	if (!Style) Style = WS_CHILD|WS_VISIBLE|SS_BITMAP|WS_TABSTOP;

	// form for the image
	A = CreateWindowEx(Exstyle,"static",NULL,Style,X,Y,0,0,hWnd,(HMENU)id,GetModuleHandle(0),NULL);

	// Text contains filename
	hBitmap=(HBITMAP)LoadImage(0,Text,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);

	// auto-adjust width and height
	if (W || H) hBitmap = (HBITMAP)CopyImage(hBitmap,IMAGE_BITMAP,W,H,LR_COPYRETURNORG);
	SendMessage(A,(UINT)STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hBitmap);
	if (W || H) SetWindowPos(A,HWND_TOP,X,Y,W,H,SWP_DRAWFRAME);
	return A;
}

HWND GetConsoleWndHandle(void)
{
	HWND hConWnd;
	OSVERSIONINFO os;
	char szTempTitle[64], szClassName[128], szOriginalTitle[1024];

	os.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
	GetVersionEx( &os );
	// may not work on WIN9x
	if ( os.dwPlatformId == VER_PLATFORM_WIN32s ) return 0;

	GetConsoleTitle( szOriginalTitle, sizeof ( szOriginalTitle ) );
	sprintf( szTempTitle,"%u - %u", GetTickCount(), GetCurrentProcessId() );
	SetConsoleTitle( szTempTitle );
	Sleep( 40 );
	// handle for NT and XP
	hConWnd = FindWindow( NULL, szTempTitle );
	SetConsoleTitle( szOriginalTitle );

	// may not work on WIN9x
	if ( os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
	{
		hConWnd = GetWindow( hConWnd, GW_CHILD );
		if ( hConWnd == NULL ) return 0;
		GetClassName( hConWnd, szClassName, sizeof ( szClassName ) );
		// while ( _stricmp( szClassName, "ttyGrab" ) != 0 )
		while ( strcmp( szClassName, "ttyGrab" ) != 0 )
		{
			hConWnd = GetNextWindow( hConWnd, GW_HWNDNEXT );
			if ( hConWnd == NULL ) return 0;
			GetClassName( hConWnd, szClassName, sizeof( szClassName ) );
		}
	}
	return hConWnd;
}

};
