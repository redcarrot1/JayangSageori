#include "Check.h"

Check::Check(string userid) {
	this->userid = userid;
	this->userData = File::getUserData(this->userid);
}

void Check::showReservationList() {
	int row = userData.size();
	cout << "row : " << row << endl;
	//getUserData���� �����͸� �о���� ���ؼ� �߻��ϴ� �����Դϴ�.
	int col = userData[0].size();
	cout << "col : " << col << endl;
	// ��¹��� �۵� Ȯ�εǸ� �����ϰڽ��ϴ�.
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << userData[i][j] << "\t";
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

