#pragma once

#include <iostream>
#include <vector>
#include "ExceptionClass.h"
#include "Convert2Standard.h"
#include "Parsing.h"
#include "User.h"
#include "WindowEnum.h"
#include "Help.h"
//#include "File.h"

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
    }
    else if (command == "signup") {
        vector<string> stdArgv = Convert2Standard::convertBook(argv);
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
        throw UnableCommandException(command, "Book");
    }
}

void windowUserSearch(string &command, vector<string> &argv) {
    if (command == "list") {

    }
    else if (command == "check") {
        window = Window::User;
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

int main() {
    cout << "프로그램을 시작합니다." << endl;
    //File::start();

    vector<string> argv;
    vector<string> stdargv;

    while (1) {
        string line;
        try {
            while (1) {
                printPrompt();
                getline(cin, line);

                string command;
                getline(cin, command);
                argv = Parsing::split(command);
                if (argv.size() == 0); // Exception

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