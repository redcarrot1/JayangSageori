#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "SearchAll.h"
#include "SearchByName.h"
#include "SearchByPhoneNum.h"



using std::vector;
using std::string;


class AdminSearch
{
private:
	vector<string> instruction; //��ɾ �Էµ� line �ޱ�

public:
	AdminSearch(vector<string> input);
	void play(); //���� & ������ �ϴ� �Լ�
};

