#include "Check.h"

Check::Check(string userid) {
	this->userid = userid;
	this->userData = File::getUserData(this->userid);
}

void Check::showReservationList() {
	int row = userData.size();
	int col = userData[0].size();
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << userData[i][j] << " ";
		}
		cout << endl;
	}
};