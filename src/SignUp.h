#pragma once

#include <iostream>
#include <vector>
#include "File.h"

using std::string;

class SignUp {
public:
    SignUp() = delete;
    static void signup(vector<string> argv);
};
