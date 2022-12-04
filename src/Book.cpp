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
    vector<vector<string>> beforeData = File::getBooking(this->sdate);
    bookFileData = File::getBooking(sdate);
    for (int i = sIndex; i < eIndex; i++) {
        string k = File::getReserNum(bookFileData[iRoomNumber][i]);
        int reservedNum = stoi(k);
        if (reservedNum > peopleNum) {
            throw WrongRuleArgumentException(sPeopleNum, "���� ���� �ο����� �� Ŀ�� ������ �����մϴ�."); 
        } }
    if (stoi(File::getMetaData()[3 + stoi(sRoomNumber)]) >= stoi(sPeopleNum)) {
        bookFileData = Optimize::optimize(this->sdate, this->sUseStartTime, this->sUseEndTime, this->sRoomNumber);

    }
    bool flag = false;
    vector<string> changed_id;
    if (checkReservation()) {
        for (int i = 0; i < bookFileData.size(); i++)
            for (int j = 0; j < bookFileData[i].size(); j++)
                if (bookFileData[i][j] != beforeData[i][j]) {
                    changed_id.push_back(bookFileData[i][j]);
                    flag = true;
                }
    }

/*
signin park 010123456
book
book 20221205 6 0900 1100 2
book 20221205 6 0930 1000 3
*/
    if (flag) {
        vector<vector<string>> changed;//���� ��ȣ, ���� timeindex, ���� timeindex, ���ȣ
        for (int j = 0; j < beforeData[0].size(); j++) {
            for (int i = 1; i < beforeData.size(); i++) {
                if (find(changed_id.begin(), changed_id.end(), bookFileData[i][j]) != changed_id.end()) {//�ٲ������ Ȯ��
                    if (changed.size() == 0) {
                        vector<string> line;
                        line.push_back(bookFileData[i][j]);//���� ��ȣ               
                        line.push_back(this->sdate);//��¥
                        line.push_back(to_string(j));//���� timeIndex
                        line.push_back(to_string(j));//���� timeIndex
                        line.push_back(to_string(i));//���ȣ
                        changed.push_back(line);
                    }
                    else {
                        for (int k = 0; k < changed.size(); k++) {
                            if (changed[k][0] == bookFileData[i][j]) {//changed�� ���� ���� ��ȣ�ִ��� Ȯ��
                                if (changed[k][changed[k].size() - 2] == to_string(j - 1) && changed[k][changed[k].size() - 1] == to_string(i)) { //���� �ð��� ���� �� ������ ���� �ð� == ���� ������ ���� �ð�, ���� ��
                                    changed[k][changed[k].size() - 2] = to_string(j);
                                }
                                else {//���� �ٲ�� ���
                                    changed[k].push_back(to_string(j));//���� timeIndex
                                    changed[k].push_back(to_string(j));//���� timeindex
                                    changed[k].push_back(to_string(i));//���ȣ
                                }
                            }
                            else {
                                vector<string> line;
                                line.push_back(bookFileData[i][j]);//���� ��ȣ
                                line.push_back(this->sdate);//��¥
                                line.push_back(to_string(j));//���� timeIndex
                                line.push_back(to_string(j));//���� timeIndex
                                line.push_back(to_string(i));//���ȣ
                                changed.push_back(line);
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < changed.size(); i++) {
            changed[i][1].insert(4, "-");
            changed[i][1].insert(7, "-");
        }

        for (int k = 0; k < changed.size(); k++) {
            for (int i = 0; i < (changed[k].size() - 2) / 3; i++) {
                //start time index            
                int index = stoi(changed[k][2 + i * 3]);
                if (index/2 + 9 == 9) {//hour == 9
                    changed[k][2 + i * 3] = "0" + to_string(index / 2 + 9);//hour
                    cout << changed[k][2 + i * 3];
                    changed[k][2 + i * 3].append(":");//std
                    if (index % 2 == 0) changed[k][2 + i * 3].append("0");
                    changed[k][2 + i * 3].append(to_string(index % 2 * 30));//minute
                }
                else {
                    changed[k][2 + i * 3] = to_string(index / 2 + 9);//hour
                    changed[k][2 + i * 3].append(":");//std
                    if (index % 2 == 0) changed[k][2 + i * 3].append("0");
                    changed[k][2 + i * 3].append(to_string(index % 2 * 30));//minute
                }
                //end time index 
                index = stoi(changed[k][3 + i * 3]);
                if ((index + 1) / 2 == 9) {//hour == 9
                    changed[k][3 + i * 3] = "0"+to_string((index + 1) / 2 + 9); //hour
                    changed[k][3 + i * 3].append(":");//std
                    if ((index + 1) % 2 == 0) changed[k][3 + i * 3].append("0");
                    changed[k][3 + i * 3].append(to_string((index + 1) % 2 * 30));//minute
                }
                else {
                    changed[k][3 + i * 3] = to_string((index + 1) / 2 + 9);//hour
                    changed[k][3 + i * 3].append(":");//std
                    if ((index + 1) % 2 == 0) changed[k][3 + i * 3].append("0");
                    changed[k][3 + i * 3].append(to_string((index + 1) % 2 * 30));//minute

                }
            }
        }
    }
    userData = File::getUserData(userId);
}


bool Book::checkReservation() {
    // ����Ǿ��ִ��� Ȯ��
    if (bookFileData.size() == 1) {
        cout << "[����] " << sOriginDate << " " << sRoomNumber << "�� ���͵�� " << this->sUseStartTime << " ~ "
            << this->sUseEndTime << "�� ���� �Ұ����� �����Դϴ�." << endl;
        return false;
    }

    return true;
}

bool comp(vector<string>& v1, vector<string>& v2) {
    // 1. ���� ��¥ ��
    string date1 = v1[1], date2 = v2[1];
    date1.erase(remove(date1.begin(), date1.end(), '-'), date1.end());
    date2.erase(remove(date2.begin(), date2.end(), '-'), date2.end());

    if (date1 > date2) return false;
    else if (date1 < date2) return true;


    // 2. ���� �ð� ��
    string start1 = v1[2], start2 = v2[2];
    start1.erase(remove(start1.begin(), start1.end(), ':'), start1.end());
    start2.erase(remove(start2.begin(), start2.end(), ':'), start2.end());

    if (start1 > start2) return false;
    else if (start1 < start2) return true;


    // 3. ���� �ð� ��
    string end1 = v1[v1.size()-2], end2 = v2[v2.size()-2];
    end1.erase(remove(end1.begin(), end1.end(), ':'), end1.end());
    end2.erase(remove(end2.begin(), end2.end(), ':'), end2.end());

    if (end1 > end2) return false;
    else if (end1 < end2) return true;


    // 4. �� ��ȣ ��

    string num1 = v1.back(), num2 = v2.back();
    if (stoi(num1) > stoi(num2)) return false;
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
    cout << userData.size()<<userData[0][1]<<userData[0][2];
    if (userData.size() != 2)
      sort(userData.begin(), userData.end()-1, comp); 
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
        cout << this->sOriginDate << " " << this->sRoomNumber << "�� ���͵�� " << this->sUseStartTime << " ~ "
            << this->sUseEndTime << " �� ���� ����Ǿ����ϴ�." << endl;
    }
}

void Book::validTime() {
    if (this->startHour < 9 || this->startHour > 19)
        throw WrongRuleArgumentException(this->sUseStartTime, "���͵���� 09:00 ~ 20:00���� ��մϴ�.");

    if (this->endHour < 9 || this->endHour > 20 || (this->endHour == 20 && this->endMin == 30)) {
        throw WrongRuleArgumentException(this->sUseEndTime, "���͵���� 09:00 ~ 20:00���� ��մϴ�.");
    }

    if (this->startHour == this->endHour) {
        if (this->startMin >= this->endMin)
            throw WrongRuleArgumentException(this->sUseEndTime, "���� ������ �ð��� ���� �ð� ���Ŀ��� �մϴ�.");
    }
    else if (this->startHour > this->endHour)
        throw WrongRuleArgumentException(this->sUseEndTime, "���� ������ �ð��� ���� �ð� ���Ŀ��� �մϴ�.");
}

void Book::validDate() {
    int inputYear = stoi(sOriginDate.substr(0, 4));
    int inputMonth = stoi(sOriginDate.substr(5, 2));
    int inputDay = stoi(sOriginDate.substr(8, 2));

    if (inputMonth < 1 || inputMonth > 12)
        throw WrongRuleArgumentException(this->sOriginDate, "�������� �ʴ� ��(month)�Դϴ�.");
    if (inputMonth == 2) {
        if ((inputYear % 4 == 0 && inputYear % 100 != 0) || (inputYear % 100 == 0 && inputYear % 400 == 0)) {
            if (inputDay < 0 || inputDay > 29)
                throw WrongRuleArgumentException(this->sOriginDate, "�������� �ʴ� ��(day)�Դϴ�.");
        }
        else {
            if (inputDay < 0 || inputDay > 28)
                throw WrongRuleArgumentException(this->sOriginDate, "�������� �ʴ� ��(day)�Դϴ�.");
        }
    }
    else if (inputMonth == 4 || inputMonth == 6 || inputMonth == 9 || inputMonth == 11) {
        if (inputDay < 0 || inputDay > 30) throw WrongRuleArgumentException(this->sOriginDate, "�������� �ʴ� ��(day)�Դϴ�.");
    }
    else {
        if (inputDay < 0 || inputDay > 31) throw WrongRuleArgumentException(this->sOriginDate, "�������� �ʴ� ��(day)�Դϴ�.");
    }


    time_t now;
    time(&now);

    time_t inputDate;
    struct tm user_stime;

    user_stime.tm_year = inputYear - 1900;   // ���� :�⵵�� 1900����� ����
    user_stime.tm_mon = inputMonth - 1;      // ���� :���� 0���� ����
    user_stime.tm_mday = inputDay;
    user_stime.tm_hour = startHour;
    user_stime.tm_min = startMin;
    user_stime.tm_sec = 0;
    user_stime.tm_isdst = 0;              // ��� Ÿ�� ��� ����

    inputDate = mktime(&user_stime);

    double d_diff = difftime(inputDate, now);
    int tm_day = d_diff / (60 * 60 * 24);

    if (tm_day >= 90)
        throw WrongRuleArgumentException(this->sOriginDate, "�ִ� 90�� �ı��� ������ �� �ֽ��ϴ�.");
    if (d_diff < 0)
        throw WrongRuleArgumentException(this->sOriginDate, "�Է� ���� \"�ð�\"�� �ṉ̀�Ģ�� �������� ���մϴ�.");

}

void Book::validRoomNumber() {
    if (this->iRoomNumber <= 0 || this->iRoomNumber > 9)
        throw WrongRuleArgumentException(this->sRoomNumber, "���͵�� ��ȣ�� 1���� 9���� �����մϴ�.");
}

void Book::validPeopleNumber() {
    vector<string> data = File::getMetaData();
    int i = stoi(data[3 + iRoomNumber]);
    if (this->peopleNum < 1) {
        throw WrongRuleArgumentException(this->sRoomNumber, "���� �ο����� 1���� Ŀ���մϴ�.");
    }
    if (this->peopleNum > i)
        throw WrongRuleArgumentException(this->sRoomNumber, "���͵���� �ִ� ���� ���� �ο����� �ʰ��Ͽ����ϴ�.");
}