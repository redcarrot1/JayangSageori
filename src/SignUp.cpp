#include "SignUp.h"
#include "File.h"
#include <string>

using namespace std;

void SignUp::signup(vector<string> argv) {
    string name = argv[0];
    string phNum = argv[1];

    vector<vector<string>> users = File::getAllUsers();
    for (vector<string> &user: users) {
        if (user[1] == name && user[2] == phNum)
            throw WrongRuleArgumentException(user[0], "이미 회원가입이 되어있는 회원입니다."); // TODO
    }

    File::addNewUser(argv);
    cout << "회원가입이 완료되었습니다." << endl;
    cout << "사용자 이름: " << name << endl;
    cout << "사용자 전화번호: " << phNum << endl;
}
