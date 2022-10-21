#pragma once

#include <string>
#include "File.h"
#include "User.h"

// 사용자의 예약된 스터디룸을 나열 우선 순위에 맞춰 나열합니다.
class Check {
private:
    static void showReservationList(string userId);

public:
    static void excuteCheck(string userId);
};

