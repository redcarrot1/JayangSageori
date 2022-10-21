#include "Check.h"

void Check::showReservationList(string userId) {
    vector<vector<string>> userData = File::getUserData(std::move(userId));
    size_t row = userData.size();
    size_t col = userData[0].size();

    //getUserData���� �����͸� �о���� ���ؼ� �߻��ϴ� �����Դϴ�.
    /* Test Code
    cout << "row : " << row << endl;
    cout << "col : " << col << endl;
     */

    // ��¹��� �۵� Ȯ�εǸ� �����ϰڽ��ϴ�.
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << userData[i][j] << "\t";
        }
        cout << endl;
    }
}

void Check::excuteCheck(string userId) {
    cout << "�����ȣ\t���͵�� ��ȣ\t��¥\t���۽ð�\t����ð�" << endl;
    showReservationList(std::move(userId));
};

