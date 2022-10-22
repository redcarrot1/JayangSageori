#include "SignUp.h"
#include "File.h"
#include <string>

using namespace std;

void SignUp::signup(vector<string> argv) {
    string name = argv[0];
    string phNum = argv[1];

    validPhone(phNum);

    File::addNewUser(argv);
    cout << "회원가입이 완료되었습니다." << endl;
    cout << "사용자 이름: " << name << endl;
    cout << "사용자 전화번호: " << phNum << endl;
}

void SignUp::validPhone(const string& phoneNum) {
    // 1. 사용자 중복 검증
    vector<vector<string>> users = File::getAllUsers();
    for (vector<string> &user: users) {
        if (user[2] == phoneNum)
            throw WrongRuleArgumentException(phoneNum, "이미 회원가입이 되어있는 전화번호입니다.");
    }

    // 2. 관리자 검증
    User admin = File::getAdmin();
    if (admin.getPhone() == phoneNum)
        throw WrongRuleArgumentException(phoneNum, "이미 회원가입이 되어있는 전화번호입니다.");
}
