#pragma once

#include "ExceptionClass.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include "User.h"

using namespace std;
namespace fs = filesystem;

class File {
    static string rootPath;
public:
    static void start();

    static vector<vector<string>> getAllUsers();

    static vector<string> getMetaData();

    static User getAdmin();

    static vector<vector<string>> getUserData(string id);

    static vector<vector<string>> getBooking(string date);

    static void addNewUser(vector<string> newUser);

    static void setUserData(string id, vector<vector<string>> data);

    static void setBooking(string date, vector<vector<string>> data);
};