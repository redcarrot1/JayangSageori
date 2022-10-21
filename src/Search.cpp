#include "Search.h"

void Search::searchAll() {
    //UserData : userID, Name, phoneNum
    vector<vector<string>> target = File::getAllUsers();

    cout << "�̸�\t��ȭ��ȣ" << endl;
    for (auto &userData: target) {
        cout << userData[1] << "\t" << userData[2] << endl;
    }
}

void Search::searchByName(const string& name) {
    //UserData : userID, Name, phoneNum
    vector<vector<string>> target = File::getAllUsers();

    cout << "�̸�\t��ȭ��ȣ" << endl;
    for (auto &userData: target) {
        if (userData[1] == name) {
            cout << userData[1] << "\t" << userData[2] << endl;
        }
    }
}


void Search::searchByNameAndPhone(const string& name, const string& phone) {
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

        change = 0;
        {// TODO �������� �Ǵ��ϴ� ��
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


        cout << "�̸�\t��ȭ��ȣ" << endl;
        cout << info[location][1] << "\t" << info[location][2] << endl << endl;
        cout << "���� ��Ȳ" << endl << endl;
        cout << "���� ��¥" << "\t" << "�̿� �ð�" << "\t" << "�� ��ȣ" << "\t	" << "���� ��ȣ" << endl << endl;
        for (int i = change; i < userInfo.size(); i++) {
            cout << userInfo[i][1] << " | " << userInfo[i][2] << " ~ " << userInfo[i][3] << " | \t" << userInfo[i][4]
                 << "\t|\t" << userInfo[i][0] << endl << endl;
        }

        cout << endl << "�̿� ��Ȳ" << endl << endl;
        cout << "���� ��¥" << "\t" << "�̿� �ð�" << "\t" << "�� ��ȣ" << "\t	" << "���� ��ȣ" << endl << endl;
        for (int i = 0; i < change; i++) {
            cout << userInfo[i][1] << " | " << userInfo[i][2] << " ~ " << userInfo[i][3] << " | \t" << userInfo[i][4]
                 << "\t|\t" << userInfo[i][0] << endl << endl;
        }
    }
    catch (exception &e) {
        exceptionMannager(e);
    }

}
