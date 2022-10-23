#include "Convert2Standard.h"
#include "ExceptionClass.h"
#include <string>
#include <sstream>
#include <regex>

using namespace std;

// ^: 이상, _: 이하
vector<string> Convert2Standard::split(string s, string pattern) {
    regex re(pattern);
    sregex_token_iterator it(s.begin(), s.end(), re, -1), end;
    return {it, end};
}

/*표현 정의*/
// ^: 이상, _: 이하
string Convert2Standard::stdPhoneNum(string phoneNum) {
    // 1. 길이 확인 (7^20_)
    size_t length = phoneNum.length();
    string std = "";
    if (length < 7 || 20 < length) {
        throw WrongLengthArgumentException(phoneNum, "7-20");
    }
    // 2. 문자 확인 ([0-9] ['-'|[0-9]] [0-9])
    for (int i = 0; i < length; i++) {
        char ch = phoneNum[i];

        if (!isdigit(ch) && ch != '-') {
            throw WrongCharArgumentException(phoneNum, ch);  // 잘못된 문자
        }
        if ((i == 0 || i == length - 1) && ch == '-') {
            ArgumentException h = ArgumentException(phoneNum);
            string basicError(h.getError());
            h.setError(basicError + "\n맨 앞이나 맨 뒤에 하이픈(-)이 존재합니다.");
            throw h;
        }
        if (isdigit(ch)) {
            std.push_back(ch);
        }
    }
    // 3. 숫자의 개수 확인 ([0-9]{7^11_})
    if (std.length() < 7 || 11 < std.length()) {
        throw WrongRuleArgumentException(phoneNum, "전화번호는 7글자 이상 11글자 이하의 길이를 만족해야합니다.");
    }
    return std;  // 표준형식 반환
}

string Convert2Standard::stdName(string name) {
    // 1. 길이 확인 (2^30_)
    size_t length = name.length();
    string std = "";
    if (length < 2 || 30 < length) {
        throw WrongLengthArgumentException(name, "2-30");
    }
    // 2. 문자 확인 ([a-z]|[A-z])
    for (int i = 0; i < length; i++) {
        char ch = name[i];
        if (!isalpha(ch)) {
            throw WrongCharArgumentException(name, ch);  // 잘못된 문자
        }
        if ('A' <= ch && ch <= 'Z') {
            ch = tolower(ch);
        }
        std.push_back(ch); // 표준형식 : .lower()
    }
    return std;
}

string Convert2Standard::stdDate(string date) {
    // 1. 길이 확인 6^10_
    size_t length = date.length();
    bool flag = false;
    string std = "";
    if (length < 6 || 10 < length) {
        throw WrongLengthArgumentException(date, "6-10");
    }
    // 2. 문자확인
    // 2-1) [0-9]{2|4}['/'|'-'][0-9]{2}['/'|'-'][0-9]{2}
    for (int i = 0; i < length; i++) {
        char ch = date[i];
        if (!isdigit(ch) && ch != '-' && ch != '/') {
            throw WrongCharArgumentException(date, ch);  // 잘못된 문자
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
            e.setError(basicError + "\n구분자를 사용하지 않는경우, 날짜는 6개 또는 8개의 숫자로 표현되어야 합니다.");
            throw e;
        }
    }
    // 표준형식 : 20YY-MM-DD 추가 처리
    if (std.length() <= 6) {
        //앞에 20 삽입
        std.insert(0, "20");
    }
    // 2-3) 구분자 잘못 사용한건 아닌지 검증 + 구분자 이용할 때 표준형식 추가 처리
    if (flag) {
        vector<string> d = split(date, R"(-|/)");
        if (d.size() != 3 || date.back() == '-' || date.back() == '/') {
            ArgumentException e = ArgumentException(date);
            string basicError(e.getError());
            e.setError(basicError + "\n구분자 사용이 잘못되었습니다.");
            throw e;
        }
        if (d.at(0).length() != 2 && d.at(0).length() != 4) {
            ArgumentException e = ArgumentException(date);
            string basicError(e.getError());
            e.setError(basicError + "\n(구분자 사용시) 연도(year)는 2개 또는 4개의 숫자로 표현되어야 합니다.");
            throw e;
        }
        if (d.at(1).length() != 2) {
            if (d.at(1).length() == 1) {
                std.insert(4, "0");
            }
            else {
                ArgumentException e = ArgumentException(date);
                string basicError(e.getError());
                e.setError(basicError + "\n(구분자 사용시) 월(month)은 1개 또는 2개의 숫자로 표현되어야 합니다.");
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
                e.setError(basicError + "\n(구분자 사용시) 일(day)은 1개 또는 2개의 숫자로 표현되어야 합니다.");
                throw e;
            }
        }
    }
    // 사이에 - 삽입
    std.insert(4, "-");
    std.insert(7, "-");
    return std;
}

