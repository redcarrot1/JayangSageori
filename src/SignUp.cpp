#include "SignUp.h"
#include "File.h"
#include <string>

using namespace std;

void SignUp::signup(vector<string> argv) {
    string name = argv[0];
    string phNum = argv[1];

    validPhone(phNum);

    File::addNewUser(argv);
    cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << endl;
    cout << "����� �̸�: " << name << endl;
    cout << "����� ��ȭ��ȣ: " << phNum << endl;
}

void SignUp::validPhone(const string& phoneNum) {
    // 1. ����� �ߺ� ����
    vector<vector<string>> users = File::getAllUsers();
    for (vector<string> &user: users) {
        if (user[2] == phoneNum)
            throw WrongRuleArgumentException(phoneNum, "�̹� ȸ�������� �Ǿ��ִ� ��ȭ��ȣ�Դϴ�.");
    }

    // 2. ������ ����
    User admin = File::getAdmin();
    if (admin.getPhone() == phoneNum)
        throw WrongRuleArgumentException(phoneNum, "�̹� ȸ�������� �Ǿ��ִ� ��ȭ��ȣ�Դϴ�.");
}
