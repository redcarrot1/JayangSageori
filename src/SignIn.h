#pragma once

#include <string>
#include <vector>
#include "File.h"
#include "SignIn.h"

class SignIn {
public:
    SignIn() = delete;
    static User signin(vector<string> args);
};
