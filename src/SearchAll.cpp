#include "SearchAll.h"

void SearchAll::search()
{
	//���Ͽ� ������ִ� ������ �̹� ǥ�� �����̹Ƿ� �߰����� ��ȯ �ʿ� X only �Ľ̸� �ʿ���
	vector<vector<string>> output = File::getAllUsers();


	cout << "�̸�	��ȭ��ȣ" << endl;
	for(int i=0;i<output.size();i++){
		for (int j = 1;j<3;j++) {
			cout << output[i][j] << "\t";
		}
		cout << endl;
	}
}