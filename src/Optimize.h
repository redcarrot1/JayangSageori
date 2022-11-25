#pragma once

#include <vector>
#include <string>

using std::string, std::vector;

class Optimize {
private:
    static int convertTimeToIndex(string &time);


public:
    Optimize() = delete;
    static bool go(vector<vector<string>>& data, int reserveId, int roomId, int peopleNum, int timeIndex);

    static vector<vector<string>> optimize(string date, string startTime, string endTime, string roomId);
};
