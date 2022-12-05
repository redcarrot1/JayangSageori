#pragma once

#include <iostream>
#include <vector>
#include <ctime>
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

#pragma warning(disable:4996)

using namespace std;

Window window = Window::Main;
User user;

void printPrompt() {
    cout << endl;
    if (window == Window::Main) cout << "Main > ";
    else if (window == Window::User) cout << user.getName().substr(0, 8) << " > ";
    else if (window == Window::UserBook) cout << user.getName().substr(0, 8) << "/Book > ";
    else if (window == Window::UserSearch) cout << user.getName().substr(0, 8) << "/Search > ";
    else if (window == Window::Admin) cout << "Admin > ";
    else if (window == Window::AdminSearch) cout << "Admin/Search > ";
}

void windowMain(string& command, vector<string>& argv) {
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
        if (argv.size() == 1) Help::printHelp(window);
        else if (argv.size() == 2) Help::printHelp(window, argv[1]);
        else throw WrongNumArgumentException("help");
    }
    else if (command == "exit") {
        if (argv.size() == 1) {
            cout << "프로그램을 종료합니다." << endl;
            exit(EXIT_SUCCESS);
        }
        else throw WrongNumArgumentException("exit");
    }
    else {
        throw UnableCommandException(command, window, "Main");
    }
}

void windowUser(string& command, vector<string>& argv) {
    if (command == "book") {
        if (argv.size() == 1) window = Window::UserBook;
        else throw WrongNumArgumentException("book");
    }
    else if (command == "search") {
        if (argv.size() == 1) window = Window::UserSearch;
        else throw WrongNumArgumentException("search");
    }
    else if (command == "logout") {
        if (argv.size() == 1) window = Window::Main;
        else throw WrongNumArgumentException("logout");
    }
    else if (command == "help") {
        if (argv.size() == 1) Help::printHelp(window);
        else if (argv.size() == 2) Help::printHelp(window, argv[1]);
        else throw WrongNumArgumentException("help");
    }
    else {
        throw UnableCommandException(command, window, "User");
    }
}

void windowUserBook(string& command, vector<string>& argv) {
    if (command == "book") {
        vector<string> stdArgv = Convert2Standard::convertBook(argv);
        Book book(stdArgv[0], stdArgv[1], stdArgv[2], stdArgv[3], user.getUserId(), stdArgv[4]);
        book.excuteBook();
    }
    else if (command == "list") {
        vector<string> stdArgv = Convert2Standard::convertList(argv);
        if (stdArgv.size() == 1) {
            time_t timer = time(NULL);
            struct tm* t = localtime(&timer);
            string arg = to_string(t->tm_year + 1900) + "-" + to_string(t->tm_mon + 1) + "-" + to_string(t->tm_mday);
            List::excuteList(stdArgv[0], arg);
        }
        else List::excuteList(stdArgv[0], stdArgv[1]);
    }
    else if (command == "back") {
        if (argv.size() == 1) window = Window::User;
        else throw WrongNumArgumentException("back");
    }
    else if (command == "help") {
        if (argv.size() == 1) Help::printHelp(window);
        else if (argv.size() == 2) Help::printHelp(window, argv[1]);
        else throw WrongNumArgumentException("help");
    }
    else {
        throw UnableCommandException(command, window, "Book");
    }
}

void windowUserSearch(string& command, vector<string>& argv) {
    if (command == "check") {
        if (argv.size() == 1) Check::excuteCheck(user.getUserId());
        else throw WrongNumArgumentException("check");
    }
    else if (command == "back") {
        if (argv.size() == 1) window = Window::User;
        else throw WrongNumArgumentException("back");
    }
    else if (command == "help") {
        if (argv.size() == 1) Help::printHelp(window);
        else if (argv.size() == 2) Help::printHelp(window, argv[1]);
        else throw WrongNumArgumentException("help");
    }
    else {
        throw UnableCommandException(command, window, "Search");
    }
}

void windowAdmin(string& command, vector<string>& argv) {
    if (command == "search") {
        if (argv.size() == 1) window = Window::AdminSearch;
        else throw WrongNumArgumentException("search");
    }
    else if (command == "logout") {
        if (argv.size() == 1) window = Window::Main;
        else throw WrongNumArgumentException("logout");
    }
    else if (command == "help") {
        if (argv.size() == 1) Help::printHelp(window);
        else if (argv.size() == 2) Help::printHelp(window, argv[1]);
        else throw WrongNumArgumentException("help");
    }
    else {
        throw UnableCommandException(command, window, "Admin");
    }
}

void windowAdminSearch(string& command, vector<string>& argv) {
    if (command == "ask") {
        vector<string> stdArgv = Convert2Standard::convertSearch(argv);
        if (stdArgv.empty()) Search::searchAll();
        else if (stdArgv.size() == 1) Search::searchByName(stdArgv[0]);
        else Search::searchByNameAndPhone(stdArgv[0], stdArgv[1]);
    }
    else if (command == "back") {
        if (argv.size() == 1) window = Window::Admin;
        else throw WrongNumArgumentException("back");
    }
    else if (command == "help") {
        if (argv.size() == 1) Help::printHelp(window);
        else if (argv.size() == 2) Help::printHelp(window, argv[1]);
        else throw WrongNumArgumentException("help");
    }
    else {
        throw UnableCommandException(command, window, "Search");
    }
}

// 데이터 파일이 저장되어 있는 폴더로 경로 지정하시면 됩니다.
// 예를 들어, /kim/desktop/  으로 설정하시면, 해당 폴더 내에 book 폴더, resource 폴더, user 폴더가 있어야 합니다.
string File::rootPath = "../../";

int main() {
    cout << "프로그램을 시작합니다." << endl;
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
                if (argv.empty()) continue;

                command = Convert2Standard::stdCommand(argv.at(0), window);

                if (window == Window::Main) windowMain(command, argv);
                else if (window == Window::User) windowUser(command, argv);
                else if (window == Window::UserBook) windowUserBook(command, argv);
                else if (window == Window::UserSearch) windowUserSearch(command, argv);
                else if (window == Window::Admin) windowAdmin(command, argv);
                else if (window == Window::AdminSearch) windowAdminSearch(command, argv);
            }
        }
        catch (exception& e) {
            exceptionMannager(e); //오류에 대한 정보
        }
    }
}
