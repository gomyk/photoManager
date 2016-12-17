/* ==============================  Application Class  =====================================
- Application : The class representing an application for Project 1
===============================================================================================*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "PhotoClass.h"
#include "DoublySortedClass.h"


using namespace std;

class Application
{
public:
	Application(void);	// default constructor
	~Application(void);	// default destructor

	/*====================================================================================
	// Function: Program driver
	// Pre: none
	// Post : none
    // =====================================================================================*/
	void Run01();

	void Run02(PhotoRecord& inData);
	/*====================================================================================
	// Function: Program driver
	// Pre: none
	// Post : none
    // =====================================================================================*/
	void Run03();

	/*====================================================================================
	// Function: Display command on screen and get a input from keyboard
	// Pre: 
	// Post : get command number.
    // =====================================================================================*/
	int GetCommand();

	/*====================================================================================
	// Function: Display command on screen and get a input from keyboard
	// Pre: 
	// Post : get command number.
    // =====================================================================================*/
	int GetCursor(int max);
	/*====================================================================================
	// Function: Display command on screen and get a input from keyboard
	// Pre: 
	// Post : get command number.
    // =====================================================================================*/
	int GetCommand2();

	/*====================================================================================
	// Function: Display command on screen and get a input from keyboard
	// Pre: 
	// Post : get command number.
    // =====================================================================================*/
	int GetCommand3();

	/*====================================================================================
	// Function: Add new photo record to list
	// Pre: 
	// Post : list is added new photo record.
	// =====================================================================================*/
	int AddPhoto(PhotoRecord& newData);

	/*====================================================================================
	// Function: Delete a studentphoto record in list
	// Pre: 
	// Post : list is deleted a photo record.
	// =====================================================================================*/
	int DeletePhoto(PhotoRecord& target);
	/*====================================================================================
	// Function: Modify a photo record in list
	// Pre: 
	// Post : list is modified a photo record.
	// =====================================================================================*/
	int ModifyPhoto(PhotoRecord& inData);

	/*====================================================================================
	// Function: 사진 수정 기록을 보여줌
	// Pre: 사진이 검색된다
	// Post : 검색된 사진의 수정기록을 보여준다
	// =====================================================================================*/
	void ViewHistory(PhotoRecord& inData);

	/*====================================================================================
	// Function: Search a photo by photoname
	// Pre: inData contains the name to be searched
	// Post : inData holds the record matched with input photoname. If found, return 1. Otherwise 0
    // =====================================================================================*/
	int SearchListByPhotoName(PhotoRecord& inData);
	int SearchByName(string temp);
	/*====================================================================================
	// Function: Search a photo by event time
	// Pre: inData contains the time to be searched
	// Post : inData holds the record matched with input time. If found, return 1. Otherwise 0
    // =====================================================================================*/
	int SearchListByEventTime(PhotoRecord& inData_01, PhotoRecord& inData_02);

	/*====================================================================================
	// Function: Search a photo by event content.
	// Pre: inData contains the content to be searched
	// Post : inData holds the record matched with input content. If found, return 1. Otherwise 0
    // =====================================================================================*/
	int SearchListByEventContent(PhotoRecord& inData);

	/*====================================================================================
	// Function: Read in a photo name from keyboard, search the record by photo name, and display on the screen
	// Pre: none
	// Post : record on screen. If found, return 1. Otherwise 0
    // =====================================================================================*/
	int RetreiveRecordByPhotoName();
	/*====================================================================================
	// Function: Read in a photo Event from keyboard, search the record by photo Event, and display on the screen
	// Pre: none
	// Post : record on screen. If found, return 1. Otherwise 0
    // =====================================================================================*/
	int RetreiveRecordByEventName();
	/*====================================================================================
	// Function: Read in a event time from keyboard, search the record by event time, and display on the screen
	// Pre: none
	// Post : record on screen. If found, return 1. Otherwise 0
    // =====================================================================================*/
	int RetreiveRecordByEventTime();

	/*====================================================================================
	// Function: Read in a event content from keyboard, search the record by event content, and display on the screen
	// Pre: none
	// Post : record on screen. If found, return 1. Otherwise 0
    // =====================================================================================*/
	int RetreiveRecordByEventContent();

	/*====================================================================================
	// Function: Display all record in the photo list on screen
	// Pre: 
	// Post : photo records on screen
   =====================================================================================*/
	void DisplayAllPhotos();

	/*====================================================================================
	// Function: Open an input file
	// Pre: name should be valid
	// Post: inFile holds input file information. 
	//       if file open error occur, return 0. Otherwise return 1
    =====================================================================================*/
	int OpenInFile(string filename);

	/*====================================================================================
	// Function: Open an output file
	// Pre: name should be valid
	// Post: outFile holds output file information. 
	//       if file open error occur, return 0. Otherwise return 1
    =====================================================================================*/
	int OpenOutFile(string filename);

	/*====================================================================================
	// Function: Open an input file and read all the student record from a file
	// Pre: file is not opened
	// Post: photoList holds all photo records read from a file. The infile is closed
	//       if file open error or file read error occur, return 0. Otherwise return 1
    =====================================================================================*/
	int ReadPhotoListFromFile();

	/*====================================================================================
	// Function: Open an output file and write all photo records to the file
	// Pre: None
	// Post: the photo list is stored in the output file
   =====================================================================================*/
	int WriteToPhotoListToFile();
	
	/*====================================================================================
	// Function: Display all record in the photo list by shooting order on screen
	// Pre: 
	// Post : photo records on screen
	// =====================================================================================*/
	void DisplyByShootingOrder();

	void gotoxy(int x, int y)
	{
	 COORD Pos = { x, y };
	 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

private :
	ifstream inFile;	// input file descriptor
	ofstream outFile;	// output file descriptor
	SortedListType<PhotoRecord> photoList;		// photo list
	SortedListType<EventRecord> EventList;		// Event list
	SortedListType<PhotoRecord> showList;		// show List
	int curCommand;			// current command number
};

