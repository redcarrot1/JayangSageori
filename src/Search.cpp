#include "Search.h"

void Search::searchAll() {
    //UserData : userID, Name, phoneNum
    vector<vector<string>> target = File::getAllUsers();

    cout << "이름\t전화번호" << endl;
    for (auto &userData: target) {
        cout << userData[1] << "\t" << userData[2] << endl;
    }
}

void Search::searchByName(const string& name) {
    //UserData : userID, Name, phoneNum
    vector<vector<string>> target = File::getAllUsers();

    cout << "이름\t전화번호" << endl;
    for (auto &userData: target) {
        if (userData[1] == name) {
            cout << userData[1] << "\t" << userData[2] << endl;
        }
    }
}


void Search::searchByNameAndPhone(const string& name, const string& phone) {
    vector<vector<string>> info = File::getAllUsers(); //userID, Name, phoneNum
    int location = -1, change; //해당하는 사용자의 행 저장
    string id; //사용자 아이디 저장

    try {
        for (int i = 0; i < info.size(); i++) {
            if (info[i][2] == phone) {
                location = i;
                id = info[i][0];
                break;
            }
        }
        if (location == -1) {
            throw WrongRuleArgumentException("전화번호", "해당 전화번호와 일치하는 사용자를 찾을 수 없습니다.");
        }

        if (name != "") {
            if (info[location][1] != name) {
                throw WrongRuleArgumentException("전화번호와 이름", "해당 전화번호와 일치하는 사용자 이름이 다릅니다.");
            }
        }

        vector<vector<string>> userInfo = File::getUserData(id); // 예약번호 예약날짜 시작시각 종료시각 방번호
        time_t now, reserveat;
        time(&now);

        change = 0;
        {// TODO 과거인지 판단하는 곳
            for (int i = 0; i < userInfo.size(); i++) {
                /*
                tm reser(0, stoi(userInfo[i][2].substr(3, 2)), stoi(userInfo[i][2].substr(0, 2)),
                         stoi(userInfo[i][1].substr(8, 2)), stoi(userInfo[i][1].substr(5, 2)) - 1,
                         stoi(userInfo[i][1].substr(0, 4)) - 1900);
                if (difftime(now, mktime(&reser)) < 0) {
                    change = i;
                    break;
                }
                 */
            }

        }


        cout << "이름\t전화번호" << endl;
        cout << info[location][1] << "\t" << info[location][2] << endl << endl;
        cout << "예약 현황" << endl << endl;
        cout << "예약 날짜" << "\t" << "이용 시간" << "\t" << "룸 번호" << "\t	" << "예약 번호" << endl << endl;
        for (int i = change; i < userInfo.size(); i++) {
            cout << userInfo[i][1] << " | " << userInfo[i][2] << " ~ " << userInfo[i][3] << " | \t" << userInfo[i][4]
                 << "\t|\t" << userInfo[i][0] << endl << endl;
        }

        cout << endl << "이용 현황" << endl << endl;
        cout << "예약 날짜" << "\t" << "이용 시간" << "\t" << "룸 번호" << "\t	" << "예약 번호" << endl << endl;
        for (int i = 0; i < change; i++) {
            cout << userInfo[i][1] << " | " << userInfo[i][2] << " ~ " << userInfo[i][3] << " | \t" << userInfo[i][4]
                 << "\t|\t" << userInfo[i][0] << endl << endl;
        }
    }
    catch (exception &e) {
        exceptionMannager(e);
    }

}
