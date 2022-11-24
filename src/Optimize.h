#pragma once

#include <vector>
#include <string>

using std::string, std::vector;

class Optimize {
private:
    static int convertTimeToIndex(string &time);

    static bool go(vector<vector<string>> &data, int reserveId, int roomId, int peopleNum, int timeIndex);

public:
    Optimize() = delete;

    static vector<vector<string>> optimize(string date, string startTime, string endTime, string roomId);
};
