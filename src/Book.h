#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "ExceptionClass.h"
#include "Parsing.h"
#include "User.h"
#include "File.h"

using namespace std;

class Book
{
public:
	Book() = delete;
	Book(string sdate, string sRoomNumber, string sUseStartTime, string sUseEndTime, string userId);
	void checkReservation();
	void updateBookFileData();
	void updateBookfile();
private:
	string sdate;
	string sRoomNumber;
	string sUseStartTime;
	string sUseEndTime;
	
	int startIndex;
	int endIndex;

	string fDate;
	int iRoomNumber;
	int startHour;
	int startMin;
	int endHour;
	int endMin;
	
	int sIndex, eIndex;
	string userId;
	vector<vector<string>> bookFileData;
	vector<vector<string>> userData;
	
};

