#include "SearchByName.h"

void SearchByName::search(string name)
{
	vector<vector<string>> target = File::getAllUsers();
	vector<int> location; //�ش��ϴ� ������� �� ����


	for (int i = 0; i < target.size(); i++) {
		if (target[i][1].compare(name) == 0) {
			location.push_back(i);
		}
	}

	cout << "�̸�	��ȭ��ȣ" << endl;
	for(int i=0;i<location.size();i++){
		for (int j = 1;j<3;j++) {
			cout << target[location.at(i)][j]<< "\t";
		}
		cout << endl;
	}
}


