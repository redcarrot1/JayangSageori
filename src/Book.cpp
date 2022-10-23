#include "Book.h"

Book::Book(string sdate, string sRoomNumber, string sUseStartTime, string sUseEndTime, string userId) {
    this->sOriginDate = sdate;
    this->userId = userId;

    this->sRoomNumber = sRoomNumber;
    this->iRoomNumber = stoi(sRoomNumber);

    this->sUseStartTime = sUseStartTime;
    this->sUseEndTime = sUseEndTime;

    this->startHour = stoi(sUseStartTime.substr(0, 2));
    this->startMin = stoi(sUseStartTime.substr(3));

    this->endHour = stoi(sUseEndTime.substr(0, 2));
    this->endMin = stoi(sUseEndTime.substr(3));
    validTime();

    sIndex = (this->startHour - 9) * 2;
    eIndex = (this->endHour - 9) * 2;
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
}


bool Book::checkReservation() {
    // 예약되어있는지 확인
    vector<int> reservedIndex;
    for (int i = sIndex; i < eIndex; i++) {
        if (bookFileData[iRoomNumber][i] != "0") {
            reservedIndex.push_back(i);
        }
    }

    if (reservedIndex.size() > 0) {
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
    if (this->startHour < 9 || this->startHour > 19)
        throw WrongRuleArgumentException(this->sUseStartTime, "스터디룸은 09:00 ~ 20:00까지 운영합니다.");

    if (this->endHour < 9 || this->endHour > 20 || (this->endHour == 20 && this->endMin == 30)) {
        throw WrongRuleArgumentException(this->sUseEndTime, "스터디룸은 09:00 ~ 20:00까지 운영합니다.");
    }

    if (this->startHour == this->endHour) {
        if (this->startMin >= this->endMin)
            throw WrongRuleArgumentException(this->sUseEndTime, "예약 끝나는 시각은 시작 시각 이후여야 합니다.");
    }
    else if (this->startHour > this->endHour)
        throw WrongRuleArgumentException(this->sUseEndTime, "예약 끝나는 시각은 시작 시각 이후여야 합니다.");
}