string Convert2Standard::correctTime(string stdtime) {
    // 시간 보정
    vector<string> c = split(stdtime, R"(:)");
    string shh = c.at(0);
    string smm = c.at(1);
    int chh = stoi(shh);
    int cmm = stoi(smm);
    // a. if((int 몫 = int(MM)/HOUR) == 1) { HH+몫, MM+나머지(%) }
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
    // 1. 길이 확인 1^5_
    size_t length = time.length();
    bool flag = false;
    string std = "";
    string correctstd = "";
    if (length < 1 || 5 < length) {
        throw WrongLengthArgumentException(time, "1-5");
    }
    // 2. 문자 확인
    // 2-1) [0-9]{1-2}['/'|'-'|':'][0-9]{1-2}
    for (int i = 0; i < length; i++) {
        char ch = time[i];
        if (!isdigit(ch) && ch != '/' && ch != '-' && ch != ':') {
            throw WrongCharArgumentException(time, ch);  // 잘못된 문자
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
            e.setError(basicError + "\n구분자를 사용하지 않는경우, 시간은 1개에서 4개의 숫자로 표현되어야 합니다.");
            throw e;
        }
        // 구분자 없을 때 표준형식 처리
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
    // 구분자 있을 때 표준형식 처리
    if (flag) {
        vector<string> t = split(time, R"(-|/|:)");
        if (t.size() != 2 || time.back() == '-' || time.back() == '/' || time.back() == ':') {
            ArgumentException e = ArgumentException(time);
            string basicError(e.getError());
            e.setError(basicError + "\n구분자 사용이 잘못되었습니다.");
            throw e;
        }
        if (t.at(0).length() != 2) {
            if (t.at(0).length() == 1) {
                std.insert(0, "0");
            }
            else {
                ArgumentException e = ArgumentException(time);
                string basicError(e.getError());
                e.setError(basicError + "\n(구분자 사용시) 시간(hour)는 1개 또는 2개의 숫자로 표현되어야 합니다.");
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
                e.setError(basicError + "\n(구분자 사용시) 분(minute)은 1개 또는 2개의 숫자로 표현되어야 합니다.");
                throw e;
            }
        }
        std.insert(2, ":");
    }
    correctstd = correctTime(std);
    return correctstd;
}

string Convert2Standard::stdRoomID(string roomID) {
    //1. 길이확인 (1)
    size_t length = roomID.length();
    string std = "";
    if (length != 1) {
        throw WrongLengthArgumentException(roomID, "1");
    }
    //2. 문자확인([1-9])
    if (!isdigit(roomID[0])) {
        throw WrongCharArgumentException(roomID, roomID[0]);  // 잘못된 문자
    }
    // 표준형식 : 그대로 (규칙만 만족하면 그대로 반환)
    std = roomID;
    return std;
}

/*public*/
vector<string> Convert2Standard::convertSign(vector<string> argv) {
    // 인자 개수 반드시 2개
    // 첫번째 인자 : 이름, 두번째 인자 : 전화번호
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
    // 인자 개수 반드시 4개
    // 1.날짜, 2.방번호, 3,4.시간
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
    // 인자 개수 0개 또는 1개
    // 날짜
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
    // 반환 형식 : 이름 - 전화번호
    // 인자 개수 0개 ~ 2개 (처리함)
    string name;
    string phoneNum;
    vector<string> returnArgv;
    size_t argNum = argv.size() - 1;
    Window window = Window::AdminSearch;
    if (argNum == 0) {
        return {};
    }
    else if (argNum == 1) {
        bool numflag = false;  //숫자가 나타나면 true;
        bool alphaflag = false; //영어가 나타나면 true
        int index = 0;
        // 1개-1 길이 체크 : (2^50_)
        size_t length = argv.at(1).length();
        if (length < 2 || 50 < length) {
            throw WrongLengthArgumentException(argv.at(1), "2-50");
        }
        // 1개-2 문자 체크 : [0-9]|[a-z]|[A-Z] & // 1개-3 문자끼리, 숫자끼리 모은뒤 데이터 표준변환 요소 호출
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
                throw WrongCharArgumentException(argv.at(1), ch);  // 잘못된 문자
            }
            if (alphaflag && numflag && isalpha(ch)) { //영어->숫자->영어 혼합
                throw ArgumentException(argv.at(1));
            }
        }
        if (!numflag) { //숫자 없을 떄
            name = argv.at(1);
        }
        else if (!alphaflag) {  //영어 없을 떄
            phoneNum = argv.at(1);
        }
        else {  //둘다 들어온 경우
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
        // 2개 : 어떤 요소가 숫자인지 / 영어인지 파악하여 이름-전화번호 호출 (첫번째 값으로 판단)
        if (isdigit(argv.at(1)[0])) {
            if (isalpha(argv.at(2)[0])) {
                phoneNum = argv.at(1);
                name = argv.at(2);
            }
            else {
                CommandException e = CommandException("search", window);
                string basicError(e.getError());
                e.setError(basicError + "인자가 2개인 경우 하나는 이름, 하나는 전화번호 형식을 따라야합니다.");
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
                e.setError(basicError + "인자가 2개인 경우 하나는 이름, 하나는 전화번호 형식을 따라야합니다.");
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

//추가
string Convert2Standard::stdCommand(string command, Window window) {
    size_t length = command.length();
    string std;
    // 1. 길이 확인 (2^30_)
    // 2. 문자 확인 ([a-z]|[A-z])
    for (int i = 0; i < length; i++) {
        char ch = command[i];
        if (!isalpha(ch)) {
            throw WrongCommandException(command, window);
        }
        if ('A' <= ch && ch <= 'Z') {  // 대소문자 변환
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