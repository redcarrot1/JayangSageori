#include <iostream>
#include <iomanip>
#include "Help.h"
#include "ExceptionClass.h"

using namespace std;

map<string, string> Help::commandDescription{
        {"help",   "도움말 출력"},
        {"back",   "이전 명령창으로 되돌아감"},
        {"signup", "회원가입"},
        {"signin", "로그인"},
        {"exit",   "프로그램 종료"},
        {"ask",    "회원 정보 검색"},
        {"book",   "예약하기"},
        {"list",   "스터디룸 예약 현황 출력"},
        {"check",  "사용자의 스터디룸 예약 출력"},
        {"logout", "로그아웃 후 메인 명령창으로 이동"}
};

void Help::printHelp(Window window) {
    header();

    if (window == Window::Main) {
        for (string command: {"help", "signup", "signin", "exit"}) {
            printCommand(command);
        }
    }
    else if (window == Window::User) {
        printCommand("help");
        printCommand("logout");
        printCommand("book", "예약 명령창으로 이동");
        printCommand("search", "예약 확인 명령창으로 이동");
    }
    else if (window == Window::UserBook) {
        for (string command: {"help", "back", "book", "list"}) {
            printCommand(command);
        }
    }
    else if (window == Window::UserSearch) {
        for (string command: {"help", "back", "check"}) {
            printCommand(command);
        }
    }
    else if (window == Window::Admin) {
        printCommand("help");
        printCommand("logout");
        printCommand("search", "회원 검색 명령창으로 이동");
    }
    else if (window == Window::AdminSearch) {
        for (string command: {"help", "back", "ask"}) {
            printCommand(command);
        }
    }
}

void Help::printHelp(Window window, const string &command) {
    if (window == Window::Main) {
        if (command == "help")
            commandDetailTemplate("help", "도움말을 출력합니다.", {"", "1"}, {"도움말을 자세히 보고 싶은 명령어를 입력합니다."});
        else if (command == "signup")
            commandDetailTemplate("signup", "도움말을 출력합니다.", {"1 2"}, {"사용자 이름을 입력합니다.", "사용자 전화번호를 입력합니다."});
        else if (command == "signin")
            commandDetailTemplate("signin", "도움말을 출력합니다.", {"1 2"}, {"사용자 이름을 입력합니다.", "사용자 전화번호를 입력합니다."});
        else if (command == "exit")
            commandDetailTemplate("exit", "프로그램을 종료합니다.", {}, {});
        else throw UnableCommandException(command, window, "command");
    }
    else if (window == Window::User) {
        if (command == "help")
            commandDetailTemplate("help", "도움말을 출력합니다.", {"", "1"}, {"도움말을 자세히 보고 싶은 명령어를 입력합니다."});
        else if (command == "logout")
            commandDetailTemplate("logout", "로그아웃 후 메인 명령창으로 이동합니다.", {}, {});
        else if (command == "book")
            commandDetailTemplate("book", "스터디룸 예약을 진행하는 명령창으로 이동합니다.", {}, {});
        else if (command == "search")
            commandDetailTemplate("search", "회원님의 예약 현황을 확인할 수 있는 명령창으로 이동합니다.", {}, {});
        else throw UnableCommandException(command, window, "command");
    }
    else if (window == Window::UserBook) {
        if (command == "help")
            commandDetailTemplate("help", "도움말을 출력합니다.", {"", "1"}, {"도움말을 자세히 보고 싶은 명령어를 입력합니다."});
        else if (command == "back")
            commandDetailTemplate("back", "사용자 명령창으로 이동합니다.", {}, {});
        else if (command == "book")
            commandDetailTemplate("book", "스터디룸 예약을 합니다.", {"1 2 3 4 5"},
                                  {"예약할 날짜를 입력합니다.", "예약할 스터디룸 번호를 입력합니다.(1~9)", "이용 시작 시간을 입력합니다.",
                                   "이용 종료 시간을 입력합니다.", "예약할 인원수를 입력합니다."});
        else if (command == "list")
            commandDetailTemplate("list", "스터디룸의 예약 현황을 출력합니다.", {"1", "2", "1 2"},
                                  {"예약할 인원수를 입력합니다.", "스터디룸의 예약 현황을 확인할 날짜를 입력합니다."});
        else throw UnableCommandException(command, window, "command");
    }
    else if (window == Window::UserSearch) {
        if (command == "help")
            commandDetailTemplate("help", "도움말을 출력합니다.", {"", "1"}, {"도움말을 자세히 보고 싶은 명령어를 입력합니다."});
        else if (command == "back")
            commandDetailTemplate("back", "사용자 명령창으로 이동합니다.", {}, {});
        else if (command == "check")
            commandDetailTemplate("check", "사용자의 예약된 스터디룸을 출력합니다.", {}, {});
        else throw UnableCommandException(command, window, "command");
    }
    else if (window == Window::Admin) {
        if (command == "help")
            commandDetailTemplate("help", "도움말을 출력합니다.", {"", "1"}, {"도움말을 자세히 보고 싶은 명령어를 입력합니다."});
        else if (command == "logout")
            commandDetailTemplate("logout", "로그아웃 후 메인 명령창으로 이동합니다.", {}, {});
        else if (command == "search")
            commandDetailTemplate("search", "회원 검색을 할 수 있는 명령창으로 이동합니다.", {}, {});
        else throw UnableCommandException(command, window, "command");
    }
    else if (window == Window::AdminSearch) {
        if (command == "help")
            commandDetailTemplate("help", "도움말을 출력합니다.", {"", "1"}, {"도움말을 자세히 보고 싶은 명령어를 입력합니다."});
        else if (command == "back")
            commandDetailTemplate("back", "관리자 명령창으로 이동합니다.", {}, {});
        else if (command == "ask")
            commandDetailTemplate("ask", "회원 정보를 조회합니다.", {"", "1", "2", "1 2", "2 1", "3"},
                                  {"검색할 이름을 입력합니다.", "검색할 전화번호를 입력합니다.",
                                   "검색할 이름과 전화번호를 두 개의 순서 고려를 하지 않고, 공백없이 연속적으로 입력합니다."});
        else throw UnableCommandException(command, window, "command");
    }
}

void Help::header() {
    cout << "--------------------------------------" << endl;
    cout << "   명령어   |        기능" << endl;
    cout << "--------------------------------------" << endl;
}

void Help::printCommand(const string &command) {
    cout << std::left << setw(10) << command;
    cout << "|  " << commandDescription[command] << endl;
}


void Help::printCommand(const string &command, const string &description) {
    cout << std::left << setw(10) << command;
    cout << "|  " << description << endl;
}

void Help::commandDetailTemplate(const string &command, const string &commandDescription,
                                 const vector<string> &argPossibleOrders,
                                 const vector<string> &argDescription) {
    cout << "명령어" << endl;
    cout << "\t" << command << " : " << commandDescription << endl;

    cout << "가능한 인자의 형태" << endl;

    if (argPossibleOrders.empty()) {
        cout << "\t해당 명령어는 인자를 받지 않습니다." << endl;
        return;
    }

    for (const auto &argPossibleOrder: argPossibleOrders) {
        cout << "\t" << command;
        for (size_t j = 0; j < argPossibleOrder.length(); j += 2) {
            cout << " [인자 " << argPossibleOrder[j] << "]";
        }
        cout << endl;
    }

    cout << "각 인자의 규칙" << endl;
    for (size_t i = 0; i < argDescription.size(); i++) {
        cout << "\t[인자 " << i + 1 << "] : " << argDescription[i] << endl;
    }
}