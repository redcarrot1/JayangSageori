#include "Convert2Standard.h"
#include "ExceptionClass.h"
#include <string>
#include <sstream>
#include <regex>

using namespace std;

// ^: �̻�, _: ����
vector<string> Convert2Standard::split(string s, string pattern) {
    regex re(pattern);
    sregex_token_iterator it(s.begin(), s.end(), re, -1), end;
    return {it, end};
}

/*ǥ�� ����*/
// ^: �̻�, _: ����
string Convert2Standard::stdPhoneNum(string phoneNum) {
    // 1. ���� Ȯ�� (7^20_)
    size_t length = phoneNum.length();
    string std = "";
    if (length < 7 || 20 < length) {
        throw WrongLengthArgumentException(phoneNum, "7-20");
    }
    // 2. ���� Ȯ�� ([0-9] ['-'|[0-9]] [0-9])
    for (int i = 0; i < length; i++) {
        char ch = phoneNum[i];

        if (!isdigit(ch) && ch != '-') {
            throw WrongCharArgumentException(phoneNum, ch);  // �߸��� ����
        }
        if ((i == 0 || i == length - 1) && ch == '-') {
            ArgumentException h = ArgumentException(phoneNum);
            string basicError(h.getError());
            h.setError(basicError + "\n�� ���̳� �� �ڿ� ������(-)�� �����մϴ�.");
            throw h;
        }
        if (isdigit(ch)) {
            std.push_back(ch);
        }
    }
    // 3. ������ ���� Ȯ�� ([0-9]{7^11_})
    if (std.length() < 7 || 11 < std.length()) {
        throw WrongRuleArgumentException(phoneNum, "��ȭ��ȣ�� 7���� �̻� 11���� ������ ���̸� �����ؾ��մϴ�.");
    }
    return std;  // ǥ������ ��ȯ
}

string Convert2Standard::stdName(string name) {
    // 1. ���� Ȯ�� (2^30_)
    size_t length = name.length();
    string std = "";
    if (length < 2 || 30 < length) {
        throw WrongLengthArgumentException(name, "2-30");
    }
    // 2. ���� Ȯ�� ([a-z]|[A-z])
    for (int i = 0; i < length; i++) {
        char ch = name[i];
        if (!isalpha(ch)) {
            throw WrongCharArgumentException(name, ch);  // �߸��� ����
        }
        if ('A' <= ch && ch <= 'Z') {
            ch = tolower(ch);
        }
        std.push_back(ch); // ǥ������ : .lower()
    }
    return std;
}

