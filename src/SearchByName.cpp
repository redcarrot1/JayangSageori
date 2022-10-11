#include "SearchByName.h"

void SearchByName::search(string name)
{
	vector<vector<string>> target = File::getAllUsers();
	vector<int> location; //해당하는 사용자의 행 저장


	for (int i = 0; i < target.size(); i++) {
		if (target[i][1].compare(name) == 0) {
			location.push_back(i);
		}
	}

	cout << "이름	전화번호" << endl;
	for(int i=0;i<location.size();i++){
		for (int j = 1;j<3;j++) {
			cout << target[location.at(i)][j]<< "\t";
		}
		cout << endl;
	}
}


