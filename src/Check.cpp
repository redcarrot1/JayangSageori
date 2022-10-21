#include "Check.h"

void Check::showReservationList(string userId) {
    vector<vector<string>> userData = File::getUserData(std::move(userId));
    size_t row = userData.size();
    size_t col = userData[0].size();

    //getUserData에서 데이터를 읽어오지 못해서 발생하는 에러입니다.
    /* Test Code
    cout << "row : " << row << endl;
    cout << "col : " << col << endl;
     */

    // 출력문은 작동 확인되면 수정하겠습니다.
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << userData[i][j] << "\t";
        }
        cout << endl;
    }
}

void Check::excuteCheck(string userId) {
    cout << "예약번호\t스터디룸 번호\t날짜\t시작시간\t종료시간" << endl;
    showReservationList(std::move(userId));
};

