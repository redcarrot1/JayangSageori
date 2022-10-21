#pragma once

#include <string>
#include <vector>
#include <map>
#include "WindowEnum.h"

using namespace std;

class Help {
private:
    static void header();

    static void printCommand(const string &command);

    static void printCommand(const string &command, const string &description);

    static void commandDetailTemplate(const string& command, const string& commandDescription, const vector<string>& argPossibleOrder, const vector<string>& argDescription);

    static map<string, string> commandDescription;
public:
    Help() = delete;

    static void printHelp(Window window);
    static void printHelp(Window window, const string& command);
};