string Convert2Standard::stdDate(string date) {
    // 1. ���� Ȯ�� 6^10_
    size_t length = date.length();
    bool flag = false;
    string std = "";
    if (length < 6 || 10 < length) {
        throw WrongLengthArgumentException(date, "6-10");
    }
    // 2. ����Ȯ��
    // 2-1) [0-9]{2|4}['/'|'-'][0-9]{2}['/'|'-'][0-9]{2}
    for (int i = 0; i < length; i++) {
        char ch = date[i];
        if (!isdigit(ch) && ch != '-' && ch != '/') {
            throw WrongCharArgumentException(date, ch);  // �߸��� ����
        }
        if (ch == '-' || ch == '/') {
            flag = true;
        }
        if (isdigit(ch)) {
            std.push_back(ch);
        }
    }
    // 2-2) [0-9]{6|8}
    if (!flag) {
        if (std.length() != 6 && std.length() != 8) {
            ArgumentException e = ArgumentException(date);
            string basicError(e.getError());
            e.setError(basicError + "\n�����ڸ� ������� �ʴ°��, ��¥�� 6�� �Ǵ� 8���� ���ڷ� ǥ���Ǿ�� �մϴ�.");
            throw e;
        }
    }
    // ǥ������ : 20YY-MM-DD �߰� ó��
    if (std.length() <= 6) {
        //�տ� 20 ����
        std.insert(0, "20");
    }
    // 2-3) ������ �߸� ����Ѱ� �ƴ��� ���� + ������ �̿��� �� ǥ������ �߰� ó��
    if (flag) {
        vector<string> d = split(date, R"(-|/)");
        if (d.size() != 3 || date.back() == '-' || date.back() == '/') {
            ArgumentException e = ArgumentException(date);
            string basicError(e.getError());
            e.setError(basicError + "\n������ ����� �߸��Ǿ����ϴ�.");
            throw e;
        }
        if (d.at(0).length() != 2 && d.at(0).length() != 4) {
            ArgumentException e = ArgumentException(date);
            string basicError(e.getError());
            e.setError(basicError + "\n(������ ����) ����(year)�� 2�� �Ǵ� 4���� ���ڷ� ǥ���Ǿ�� �մϴ�.");
            throw e;
        }
        if (d.at(1).length() != 2) {
            if (d.at(1).length() == 1) {
                std.insert(4, "0");
            }
            else {
                ArgumentException e = ArgumentException(date);
                string basicError(e.getError());
                e.setError(basicError + "\n(������ ����) ��(month)�� 1�� �Ǵ� 2���� ���ڷ� ǥ���Ǿ�� �մϴ�.");
                throw e;
            }
        }
        if (d.at(2).length() != 2) {
            if (d.at(2).length() == 1) {
                std.insert(6, "0");
            }
            else {
                ArgumentException e = ArgumentException(date);
                string basicError(e.getError());
                e.setError(basicError + "\n(������ ����) ��(day)�� 1�� �Ǵ� 2���� ���ڷ� ǥ���Ǿ�� �մϴ�.");
                throw e;
            }
        }
    }
    // ���̿� - ����
    std.insert(4, "-");
    std.insert(7, "-");
    return std;
}

string Convert2Standard::correctTime(string stdtime) {
    // �ð� ����
    vector<string> c = split(stdtime, R"(:)");
    string shh = c.at(0);
    string smm = c.at(1);
    int chh = stoi(shh);
    int cmm = stoi(smm);
    // a. if((int �� = int(MM)/HOUR) == 1) { HH+��, MM+������(%) }
    if (cmm / 60 == 1) {
        chh++;
        cmm = cmm % 60;
    }

    // b. if(0 <= MM <= 14) {MM=00}, elif(15 <= MM <= 44) {MM=30}, else(45<=MM<=59) {MM=00, HH++}
    if (cmm <= 14) {
        smm = "00";
    }
    else if (cmm <= 44) {
        smm = "30";
    }
    else {
        smm = "00";
        chh++;
    }
    shh = to_string(chh);
    if (shh.length() == 1) {
        shh.insert(0, "0");
    }
    return shh + ":" + smm;
}

string Convert2Standard::stdTime(string time) {
    // 1. ���� Ȯ�� 1^5_
    size_t length = time.length();
    bool flag = false;
    string std = "";
    string correctstd = "";
    if (length < 1 || 5 < length) {
        throw WrongLengthArgumentException(time, "1-5");
    }
    // 2. ���� Ȯ��
    // 2-1) [0-9]{1-2}['/'|'-'|':'][0-9]{1-2}
    for (int i = 0; i < length; i++) {
        char ch = time[i];
        if (!isdigit(ch) && ch != '/' && ch != '-' && ch != ':') {
            throw WrongCharArgumentException(time, ch);  // �߸��� ����
        }
        if (ch == '/' || ch == '-' || ch == ':') {
            flag = true;
        }
        if (isdigit(ch)) {
            std.push_back(ch);
        }
    }
    // 2-2) [0-9]{1-4}
    if (!flag) {
        if (std.length() < 1 || 4 < std.length()) {
            ArgumentException e = ArgumentException(time);
            string basicError(e.getError());
            e.setError(basicError + "\n�����ڸ� ������� �ʴ°��, �ð��� 1������ 4���� ���ڷ� ǥ���Ǿ�� �մϴ�.");
            throw e;
        }
        // ������ ���� �� ǥ������ ó��
        if (std.length() == 1 || std.length() == 2) {
            std.append(":00");
            if (std.length() == 1) {
                std.insert(0, "0");
            }
        }
        else {
            if (std.length() == 3) {
                std.insert(0, "0");
            }
            std.insert(2, ":");
        }
    }
    // ������ ���� �� ǥ������ ó��
    if (flag) {
        vector<string> t = split(time, R"(-|/|:)");
        if (t.size() != 2 || time.back() == '-' || time.back() == '/' || time.back() == ':') {
            ArgumentException e = ArgumentException(time);
            string basicError(e.getError());
            e.setError(basicError + "\n������ ����� �߸��Ǿ����ϴ�.");
            throw e;
        }
        if (t.at(0).length() != 2) {
            if (t.at(0).length() == 1) {
                std.insert(0, "0");
            }
            else {
                ArgumentException e = ArgumentException(time);
                string basicError(e.getError());
                e.setError(basicError + "\n(������ ����) �ð�(hour)�� 1�� �Ǵ� 2���� ���ڷ� ǥ���Ǿ�� �մϴ�.");
                throw e;
            }
        }
        if (t.at(1).length() != 2) {
            if (t.at(1).length() == 1) {
                std.insert(2, "0");
            }
            else {
                ArgumentException e = ArgumentException(time);
                string basicError(e.getError());
                e.setError(basicError + "\n(������ ����) ��(minute)�� 1�� �Ǵ� 2���� ���ڷ� ǥ���Ǿ�� �մϴ�.");
                throw e;
            }
        }
        std.insert(2, ":");
    }
    correctstd = correctTime(std);
    return correctstd;
}

