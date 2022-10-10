#include "List.h"

List::List(string sdate, string id)
{
	this->sdate = sdate;
	this->id = id;
	sdate.erase(remove(sdate.begin(), sdate.end(), '-'),sdate.end());
	cout << sdate << endl; //테스트 코드
	this->sdate = sdate;
	cout << this->sdate; //테스트 코드
	this->fileData = File::getBooking(this->sdate);
}

void List::excuteList()
{
	int row = fileData.size();
	cout << row << endl; //테스트 코드
	int col = fileData[0].size();
	cout << col << endl; //테스트 코드

	//출력문은 테스트 후 수정하겠습니다.
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << fileData[i][col] << "\t";
		}
		cout << endl;
	}
}

