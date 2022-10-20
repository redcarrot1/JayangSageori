#pragma once

#include "File.h"
#include "User.h"

class List {
public:
    List(string sdate, string id);

    void excuteList();

private:
    string sdate;
    string id;
    vector<vector<string>> fileData;
};
