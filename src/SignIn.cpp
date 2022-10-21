#include "SignIn.h"

User SignIn::signin(vector<string> v1) {
    string name = v1[0];
    string phNum = v1[1];

    User admin = File::getAdmin();
    if (admin.getName() == name && admin.getPhone() == phNum) {
        cout << "�����ڷ� �α��� �Ǿ����ϴ�." << endl;
        return admin;
    }

    vector<vector<string>> users = File::getAllUsers();
    for (vector<string> &user: users) {
        if (user[1] == name && user[2] == phNum) {
            cout << "����ڷ� �α��� �Ǿ����ϴ�." << endl;
            return {user[0], user[1], user[2]};
        }
    }

    throw WrongRuleArgumentException("ȸ������", "�������� �ʴ� ȸ���Դϴ�.\n");
}