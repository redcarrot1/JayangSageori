#pragma once

#include <iostream>
#include <vector>
#include "File.h"

using std::string;

class SignUp {
private:
    static void validPhone(const string& phoneNum);
public:
    SignUp() = delete;
    static void signup(vector<string> argv);
};
