#include "Optimize.h"
#include "File.h"
#include <tuple>

using namespace std;

vector<vector<string>> Optimize::optimize(string date, string startTime, string endTime, string roomIdStr) {
    // ��ȯ: ����ȭ �Ϸ� ���� ���͵� �� ���� ��Ȳ. (���� �����ϰ��� �ϴ� ������ �� ���� �ʽ��ϴ�.)
    vector<vector<string>> data = File::getBooking(date);
    int roomId = stoi(roomIdStr);

    int startTimeIndex = convertTimeToIndex(startTime), endTimeIndex = convertTimeToIndex(endTime);
    for (int i = startTimeIndex; i < endTimeIndex; i++) {
        if (data[roomId][i] != "0") {
            if (!go(data, stoi(data[roomId][i]), roomId,
                    stoi(File::getReserNum(data[roomId][i])), i))
                return {{}}; // ����
        }
    }
    return data; // ����
}

bool Optimize::go(vector<vector<string>> &data, int reserveId, int roomId, int peopleNum, int timeIndex) {
    // [roomId][timeIndex] �� �����ϴ� ������ �ٸ� ���͵������ �̵����Ѿ� ��
    vector<tuple<int, int, int>> possibleStudyRoom; // <���� ��ȣ, roomId, ���� �ο� - ���� �ο�>
    for (int id = 1; id < 10; id++) {
        if (id == roomId) continue;

        int limitNum = stoi(File::getRoomCapacity(to_string(id)));
        if (limitNum < peopleNum) continue;

        if (data[id][timeIndex] == "0") possibleStudyRoom.push_back({0, id, limitNum - peopleNum});
        else if (stoi(File::getReserNum(data[id][timeIndex])) < peopleNum) {
            possibleStudyRoom.push_back({stoi(data[id][timeIndex]), id, limitNum - peopleNum});
        }
    }

    if (possibleStudyRoom.empty()) return false; // ����. �ش� ������ ���͵���� �ű� �� �ִ� ���ɼ��� ����

    sort(possibleStudyRoom.begin(), possibleStudyRoom.end(),
         [](tuple<int, int, int> p1, tuple<int, int, int> p2) {
             int reserveId1, roomId1, diff1, reserveId2, roomId2, diff2;
             tie(reserveId1, roomId1, diff1) = p1;
             tie(reserveId2, roomId2, diff2) = p2;

             // �켱 ���� 1. ���� ������ �Ǿ����� ���� ��
             if (reserveId1 == 0 || reserveId2 == 0) return reserveId1 < reserveId2;

             // �켱 ���� 2. (���� �ο� - ���� �ο�)�� ���� ��
             if (diff1 != diff2) return diff1 < diff2;

             // �켱 ���� 3. ���͵� �� ��ȣ�� ���� ��
             return roomId1 < roomId2;
         });


    int movingReserveId = get<0>(possibleStudyRoom[0]), movingRoomId = get<1>(possibleStudyRoom[0]);
    data[movingRoomId][timeIndex] = to_string(reserveId);
    if (movingReserveId == 0) return true;
    else
        return go(data, movingReserveId, movingRoomId,
                  stoi(File::getReserNum(to_string(movingReserveId))), timeIndex);
}

int Optimize::convertTimeToIndex(string &time) {
    // 09:00 -> 0, 10:00 -> 2, 11:00 -> 4, ... 19:00 -> 20
    int ret = (stoi(time.substr(0, 2)) - 9) * 2;
    return time[3] == '0' ? ret : ret + 1;
}
