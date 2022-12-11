#include "List.h"

void List::excuteList(string peopleNum, string date) {
    validDate(date);
    validPeopleNumber(peopleNum);
    vector<vector<string>> fileData = File::getBooking(date);

    cout << date << " ���͵�� �����Դϴ�." << endl;
    cout << left << setw(6) << "���͵�� ";
    for (int i = 9; i < 20; ++i) {
        string hour = to_string(i);
        string time;
        if (hour.length() == 1) time = "0" + hour + ":00";
        else time = hour + ":00";
        cout << left << setw(6) << time;

        if (hour.length() == 1) time = "0" + hour + ":30";
        else time = hour + ":30";
        cout << left << setw(6) << time;
    }

    cout << endl;
    for (int i = 1; i < 10; i++) {
        cout << i << " (" << File::getRoomCapacity(to_string(i)) << "�ν�)";
        for (int j = 0; j < 22; j++) {
            vector<vector<string>> newfileData = File::getBooking(date);
            string hour = to_string(j / 2 + 9);
            int min = j % 2;
            string minute;
            string startTime;
            string endTime;
            if (hour.length() == 1) hour = "0" + hour;
            if (min == 0) minute = "00";
            else minute = "30";

            startTime = hour + ":" + minute;

            if (min == 0) minute = "30";
            else {
                minute = "00";
                hour = to_string(j / 2 + 10);
            }

            if (hour.length() == 1) hour = "0" + hour;

            endTime = hour + ":" + minute;
            if ((stoi(File::getMetaData()[3 + i]) >= stoi(peopleNum)) && (stoi(File::getReserNum(newfileData[i][j])) <
                                                                          stoi(peopleNum))) {  // �����ο����� ������, ������ ������ �� ������ �ο������� �� �ο����� �� ���ƾ� optimizer�� ������ �� �ִ�.
                if (Optimize::optimize(date, startTime, endTime, to_string(i)).size() > 1) {
                    cout << left << setw(7) << " ���� ";
                }
                else cout << left << setw(7) << " X ";
            }
            else cout << left << setw(7) << " X ";
        }
        cout << endl;
    }
}


void List::validDate(string date) {
    int inputYear = stoi(date.substr(0, 4));
    int inputMonth = stoi(date.substr(5, 2));
    int inputDay = stoi(date.substr(8, 2));

    if (inputMonth < 1 || inputMonth > 12)
        throw WrongRuleArgumentException(date, "�������� �ʴ� ��(month)�Դϴ�.");
    if (inputMonth == 2) {
        if ((inputYear % 4 == 0 && inputYear % 100 != 0) || (inputYear % 100 == 0 && inputYear % 400 == 0)) {
            if (inputDay < 0 || inputDay > 29)
                throw WrongRuleArgumentException(date, "�������� �ʴ� ��(day)�Դϴ�.");
        }
        else {
            if (inputDay < 0 || inputDay > 28)
                throw WrongRuleArgumentException(date, "�������� �ʴ� ��(day)�Դϴ�.");
        }
    }
    else if (inputMonth == 4 || inputMonth == 6 || inputMonth == 9 || inputMonth == 11) {
        if (inputDay < 0 || inputDay > 30) throw WrongRuleArgumentException(date, "�������� �ʴ� ��(day)�Դϴ�.");
    }
    else {
        if (inputDay < 0 || inputDay > 31) throw WrongRuleArgumentException(date, "�������� �ʴ� ��(day)�Դϴ�.");
    }

    time_t now;
    time(&now);

    time_t inputDate;
    struct tm user_stime;

    user_stime.tm_year = inputYear - 1900;   // ���� :�⵵�� 1900����� ����
    user_stime.tm_mon = inputMonth - 1;      // ���� :���� 0���� ����
    user_stime.tm_mday = inputDay + 1;
    user_stime.tm_hour = 0;
    user_stime.tm_min = 0;
    user_stime.tm_sec = 0;
    user_stime.tm_isdst = 0;              // ��� Ÿ�� ��� ����

    inputDate = mktime(&user_stime);

    double d_diff = difftime(inputDate, now);
    int tm_day = d_diff / (60 * 60 * 24);

    if (tm_day >= 90)
        throw WrongRuleArgumentException(date, "�ִ� 90�� �ı��� Ȯ���� �� �ֽ��ϴ�.");
    if (d_diff < 0)
        throw WrongRuleArgumentException(date, "���� ��¥�� ��ȸ�� �� �����ϴ�.");

}

void List::validPeopleNumber(string peopleNum) {
    vector<string> data = File::getMetaData();
    if (stoi(peopleNum) < 1) {
        throw WrongRuleArgumentException(peopleNum, "���� �ο����� 0���� Ŀ���մϴ�.");
    }
}