#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include "File.h"

using std::string;


class SignUp {
private:
	string phNum;
	string name;

public:
	void signup(vector<string> v1);
};

class SignIn {
private:
	string phNum;
	string name;

public:
	void signin(vector<string> v1);

};
