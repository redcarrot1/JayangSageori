#pragma once

#include <string>
#include "File.h"
#include "User.h"

// ������� ����� ���͵���� ���� �켱 ������ ���� �����մϴ�.
class Check {
private:
    static void showReservationList(string userId);

public:
    static void excuteCheck(string userId);
};

