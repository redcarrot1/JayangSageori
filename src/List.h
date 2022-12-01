#pragma once

#include "File.h"
#include "User.h"
#include "Optimize.h"

class List {
public:
    List() = delete;

    static void excuteList(string peopleNum, string sdate);
    static void validDate(string date);
    static void validPeopleNumber(string peopleNum);

private:
};
