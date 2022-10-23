#include "Book.h"

Book::Book(string sdate, string sRoomNumber, string sUseStartTime, string sUseEndTime, string userId) {
    validTime();

    this->userId = userId;
    stringstream ssInt(sRoomNumber);
    this->sRoomNumber = sRoomNumber;
    int roomNumberInt;
    ssInt >> roomNumberInt;
    this->iRoomNumber = roomNumberInt;
    this->sUseStartTime = sUseStartTime;
    this->sUseEndTime = sUseEndTime;
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
    eIndex = (this->endHour - 9) * 2;
    if (this->startMin == 30) {
        sIndex += 1;
    }
    if (this->endMin == 30) {
        eIndex += 1;
    }

    this->sOriginDate = sdate;
    sdate.erase(remove(sdate.begin(), sdate.end(), '-'), sdate.end());
    this->sdate = sdate;

    bookFileData = File::getBooking(sdate);
    userData = File::getUserData(userId);
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
        int start = reservedIndex[0];
        int end = reservedIndex[reservedIndex.size() - 1];


        cout << "[오류] " << sOriginDate << " " << sRoomNumber << "번 스터디룸 " << this->sUseStartTime << " ~ "
             << this->sUseEndTime << "는 예약 불가능한 상태입니다." << endl;
        return false;
    }

    return true;
}

void Book::updateBookFileData() {
    vector<string> data = File::getMetaData();

    for (int i = sIndex; i < eIndex; i++) {
        bookFileData[iRoomNumber][i] = data[3];
    }

    vector<string> newData;
    newData.push_back(data[3]);
    newData.push_back(sdate);
    newData.push_back(sUseStartTime);
    newData.push_back(sUseEndTime);
    newData.push_back(sRoomNumber);
    userData.push_back(newData);
}

void Book::updateBookfile() {
    File::setUserData(userId, userData);
    File::setBooking(sdate, bookFileData);
}

void Book::excuteBook() {
    if (checkReservation()) {
        updateBookFileData();
        updateBookfile();
        cout << this->sOriginDate << " " << this->sRoomNumber << "번 스터디룸 " << this->sUseStartTime << " ~ "
             << this->sUseEndTime << " 로 정상 예약되었습니다." << endl;
    }
}

void Book::validTime() {

    int startHour = stoi(this->sUseStartTime.substr(0, 2));
    int startMinute = stoi(this->sUseStartTime.substr(3));
    if (startHour < 9 || startHour > 19)
        throw WrongRuleArgumentException(sUseStartTime, "스터디룸은 09:00 ~ 20:00까지 운영합니다.");

    int endHour = stoi(this->sUseEndTime.substr(0, 2));
    int endMinute = stoi(this->sUseEndTime.substr(3));
    if (endHour < 9 || endHour > 19) {
        throw WrongRuleArgumentException(sUseEndTime, "스터디룸은 09:00 ~ 20:00까지 운영합니다.");
    }

    if (startHour == endHour) {
        if (startMinute >= endMinute)
            throw WrongRuleArgumentException(sUseEndTime, "예약 끝나는 시각은 시작 시각 이후여야 합니다.");
    }
    else if (startHour > endHour)
        throw WrongRuleArgumentException(sUseEndTime, "예약 끝나는 시각은 시작 시각 이후여야 합니다.");
}
