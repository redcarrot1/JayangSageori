#include <iostream>
#include <iomanip>
#include "Help.h"
#include "ExceptionClass.h"

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

void Help::printHelp(Window window, const string &command) {
    if (window == Window::Main) {
        if (command == "help")
            commandDetailTemplate("help", "������ ����մϴ�.", {"", "1"}, {"������ �ڼ��� ���� ���� ��ɾ �Է��մϴ�."});
        else if (command == "signup")
            commandDetailTemplate("signup", "������ ����մϴ�.", {"1 2"}, {"����� �̸��� �Է��մϴ�.", "����� ��ȭ��ȣ�� �Է��մϴ�."});
        else if (command == "signin")
            commandDetailTemplate("signin", "������ ����մϴ�.", {"1 2"}, {"����� �̸��� �Է��մϴ�.", "����� ��ȭ��ȣ�� �Է��մϴ�."});
        else if (command == "exit")
            commandDetailTemplate("exit", "���α׷��� �����մϴ�.", {}, {});
        else throw UnableCommandException(command, window, "command");
    }
    else if (window == Window::User) {
        if (command == "help")
            commandDetailTemplate("help", "������ ����մϴ�.", {"", "1"}, {"������ �ڼ��� ���� ���� ��ɾ �Է��մϴ�."});
        else if (command == "logout")
            commandDetailTemplate("logout", "�α׾ƿ� �� ���� ���â���� �̵��մϴ�.", {}, {});
        else if (command == "book")
            commandDetailTemplate("book", "���͵�� ������ �����ϴ� ���â���� �̵��մϴ�.", {}, {});
        else if (command == "search")
            commandDetailTemplate("search", "ȸ������ ���� ��Ȳ�� Ȯ���� �� �ִ� ���â���� �̵��մϴ�.", {}, {});
        else throw UnableCommandException(command, window, "command");
    }
    else if (window == Window::UserBook) {
        if (command == "help")
            commandDetailTemplate("help", "������ ����մϴ�.", {"", "1"}, {"������ �ڼ��� ���� ���� ��ɾ �Է��մϴ�."});
        else if (command == "back")
            commandDetailTemplate("back", "����� ���â���� �̵��մϴ�.", {}, {});
        else if (command == "book")
            commandDetailTemplate("book", "���͵�� ������ �մϴ�.", {"1 2 3 4 5"},
                                  {"������ ��¥�� �Է��մϴ�.", "������ ���͵�� ��ȣ�� �Է��մϴ�.(1~9)", "�̿� ���� �ð��� �Է��մϴ�.",
                                   "�̿� ���� �ð��� �Է��մϴ�.", "������ �ο����� �Է��մϴ�."});
        else if (command == "list")
            commandDetailTemplate("list", "���͵���� ���� ��Ȳ�� ����մϴ�.", {"1", "2", "1 2"},
                                  {"������ �ο����� �Է��մϴ�.", "���͵���� ���� ��Ȳ�� Ȯ���� ��¥�� �Է��մϴ�."});
        else throw UnableCommandException(command, window, "command");
    }
    else if (window == Window::UserSearch) {
        if (command == "help")
            commandDetailTemplate("help", "������ ����մϴ�.", {"", "1"}, {"������ �ڼ��� ���� ���� ��ɾ �Է��մϴ�."});
        else if (command == "back")
            commandDetailTemplate("back", "����� ���â���� �̵��մϴ�.", {}, {});
        else if (command == "check")
            commandDetailTemplate("check", "������� ����� ���͵���� ����մϴ�.", {}, {});
        else throw UnableCommandException(command, window, "command");
    }
    else if (window == Window::Admin) {
        if (command == "help")
            commandDetailTemplate("help", "������ ����մϴ�.", {"", "1"}, {"������ �ڼ��� ���� ���� ��ɾ �Է��մϴ�."});
        else if (command == "logout")
            commandDetailTemplate("logout", "�α׾ƿ� �� ���� ���â���� �̵��մϴ�.", {}, {});
        else if (command == "search")
            commandDetailTemplate("search", "ȸ�� �˻��� �� �� �ִ� ���â���� �̵��մϴ�.", {}, {});
        else throw UnableCommandException(command, window, "command");
    }
    else if (window == Window::AdminSearch) {
        if (command == "help")
            commandDetailTemplate("help", "������ ����մϴ�.", {"", "1"}, {"������ �ڼ��� ���� ���� ��ɾ �Է��մϴ�."});
        else if (command == "back")
            commandDetailTemplate("back", "������ ���â���� �̵��մϴ�.", {}, {});
        else if (command == "ask")
            commandDetailTemplate("ask", "ȸ�� ������ ��ȸ�մϴ�.", {"", "1", "2", "1 2", "2 1", "3"},
                                  {"�˻��� �̸��� �Է��մϴ�.", "�˻��� ��ȭ��ȣ�� �Է��մϴ�.",
                                   "�˻��� �̸��� ��ȭ��ȣ�� �� ���� ���� ����� ���� �ʰ�, ������� ���������� �Է��մϴ�."});
        else throw UnableCommandException(command, window, "command");
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

void Help::commandDetailTemplate(const string &command, const string &commandDescription,
                                 const vector<string> &argPossibleOrders,
                                 const vector<string> &argDescription) {
    cout << "��ɾ�" << endl;
    cout << "\t" << command << " : " << commandDescription << endl;

    cout << "������ ������ ����" << endl;

    if (argPossibleOrders.empty()) {
        cout << "\t�ش� ��ɾ�� ���ڸ� ���� �ʽ��ϴ�." << endl;
        return;
    }

    for (const auto &argPossibleOrder: argPossibleOrders) {
        cout << "\t" << command;
        for (size_t j = 0; j < argPossibleOrder.length(); j += 2) {
            cout << " [���� " << argPossibleOrder[j] << "]";
        }
        cout << endl;
    }

    cout << "�� ������ ��Ģ" << endl;
    for (size_t i = 0; i < argDescription.size(); i++) {
        cout << "\t[���� " << i + 1 << "] : " << argDescription[i] << endl;
    }
}