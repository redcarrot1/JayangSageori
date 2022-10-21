#include <iostream>
#include <iomanip>
#include "Help.h"

using namespace std;

map<string, string> Help::commandDescription{
        {"help",   "���� ���"},
        {"back",   "���� ���â���� �ǵ��ư�"},
        {"signup", "ȸ������"},
        {"signin", "�α���"},
        {"exit",   "���α׷� ����"},
        {"ask",    "ȸ�� ���� �˻�"},
        {"book",   "�����ϱ�"},
        {"list",   "���͵�� ���� ��Ȳ ���"},
        {"check",  "������� ���͵�� ���� ���"},
        {"logout", "�α׾ƿ� �� ���� ���â���� �̵�"}
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
        printCommand("book", "���� ���â���� �̵�");
        printCommand("search", "���� Ȯ�� ���â���� �̵�");
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
        printCommand("search", "ȸ�� �˻� ���â���� �̵�");
    }
    else if (window == Window::AdminSearch) {
        for (string command: {"help", "back", "ask"}) {
            printCommand(command);
        }
    }
}

void Help::header() {
    cout << "--------------------------------------" << endl;
    cout << "   ��ɾ�   |        ���" << endl;
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


