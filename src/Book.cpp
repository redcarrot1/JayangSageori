#include "Book.h"

Book::Book(string sdate, string sRoomNumber, string sUseStartTime, string sUseEndTime, string userId) {
    this->userId = userId;
    stringstream ssInt(sRoomNumber);

    int roomNumberInt;
    ssInt >> roomNumberInt;
    this->iRoomNumber = roomNumberInt;

    string startHour = sUseStartTime.substr(0, 2);
    stringstream sStartHour(startHour);

    int hourStart;
    sStartHour >> hourStart;
    this->startHour = hourStart;

    string startMinute = sUseStartTime.substr(2, 2);
    stringstream sStartMinute(startMinute);

    int minuteStart;
    sStartMinute >> minuteStart;
    this->startMin = minuteStart;

    string endHour = sUseEndTime.substr(0, 2);
    stringstream sEndHour(endHour);

    int hourEnd;
    sEndHour >> hourEnd;
    this->endHour = hourEnd;

    string endMinute = sUseEndTime.substr(2, 2);
    stringstream sEndMinute(endMinute);

    int minuteEnd;
    sEndMinute >> minuteEnd;
    this->endMin = minuteEnd;
    sIndex = (this->startHour - 9) * 2;
    eIndex = (this->startMin - 9) * 2;
    if (this->startMin == 30) {
        sIndex += 1;
    }
    if (this->endMin == 30) {
        eIndex += 1;
    }

    sdate.erase(remove(sdate.begin(), sdate.end(), '-'), sdate.end());
    this->sdate = sdate;

    bookFileData = File::getBooking(sdate);
    userData = File::getUserData(userId);

    /* Test Code
    cout << this->sdate << endl;
    cout << bookFileData.size() << endl;
    cout << userData.size() << endl;
     */
}

void Book::excuteBook() {
    if (checkReservation()) {
        updateBookFileData();
        updateBookfile();
    }
}


bool Book::checkReservation() {
    try {
        if ((startHour > endHour) || (startHour == endHour && startMin > endMin)) {
            throw WrongRuleArgumentException(this->sUseEndTime, "예약 종료 시간은 예약 시작 시간보다 빨라질 수 없습니다.");
        }
    }
    catch (exception &e) {
        exceptionMannager(e);
    }

    // 예약되어있는지 확인
    vector<int> reservedIndex;
    for (int i = sIndex; i < eIndex; i++) {
        if (bookFileData[iRoomNumber][i] != "0") {
            reservedIndex.push_back(i);
        }
    }

    if (reservedIndex.size() > 0) {
        int start = *reservedIndex.begin();
        int end = *reservedIndex.end();
        cout << "[오류] date studyroomnumber 번 스터디룸 " << endl;
        return false;
    }

    return true;
}

void Book::updateBookFileData() {
    vector<string> data = File::getMetaData();
    for (int i = sIndex; i < eIndex; i++) {
        bookFileData[iRoomNumber][i] = data[3];
    }
    userData[0].push_back(data[3] + "\t" + sdate + "\t" + sUseStartTime + "\t" + sUseEndTime + "\t" + sRoomNumber);
}

void Book::updateBookfile() {
    File::setUserData(userId, userData);
    File::setBooking(sdate, bookFileData);
}
