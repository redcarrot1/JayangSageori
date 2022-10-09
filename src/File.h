#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<direct.h>	//mkdir
#include<sstream>

using namespace std;

class File
{
private:
	string userdata = ".\\resource\\userdata.txt";
	string meta = ".\\resource\\meta.txt";
	string booking = ".\\book\\";
	string userid = ".\\user\\";
	ifstream datafile;

	static vector<vector<string>> readSplit();

public:
	//File();//생성자
	static void start();
	static vector<vector<string>>getAllUsers();
	static vector<string>getMetaData();
	static vector<vector<string>>getUserData(string id);
	static vector<vector<string>>getBooking(string date);
	static void addNewUser(vector<string> newUser);
	static void setUserData(string id, vector<vector<string>> data);
	static void setBooking(string date, vector<vector<string>>data);
};