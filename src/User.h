#pragma once

#include <string>

using std::string;

class User { // 사용자+admin 공용사용
private:
    int userId; // 관리자면 0, 사용자면 사용자id
    string name;
    string phone;
    string role; // 사용자면 user 또는 관리자면 admin, 나중에 enum으로 바꿀지도?
public:
    User(int userId, string name, string phone); // 사용자용
    User(string name, string phone); // 관리자용

    int getUserId();

    string getName();

    string getPhone();

    string getRole();

    void printInfo();

    bool isUser();

    bool isAdmin();
};