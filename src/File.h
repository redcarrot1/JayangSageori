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
	string userdata;
	string meta;
	string booking;
	string userid;
	ifstream datafile;

	vector<vector<string>> readSplit();

public:
	File();//생성자
	vector<vector<string>>getAllUsers();
	vector<string>getMetaData();
	vector<vector<string>>getUserData(string id);
	vector<vector<string>>getBooking(string date);
	void addNewUser(vector<string> newUser);
	void setUserData(string id, vector<vector<string>> data);
	void setBooking(string date, vector<vector<string>>data);
};