string Convert2Standard::stdRoomID(string roomID) {
    //1. ����Ȯ�� (1)
    size_t length = roomID.length();
    string std = "";
    if (length != 1) {
        throw WrongLengthArgumentException(roomID, "1");
    }
    //2. ����Ȯ��([1-9])
    if (!isdigit(roomID[0])) {
        throw WrongCharArgumentException(roomID, roomID[0]);  // �߸��� ����
    }
    // ǥ������ : �״�� (��Ģ�� �����ϸ� �״�� ��ȯ)
    std = roomID;
    return std;
}

/*public*/
vector<string> Convert2Standard::convertSign(vector<string> argv) {
    // ���� ���� �ݵ�� 2��
    // ù��° ���� : �̸�, �ι�° ���� : ��ȭ��ȣ
    vector<string> returnArgv;
    size_t argNum = argv.size() - 1;
    if (argNum != 2) {
        throw WrongNumArgumentException("signup/in");
    }
    returnArgv.push_back(stdName(argv.at(1)));
    returnArgv.push_back(stdPhoneNum(argv.at(2)));
    return returnArgv;
}

vector<string> Convert2Standard::convertBook(vector<string> argv) {
    // ���� ���� �ݵ�� 4��
    // 1.��¥, 2.���ȣ, 3,4.�ð�
    vector<string> returnArgv;
    size_t argNum = argv.size() - 1;
    if (argNum != 4) {
        throw WrongNumArgumentException("book");
    }
    returnArgv.push_back(stdDate(argv.at(1)));
    returnArgv.push_back(stdRoomID(argv.at(2)));
    returnArgv.push_back(stdTime(argv.at(3)));
    returnArgv.push_back(stdTime(argv.at(4)));
    return returnArgv;
}

vector<string> Convert2Standard::convertList(vector<string> argv) {
    // ���� ���� 0�� �Ǵ� 1��
    // ��¥
    vector<string> returnArgv;
    size_t argNum = argv.size() - 1;

    if (argNum == 0) return {};
    else if (argNum == 1) {
        returnArgv.push_back(stdDate(argv.at(1)));
    }
    else {
        throw WrongNumArgumentException("list");
    }
    return returnArgv;
}

