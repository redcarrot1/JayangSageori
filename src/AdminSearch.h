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
	vector<string> instruction; //명령어가 입력된 line 받기

public:
	AdminSearch(vector<string> input);
	void play(); //검증 & 실행을 하는 함수
};

