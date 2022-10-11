#include "AdminSearch.h"
//아마도 메인에서 돌릴듯?
AdminSearch::AdminSearch(vector<string> input)//input은 이미 표준 형식으로 파싱해서 들어옴
{
	instruction = input;
}


void AdminSearch::play() //명령어 숫자 문자 순
{
	
	int flag = 0; // 0: 인자 없음	1: 인자 1개(이름)	2: 인자 1개(전화번호) 3: 인자 2개(이름, 전화번호)
				  
	//instruction은 파싱 & standard 해서 들어온 사용자 입력
	if (instruction.size() == 2) {
		if (instruction.at(1)[0] >= 'a' && instruction.at(1)[0] <= 'z') {
			flag = 1;
		}
		else {
			flag = 2;
		}
	}
	else if (instruction.size() == 3) {
			flag = 3;
	}
	switch (flag) {
	case 0:
		SearchAll().search();
		break;
	case 1:
		cout << 1;
		SearchByName().search(instruction.at(1)); // 명령어 파싱한 라인의 1번 index
		break;
	case 2:
		SearchByPhoneNum().search(instruction.back(), ""); // 명령어 파싱한 라인의 1번 index
		break;
	case 3:
		SearchByPhoneNum().search(instruction.at(2), instruction.at(1)); //명령어 파싱한 라인의 2, 1번 index
		break;

	}
}