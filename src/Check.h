#pragma once

#include "File.h"
#include "User.h"
#include <string>

// ������� ����� ���͵���� ���� �켱 ������ ���� �����մϴ�.
class Check {
public:
    Check(string userid);

    void excuteCheck();

private:
    void showReservationList();

    vector<vector<string>> userData;
};

