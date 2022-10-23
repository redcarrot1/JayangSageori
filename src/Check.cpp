#include "Check.h"

void Check::showReservationList(string userId) {
    vector<vector<string>> userData = File::getUserData(std::move(userId));
    size_t row = userData.size();
    size_t col = 0;
    if (row != 0) col = userData[0].size();

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << userData[i][j] << "\t";
        }
        cout << endl;
    }
}

void Check::excuteCheck(string userId) {
    cout << "예약번호  날짜\t     종료시간 시작시간  스터디룸 번호" << endl;
    showReservationList(std::move(userId));
};

