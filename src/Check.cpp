#include "Check.h"

void Check::showReservationList(string userId) {
    vector<vector<string>> userData = File::getUserData(std::move(userId));
    size_t row = userData.size();
    size_t col = 0;
    if (row != 0) col = userData[0].size();

    for (int i = 0; i < row; i++) {
        int roomCount = (userData[i].size() - 2) / 3;

        int inputYear = stoi(userData[i][1].substr(0, 4));
        int inputMonth = stoi(userData[i][1].substr(5, 2));
        int inputDay = stoi(userData[i][1].substr(8, 2));
        int startHour = stoi(userData[i][2].substr(0, 2));
        int startMin = stoi(userData[i][2].substr(3));

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

        if (difftime(inputDate, now) < 0) continue;
        
        string date = userData[i][1];
        cout << left << setw(8) << userData[i][0]<<"\t";
        for (int j = 0; j < (userData[i].size() - 2) / 3; j++) {
            if (j != 0)  cout << "\t\t";
            cout << date << "\t" << File::getReserNum(userData[i][0]) << "명" << "\t";
            cout << userData[i][4 + 3 * j] << "번 스터디룸\t";
            cout << userData[i][2+3*j] << "\t\t";
            cout << userData[i][3 + 3 * j] << endl;
        }
    }
}

void Check::excuteCheck(string userId) {
    cout << "예약번호\t예약날짜\t인원\t스터디룸 번호\t시작시간\t종료시간" << endl;
    showReservationList(std::move(userId));
};

