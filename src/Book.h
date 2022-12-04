#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "ExceptionClass.h"
#include "Parsing.h"
#include "User.h"
#include "File.h"
#include "Optimize.h"

using namespace std;

class Book {
private:
    string sdate;
    string sOriginDate;
    string sRoomNumber;
    string sUseStartTime;
    string sUseEndTime;
    string sPeopleNum;

    int startIndex;
    int endIndex;

    string fDate;
    int iRoomNumber;
    int startHour;
    int startMin;
    int endHour;
    int endMin;
    int peopleNum;

    int sIndex, eIndex;
    string userId;
    vector<vector<string>> bookFileData;
    vector<vector<string>> userData;

    bool checkReservation();

    void updateBookFileData();

    void updateBookfile();

    void validTime();

    void validDate();
    void validRoomNumber();
    void validPeopleNumber();

public:
    Book(string sdate, string sRoomNumber, string sUseStartTime, string sUseEndTime, string userId, string sPeopleNum);

    void excuteBook();
};

