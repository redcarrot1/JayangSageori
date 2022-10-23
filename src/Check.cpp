#include "Check.h"

void Check::showReservationList(string userId) {
    vector<vector<string>> userData = File::getUserData(std::move(userId));
    size_t row = userData.size();
    size_t col = 0;
    if (row != 0) col = userData[0].size();

    for (int i = 0; i < row; i++) {
        int inputYear = stoi(userData[i][1].substr(0, 4));
        int inputMonth = stoi(userData[i][1].substr(5, 2));
        int inputDay = stoi(userData[i][1].substr(8, 2));

        time_t now;
        time(&now);

        time_t inputDate;
        struct tm user_stime;

        user_stime.tm_year = inputYear - 1900;   // ���� :�⵵�� 1900����� ����
        user_stime.tm_mon = inputMonth - 1;      // ���� :���� 0���� ����
        user_stime.tm_mday = inputDay;
        user_stime.tm_hour = 0;
        user_stime.tm_min = 0;
        user_stime.tm_sec = 0;
        user_stime.tm_isdst = 0;              // ��� Ÿ�� ��� ����

        inputDate = mktime(&user_stime);

        if (difftime(inputDate, now) < 0) continue;

        cout << left << setw(8) << userData[i][0];
        cout << userData[i][1] << "  ";
        cout << userData[i][4] << "�� ���͵��    ";
        cout << userData[i][2] << "     ";
        cout << userData[i][3];
        cout << endl;
    }
}

void Check::excuteCheck(string userId) {
    cout << "�����ȣ    ���೯¥    ���͵�� ��ȣ    ���۽ð�    ����ð�" << endl;
    showReservationList(std::move(userId));
};

