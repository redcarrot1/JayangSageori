#include "Check.h"

Check::Check(string userid) {
    this->userData = File::getUserData(userid);
}

void Check::showReservationList() {
    int row = userData.size();
    int col = userData[0].size();

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

void Check::excuteCheck() {
    cout << "�����ȣ\t���͵�� ��ȣ\t��¥\t���۽ð�\t����ð�" << endl;
    showReservationList();
};

