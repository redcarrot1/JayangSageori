#include "User.h"
#include <iostream>

using namespace std;

User::User(int userId, string name, string phone) : userId(userId), name(name), phone(phone), role("user") {

}

User::User(string name, string phone) : userId(0), name(name), phone(phone), role("admin") {

}

int User::getUserId() {
    return this->userId;
}

string User::getName() {
    return this->name;
}

string User::getPhone() {
    return this->phone;
}

string User::getRole() {
    return this->role;
}

void User::printInfo() {
    // For 디버깅
    cout << "======== UserInfo ========" << endl;
    cout << "userId = " << this->userId << endl;
    cout << "name = " << this->name << endl;
    cout << "phone = " << this->phone << endl;
    cout << "role = " << this->role << endl;
    cout << "==========================" << endl;
}

bool User::isUser() {
    return role == "user";
}

bool User::isAdmin() {
    return role == "admin";
}

