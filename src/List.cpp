#include "List.h"

void List::excuteList(string date) {
    vector<vector<string>> fileData = File::getBooking(date);

    cout << date << " 스터디룸 상태입니다." << endl;
    cout << left << setw(6) << "스터디룸 ";
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
    for (int i = 0; i < 9; i++) {
        cout << left << setw(7) << i + 1;
        for (int j = 0; j < 22; j++) {
            if (fileData[i][j] == "0") cout << left << setw(7) << " 가능 ";
            else cout << left << setw(7) << "X";
        }
        cout << endl;
    }

}

