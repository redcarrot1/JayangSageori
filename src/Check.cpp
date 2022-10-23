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
    cout << "�����ȣ  ��¥\t     ����ð� ���۽ð�  ���͵�� ��ȣ" << endl;
    showReservationList(std::move(userId));
};

