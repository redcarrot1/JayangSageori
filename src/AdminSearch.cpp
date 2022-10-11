#include "AdminSearch.h"
//�Ƹ��� ���ο��� ������?
AdminSearch::AdminSearch(vector<string> input)//input�� �̹� ǥ�� �������� �Ľ��ؼ� ����
{
	instruction = input;
}


void AdminSearch::play() //��ɾ� ���� ���� ��
{
	
	int flag = 0; // 0: ���� ����	1: ���� 1��(�̸�)	2: ���� 1��(��ȭ��ȣ) 3: ���� 2��(�̸�, ��ȭ��ȣ)
				  
	//instruction�� �Ľ� & standard �ؼ� ���� ����� �Է�
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
		SearchByName().search(instruction.at(1)); // ��ɾ� �Ľ��� ������ 1�� index
		break;
	case 2:
		SearchByPhoneNum().search(instruction.back(), ""); // ��ɾ� �Ľ��� ������ 1�� index
		break;
	case 3:
		SearchByPhoneNum().search(instruction.at(2), instruction.at(1)); //��ɾ� �Ľ��� ������ 2, 1�� index
		break;

	}
}