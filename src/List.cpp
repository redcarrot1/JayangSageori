#include "List.h"

List::List(string sdate, string id)
{
	this->sdate = sdate;
	this->id = id;
	sdate.erase(remove(sdate.begin(), sdate.end(), '-'),sdate.end());
	cout << sdate << endl; //�׽�Ʈ �ڵ�
	this->sdate = sdate;
	cout << this->sdate; //�׽�Ʈ �ڵ�
	this->fileData = File::getBooking(this->sdate);
}

void List::excuteList()
{
	int row = fileData.size();
	cout << row << endl; //�׽�Ʈ �ڵ�
	int col = fileData[0].size();
	cout << col << endl; //�׽�Ʈ �ڵ�

	//��¹��� �׽�Ʈ �� �����ϰڽ��ϴ�.
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << fileData[i][col] << "\t";
		}
		cout << endl;
	}
}

