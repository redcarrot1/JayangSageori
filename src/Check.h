#pragma once
#include "File.h"
#include "User.h"
#include <string>

// ������� ����� ���͵���� ���� �켱 ������ ���� �����մϴ�.
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

