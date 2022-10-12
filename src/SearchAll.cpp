#include "SearchAll.h"

void SearchAll::search()
{
	//파일에 저장돼있는 라인은 이미 표준 형식이므로 추가적인 변환 필요 X only 파싱만 필요함
	vector<vector<string>> output = File::getAllUsers();


	cout << "이름	전화번호" << endl;
	for(int i=0;i<output.size();i++){
		for (int j = 1;j<3;j++) {
			cout << output[i][j] << "\t";
		}
		cout << endl;
	}
}