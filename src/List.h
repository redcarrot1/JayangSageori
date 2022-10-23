#pragma once

#include "File.h"
#include "User.h"

class List {
public:
    List() = delete;

    static void excuteList(string sdate);

    static void validDate(string date);
};
