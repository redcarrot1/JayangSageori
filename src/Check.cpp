#include "Check.h"

Check::Check(string userid) {
	this->userid = userid;
	this->userData = File::getUserData(this->userid);
	cout << userData.size();
}

void Check::showReservationList() {
	int row = userData.size();
	cout << row << endl;
	//getUserData���� �����͸� �о���� ���ؼ� �߻��ϴ� �����Դϴ�.
	int col = userData[0].size();
	// ��¹��� �۵� Ȯ�εǸ� �����ϰڽ��ϴ�.
	cout << col << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << userData[i][j] << " ";
		}
		cout << endl;
	}
}
void Check::excuteCheck()
{
	cout << "�����ȣ\t���͵�� ��ȣ\t��¥\t���۽ð�\t����ð�" << endl;
	showReservationList();
}
;

