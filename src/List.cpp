#include "List.h"

List::List(string sdate, string id)
{
	this->sdate = sdate;
	this->id = id;
	this->sdate.erase(remove(sdate.begin(), sdate.end(), '-'));
	this->fileData = File::getBooking(this->sdate);

}

void List::excuteList()
{
	int row = fileData.size();
	int col = fileData[0].size();
	//��¹��� �׽�Ʈ �� �����ϰڽ��ϴ�.
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << fileData[i][col] << "\t";
		}
		cout << endl;
	}
}

