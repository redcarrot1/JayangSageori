#include "Search.h"

void Search::searchAll() {
    //UserData : userID, Name, phoneNum
    vector<vector<string>> target = File::getAllUsers();

    cout << "�̸�\t��ȭ��ȣ" << endl;
    for (auto &userData: target) {
        cout << userData[1] << "\t" << userData[2] << endl;
    }
}

void Search::searchByName(const string &name) {
    //UserData : userID, Name, phoneNum
    vector<vector<string>> target = File::getAllUsers();

    cout << "�̸�\t\t\t��ȭ��ȣ" << endl;
    for (auto &userData: target) {
        if (userData[1] == name) {
            cout << userData[1] << "\t\t\t" << userData[2] << endl;
        }
    }
}


void Search::searchByNameAndPhone(const string &name, const string &phone) {
    vector<vector<string>> info = File::getAllUsers(); //userID, Name, phoneNum
    int location = -1, change; //�ش��ϴ� ������� �� ����
    string id; //����� ���̵� ����

    try {
        for (int i = 0; i < info.size(); i++) {
            if (info[i][2] == phone) {
                location = i;
                id = info[i][0];
                break;
            }
        }
        if (location == -1) {
            throw WrongRuleArgumentException("��ȭ��ȣ", "�ش� ��ȭ��ȣ�� ��ġ�ϴ� ����ڸ� ã�� �� �����ϴ�.");
        }

        if (name != "") {
            if (info[location][1] != name) {
                throw WrongRuleArgumentException("��ȭ��ȣ�� �̸�", "�ش� ��ȭ��ȣ�� ��ġ�ϴ� ����� �̸��� �ٸ��ϴ�.");
            }
        }

        vector<vector<string>> userInfo = File::getUserData(id); // �����ȣ ���೯¥ ���۽ð� ����ð� ���ȣ
        time_t now, reserveat;
        time(&now);

        change = userInfo.size();
        for (int i = 0; i < userInfo.size(); i++) {
            tm reser({0, stoi(userInfo[i][2].substr(3, 2)), stoi(userInfo[i][2].substr(0, 2)),
                      stoi(userInfo[i][1].substr(8, 2)), stoi(userInfo[i][1].substr(5, 2)) - 1,
                      stoi(userInfo[i][1].substr(0, 4)) - 1900});
            if (difftime(now, mktime(&reser)) < 0) {
                change = i;
                break;
            }
        }

        int count=0;
        for (int i = 0; i < userInfo.size(); i++)
            if (count < (userInfo[i].size() - 2) / 3)
                count = (userInfo[i].size() - 2) / 3;
        

        cout << "�̸�\t\t\t��ȭ��ȣ" << endl;
        cout << info[location][1] << "\t\t\t" << info[location][2] << endl << endl;
        cout << "���� ��Ȳ" << endl << endl;
        cout << "���� ��¥" << "\t" << "�̿� �ð�" << "\t" << "�� ��ȣ";
        for (int i = 0; i < count/3.3; i++)
            cout << "\t";
        if (count == 9)
            cout << "\t";

        cout << "\t���� ��ȣ" << endl << endl;
        for (int i = change; i < userInfo.size(); i++) {
            set<string> room;
            set<string> ::iterator iter;
            int roomCount = (userInfo[i].size()-2)/3;

            for (int j = 0; j < roomCount; j++) {
                room.insert(userInfo[i][4 + 3 * j]);
            }


            cout << userInfo[i][1] << " | " << userInfo[i][2] << " ~ " << userInfo[i][userInfo[i].size() - 2] << " | \t";
            for (iter = room.begin(); iter != room.end(); iter++) {
                cout << *iter << ", ";
            }
            if (roomCount != 6 || count != 6)
                cout << "\b\b \b\t";
            else
                cout << "\b\b \b";
            
            if (count > 6 && roomCount == 6 &&count != 9)
                cout << "\b";

            if ((roomCount != 9 && count == 9 && roomCount != 6) && !((count == 7 || count == 8) && roomCount == 6))
                cout << "\t";

            for (int j = 0; j < int(count / 3.3) - int(roomCount / 3.3); j++) {
                cout << "\t";
            }
               

            cout<<"| \t" << userInfo[i][0] << endl << endl;
        }
        
        //������ ��
        cout << endl << "�̿� ��Ȳ" << endl << endl;
        cout << "���� ��Ȳ" << endl << endl;
        cout << "���� ��¥" << "\t" << "�̿� �ð�" << "\t" << "�� ��ȣ";
        for (int i = 0; i < count / 3.3; i++)
            cout << "\t";
        if (count == 9)
            cout << "\t";

        cout << "\t���� ��ȣ" << endl << endl;
        for (int i = 0; i < change; i++) {
            set<string> room;
            set<string> ::iterator iter;
            int roomCount = (userInfo[i].size() - 2) / 3;

            for (int j = 0; j < roomCount; j++) {
                room.insert(userInfo[i][4 + 3 * j]);
            }


            cout << userInfo[i][1] << " | " << userInfo[i][2] << " ~ " << userInfo[i][userInfo[i].size() - 2] << " | \t";
            for (iter = room.begin(); iter != room.end(); iter++) {
                cout << *iter << ", ";
            }
            if (roomCount != 6 || count != 6)
                cout << "\b\b \b\t";
            else
                cout << "\b\b \b";


            if (count > 6 && roomCount == 6 && count != 9)
                cout << "\b";

            if ((roomCount != 9 && count == 9 && roomCount != 6) && !((count == 7 || count == 8) && roomCount == 6))
                cout << "\t";

            for (int j = 0; j < int(count / 3.3) - int(roomCount / 3.3); j++) {
                cout << "\t";
            }


            cout << "| \t" << userInfo[i][0] << endl << endl;
        }
    }
    catch (exception &e) {
        exceptionMannager(e);
    }

}
