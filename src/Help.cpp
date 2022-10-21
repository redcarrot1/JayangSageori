#include <iostream>
#include <iomanip>
#include "Help.h"

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