vector<string> Convert2Standard::convertSearch(vector<string> argv) {
    // ��ȯ ���� : �̸� - ��ȭ��ȣ
    // ���� ���� 0�� ~ 2�� (ó����)
    string name;
    string phoneNum;
    vector<string> returnArgv;
    size_t argNum = argv.size() - 1;
    Window window = Window::AdminSearch;
    if (argNum == 0) {
        return {};
    }
    else if (argNum == 1) {
        bool numflag = false;  //���ڰ� ��Ÿ���� true;
        bool alphaflag = false; //��� ��Ÿ���� true
        int index = 0;
        // 1��-1 ���� üũ : (2^50_)
        size_t length = argv.at(1).length();
        if (length < 2 || 50 < length) {
            throw WrongLengthArgumentException(argv.at(1), "2-50");
        }
        // 1��-2 ���� üũ : [0-9]|[a-z]|[A-Z] & // 1��-3 ���ڳ���, ���ڳ��� ������ ������ ǥ�غ�ȯ ��� ȣ��
        for (int i = 0; i < length; i++) {
            char ch = argv.at(1)[i];
            if (!numflag && isdigit(ch)) {
                numflag = true;
                index = i;
            }
            if (!alphaflag && isalpha(ch)) {
                alphaflag = true;
            }
            if (!isdigit(ch) && !isalpha(ch) && ch != '-') {
                throw WrongCharArgumentException(argv.at(1), ch);  // �߸��� ����
            }
            if (alphaflag && numflag && isalpha(ch)) { //����->����->���� ȥ��
                throw ArgumentException(argv.at(1));
            }
        }
        if (!numflag) { //���� ���� ��
            name = argv.at(1);
        }
        else if (!alphaflag) {  //���� ���� ��
            phoneNum = argv.at(1);
        }
        else {  //�Ѵ� ���� ���
            name = argv.at(1).substr(0, index);
            phoneNum = argv.at(1).substr(index);
        }

        if (!name.empty()) {
            returnArgv.push_back(stdName(name));
        }
        if (!phoneNum.empty()) {
            if (name.empty()) {
                returnArgv.push_back("");
            }
            returnArgv.push_back(stdPhoneNum(phoneNum));
        }
    }
    else if (argNum == 2) {
        // 2�� : � ��Ұ� �������� / �������� �ľ��Ͽ� �̸�-��ȭ��ȣ ȣ�� (ù��° ������ �Ǵ�)
        if (isdigit(argv.at(1)[0])) {
            if (isalpha(argv.at(2)[0])) {
                phoneNum = argv.at(1);
                name = argv.at(2);
            }
            else {
                CommandException e = CommandException("search", window);
                string basicError(e.getError());
                e.setError(basicError + "���ڰ� 2���� ��� �ϳ��� �̸�, �ϳ��� ��ȭ��ȣ ������ ������մϴ�.");
                throw e;
            }
        }
        else if (isalpha(argv.at(1)[0])) {
            if (isdigit(argv.at(2)[0])) {
                name = argv.at(1);
                phoneNum = argv.at(2);
            }
            else {
                CommandException e = CommandException("search", window);
                string basicError(e.getError());
                e.setError(basicError + "���ڰ� 2���� ��� �ϳ��� �̸�, �ϳ��� ��ȭ��ȣ ������ ������մϴ�.");
                throw e;
            }
        }
        else {
            throw ArgumentException(argv.at(1));
        }
        returnArgv.push_back(stdName(name));
        returnArgv.push_back(stdPhoneNum(phoneNum));
    }
    else {
        throw WrongNumArgumentException("search");
    }
    return returnArgv;
}

//�߰�
string Convert2Standard::stdCommand(string command, Window window) {
    size_t length = command.length();
    string std;
    // 1. ���� Ȯ�� (2^30_)
    // 2. ���� Ȯ�� ([a-z]|[A-z])
    for (int i = 0; i < length; i++) {
        char ch = command[i];
        if (!isalpha(ch)) {
            throw WrongCommandException(command, window);
        }
        if ('A' <= ch && ch <= 'Z') {  // ��ҹ��� ��ȯ
            ch = tolower(ch);
        }
        std.push_back(ch);
    }
    vector<string> commandList = {"back", "exit", "logout", "help", "signup", "signin", "book", "list", "check",
                                  "logout", "ask", "search"};
    auto it = find(commandList.begin(), commandList.end(), std);
    if (it == commandList.end()) {
        throw WrongCommandException(command, window);
    }
    return std;
}