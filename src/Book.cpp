#include "Book.h"

Book::Book(string sdate, string sRoomNumber, string sUseStartTime, string sUseEndTime, string userId, string sPeopleNum) {
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

    this->sPeopleNum = sPeopleNum;
    this->peopleNum = stoi(sPeopleNum);

    validTime();
    validDate();
    validRoomNumber();
    validPeopleNumber();

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
    bookFileData = { {} };
    if (stoi(File::getMetaData()[3 + stoi(sRoomNumber)]) >= stoi(sPeopleNum)) {
        bookFileData = Optimize::optimize(this->sdate, this->sUseStartTime, this->sUseEndTime, this->sRoomNumber);

    }
    userData = File::getUserData(userId);
}


bool Book::checkReservation() {
    // 예약되어있는지 확인
    if (bookFileData.size() == 1) {
        cout << "[오류] " << sOriginDate << " " << sRoomNumber << "번 스터디룸 " << this->sUseStartTime << " ~ "
            << this->sUseEndTime << "는 예약 불가능한 상태입니다." << endl;
        return false;
    }

    return true;
}

bool comp(vector<string>& v1, vector<string>& v2) {
    // 1. 예약 날짜 비교
    string date1 = v1[1], date2 = v2[1];
    date1.erase(remove(date1.begin(), date1.end(), '-'), date1.end());
    date2.erase(remove(date2.begin(), date2.end(), '-'), date2.end());

    if (date1 > date2) return false;
    else if (date1 < date2) return true;


    // 2. 시작 시각 비교
    string start1 = v1[2], start2 = v2[2];
    start1.erase(remove(start1.begin(), start1.end(), ':'), start1.end());
    start2.erase(remove(start2.begin(), start2.end(), ':'), start2.end());

    if (start1 > start2) return false;
    else if (start1 < start2) return true;


    // 3. 종료 시각 비교
    string end1 = v1[v1.size()-2], end2 = v2[v2.size()-2];
    end1.erase(remove(end1.begin(), end1.end(), ':'), end1.end());
    end2.erase(remove(end2.begin(), end2.end(), ':'), end2.end());

    if (end1 > end2) return false;
    else if (end1 < end2) return true;


    // 4. 방 번호 비교
    string num1 = v1[v1.size()-1], num2 = v2[v2.size() -1];
    if (num1[0] - '0' > num2[0] - '0') return false;
    else return true;
}

void Book::updateBookFileData() {
    vector<string> data = File::getMetaData();
    data[3] = to_string(stoi(data[3]) + 1);

    for (int i = sIndex; i < eIndex; i++) {
        bookFileData[iRoomNumber][i] = data[3];
    }

    vector<string> newData;
    newData.push_back(data[3]);
    newData.push_back(sOriginDate);
    newData.push_back(sUseStartTime);
    newData.push_back(sUseEndTime);
    newData.push_back(sRoomNumber);
    userData.push_back(newData);
    sort(userData.begin(), userData.end(), comp); 
}

//book book x   
void Book::updateBookfile() {
    vector<string> data = File::getMetaData();

    data[3] = to_string(stoi(data[3]) + 1);
    File::setUserData(userId, userData);
    File::setBooking(sOriginDate, bookFileData);
    cout << "addReserNum start" << endl;
    File::addReserNum(sPeopleNum, userId);
    cout << "addReserNum end" << endl;
}

void Book::excuteBook() {
    if (checkReservation()) {
        cout << "Can Resulvation" << endl;
        updateBookFileData();
        cout << "Update Book File Data Success" << endl;
        updateBookfile();
        cout << "Updata Book File Success" << endl;
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

void Book::validDate() {
    int inputYear = stoi(sOriginDate.substr(0, 4));
    int inputMonth = stoi(sOriginDate.substr(5, 2));
    int inputDay = stoi(sOriginDate.substr(8, 2));

    if (inputMonth < 1 || inputMonth > 12)
        throw WrongRuleArgumentException(this->sOriginDate, "존재하지 않는 달(month)입니다.");
    if (inputMonth == 2) {
        if ((inputYear % 4 == 0 && inputYear % 100 != 0) || (inputYear % 100 == 0 && inputYear % 400 == 0)) {
            if (inputDay < 0 || inputDay > 29)
                throw WrongRuleArgumentException(this->sOriginDate, "존재하지 않는 일(day)입니다.");
        }
        else {
            if (inputDay < 0 || inputDay > 28)
                throw WrongRuleArgumentException(this->sOriginDate, "존재하지 않는 일(day)입니다.");
        }
    }
    else if (inputMonth == 4 || inputMonth == 6 || inputMonth == 9 || inputMonth == 11) {
        if (inputDay < 0 || inputDay > 30) throw WrongRuleArgumentException(this->sOriginDate, "존재하지 않는 일(day)입니다.");
    }
    else {
        if (inputDay < 0 || inputDay > 31) throw WrongRuleArgumentException(this->sOriginDate, "존재하지 않는 일(day)입니다.");
    }


    time_t now;
    time(&now);

    time_t inputDate;
    struct tm user_stime;

    user_stime.tm_year = inputYear - 1900;   // 주의 :년도는 1900년부터 시작
    user_stime.tm_mon = inputMonth - 1;      // 주의 :월은 0부터 시작
    user_stime.tm_mday = inputDay;
    user_stime.tm_hour = startHour;
    user_stime.tm_min = startMin;
    user_stime.tm_sec = 0;
    user_stime.tm_isdst = 0;              // 썸머 타임 사용 안함

    inputDate = mktime(&user_stime);

    double d_diff = difftime(inputDate, now);
    int tm_day = d_diff / (60 * 60 * 24);

    if (tm_day >= 90)
        throw WrongRuleArgumentException(this->sOriginDate, "최대 90일 후까지 예약할 수 있습니다.");
    if (d_diff < 0)
        throw WrongRuleArgumentException(this->sOriginDate, "입력 인자 \"시간\"이 의미규칙을 만족하지 못합니다.");

}

void Book::validRoomNumber() {
    if (this->iRoomNumber <= 0 || this->iRoomNumber > 9)
        throw WrongRuleArgumentException(this->sRoomNumber, "스터디룸 번호는 1부터 9까지 존재합니다.");
}

void Book::validPeopleNumber() {
    vector<string> data = File::getMetaData();
    int i = stoi(data[3 + iRoomNumber]);
    if (this->peopleNum < 1) {
        throw WrongRuleArgumentException(this->sRoomNumber, "예약 인원수는 1보다 커야합니다.");
    }
    if (this->peopleNum > i)
        throw WrongRuleArgumentException(this->sRoomNumber, "스터디룸의 최대 예약 가능 인원수를 초과하였습니다.");
}