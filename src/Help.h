#pragma once

#include <string>
#include <map>
#include "WindowEnum.h"

using namespace std;

class Help {
private:
    static void header();

    static void printCommand(const string &command);

    static void printCommand(const string &command, const string &description);

    static map<string, string> commandDescription;
public:
    Help() = delete;

    static void printHelp(Window window);
};
