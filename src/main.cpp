#pragma once

#include <iostream>
#include <vector>
#include "ExceptionClass.h"
#include "Convert2Standard.h"
#include "Parsing.h"
#include "User.h"
#include "WindowEnum.h"
#include "Help.h"
#include "File.h"
#include "SignIn.h"
#include "SignUp.h"
#include "Book.h"
#include "Check.h"
#include "List.h"
#include "Search.h"
#include "User.h"

using namespace std;

Window window = Window::Main;
User user;

void printPrompt() {
    if (window == Window::Main) cout << "Main > ";
    else if (window == Window::User) cout << user.getName().substr(0, 8) << " > ";
    else if (window == Window::UserBook) cout << user.getName().substr(0, 8) << "/Book > ";
    else if (window == Window::UserSearch) cout << user.getName().substr(0, 8) << "/Search > ";
    else if (window == Window::Admin) cout << "Admin > ";
    else if (window == Window::AdminSearch) cout << "Admin/Search > ";
}

void windowMain(string &command, vector<string> &argv) {
    if (command == "signin") {
        vector<string> stdArgv = Convert2Standard::convertSign(argv);
        user = SignIn::signin(stdArgv);

        if (user.isAdmin()) window = Window::Admin;
        else window = Window::User;
    }
    else if (command == "signup") {
        vector<string> stdArgv = Convert2Standard::convertSign(argv);
        SignUp::signup(stdArgv);
    }
    else if (command == "help") {
        Help::printHelp(window);
    }
    else if (command == "exit") {
        exit(0);
    }
    else {
        throw UnableCommandException(command, "Main");
    }
}

void windowUser(string &command, vector<string> &argv) {
    if (command == "book") {
        window = Window::UserBook;
    }
    else if (command == "search") {
        window = Window::UserSearch;
    }
    else if (command == "logout") {
        window = Window::Main;
    }
    else if (command == "help") {
        Help::printHelp(window);
    }
    else {
        throw UnableCommandException(command, "User");
    }
}

void windowUserBook(string &command, vector<string> &argv) {
    if (command == "book") {
        vector<string> stdArgv = Convert2Standard::convertBook(argv);
        Book book(stdArgv[0], stdArgv[1], stdArgv[2], stdArgv[3], to_string(user.getUserId()));
        book.excuteBook();
    }
    else if (command == "list") {
        vector<string> stdArgv = Convert2Standard::convertList(argv);
        List list(stdArgv[0], to_string(user.getUserId()));
        list.excuteList();
    }
    else if (command == "back") {
        window = Window::User;
    }
    else if (command == "help") {
        Help::printHelp(window);
    }
    else {
        throw UnableCommandException(command, "Book");
    }
}

void windowUserSearch(string &command, vector<string> &argv) {
    if (command == "check") {
        Check check(to_string(user.getUserId()));
        check.excuteCheck();
    }
    else if (command == "back") {
        window = Window::User;
    }
    else if (command == "help") {
        Help::printHelp(window);
    }
    else {
        throw UnableCommandException(command, "Search");
    }
}

void windowAdmin(string &command, vector<string> &argv) {
    if (command == "search") {
        window = Window::AdminSearch;
    }
    else if (command == "logout") {
        window = Window::User;
    }
    else if (command == "help") {
        Help::printHelp(window);
    }
    else {
        throw UnableCommandException(command, "Admin");
    }
}

void windowAdminSearch(string &command, vector<string> &argv) {
    if (command == "ask") {
        vector<string> stdArgv = Convert2Standard::convertSearch(argv);
        if (stdArgv.size() == 1) Search::searchAll();
        else if (stdArgv.size() == 2) Search::searchByName(stdArgv[1]);
        else Search::searchByNameAndPhone(stdArgv[0], stdArgv[1]);
    }
    else if (command == "back") {
        window = Window::User;
    }
    else if (command == "help") {
        Help::printHelp(window);
    }
    else {
        throw UnableCommandException(command, "Search");
    }
}

string File::rootPath = "/Users/hongseungtaeg/Desktop/project/mycode/";

int main() {
    cout << "프로그램을 시작합니다." << endl;
    cout << "내 현재 경로 : " << fs::current_path() << std::endl; // test
    File::start();

    vector<string> argv;
    vector<string> stdargv;

    while (true) {
        try {
            while (true) {
                printPrompt();

                string command;
                getline(cin, command);
                argv = Parsing::split(command);
                if (argv.size() == 0); // Exception

                /*
                    cout << "=== 들어온 명령어 === ( / 로 명령어와 인자 구분)" << endl;
                    for (string &arg: argv) {
                        cout << arg << " / ";
                    }
                    cout << "\n========================================" << endl;
                */

                command = Convert2Standard::stdCommand(argv.at(0));

                if (window == Window::Main) windowMain(command, argv);
                else if (window == Window::User) windowUser(command, argv);
                else if (window == Window::UserBook) windowUserBook(command, argv);
                else if (window == Window::UserSearch) windowUserSearch(command, argv);
                else if (window == Window::Admin) windowAdmin(command, argv);
                else if (window == Window::AdminSearch) windowAdminSearch(command, argv);
            }
        }
        catch (exception &e) {
            exceptionMannager(e); //오류에 대한 정보
        }
    }
}