#include "SignIn.h"

User SignIn::signin(vector<string> v1) {
    string name = v1[0];
    string phNum = v1[1];

    User admin = File::getAdmin();
    if (admin.getName() == name && admin.getPhone() == phNum) {
        cout << "관리자로 로그인 되었습니다." << endl;
        return admin;
    }

    vector<vector<string>> users = File::getAllUsers();
    for (vector<string> &user: users) {
        if (user[1] == name && user[2] == phNum) {
            cout << "사용자로 로그인 되었습니다." << endl;
            return {user[0], user[1], user[2]};
        }
    }

    throw WrongRuleArgumentException("회원정보", "존재하지 않는 회원입니다.\n");
}