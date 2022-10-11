#pragma once
#include "File.h"
#include "User.h"
#include <string>

// 사용자의 예약된 스터디룸을 나열 우선 순위에 맞춰 나열합니다.
class Check
{
public:
	Check() = delete;
	Check(string userid);
	void showReservationList();
	void excuteCheck();
private:
	string userid;
	vector<vector<string>> userData;
};

