#include "File.h"

using namespace std;
namespace fs = filesystem;

void File::start() {
	//프로그램 시작 시, 각 디렉토리 생성 & meta.txt 이동
	if (!fs::exists("book")) {fs::create_directory("book");}
	if(!fs::exists("user")){ fs::create_directory("user"); }
	if (!fs::exists("resource")) { fs::create_directory("resource"); }
	if (!fs::exists("resource\\userdata.txt")) { ofstream("resource\\userdata.txt"); }
	if (fs::exists("meta.txt")) {
		if (!fs::exists("resource\\meta.txt")) {
			fs::copy("meta.txt", "resource\\meta.txt");
		}
		fs::remove("meta.txt");
	}
	else {
		try {
			if (!fs::exists("resource\\meta.txt"))	throw NotExistMetaFileException();
		}
		catch (exception& e) {
			exceptionMannager(e);
		}
	}
}

vector<vector<string>>File::getAllUsers() {
	//userdata.txt
	//UserData : userID, Name, phoneNum
	vector<vector<string>> data;
	ifstream datafile;
	try {
		datafile.open(".\\resource\\userdata.txt");
		if (!datafile.is_open())	throw NotExistFileException("userdata.txt");
	}
	catch (exception& e) {
		exceptionMannager(e);
	}
	string line;
	while (1) {
		getline(datafile, line);
		if (line == "")	break;
		istringstream iss(line);
		string str_buf;
		vector<string> v;
		while (getline(iss, str_buf, '\t')) {
			v.push_back(str_buf);
		}
		data.push_back(v);
	}
	datafile.close();
	return  data;		//UserData 전체 return (한 행에 한 명씩)
}
	
vector<string>File::getMetaData() {	
	//meta.txt
	//관리자 이름, 전화번호, 현재 회원 수, 예약 번호 
	vector<string> data;
	ifstream datafile;
	try {
		datafile.open(".\\resource\\meta.txt");
		if (!datafile.is_open())	throw NotExistMetaFileException();
	}
	catch (exception &e) {
		exceptionMannager(e);
	}
	while (1) {
		string line;
		getline(datafile, line);
		if (line == "")
			break;
		istringstream iss(line);
		string str_buf;
		while (getline(iss, str_buf, '\t')) {
			data.push_back(str_buf);
		}
	}
	datafile.close();
	return data;//정보 4개를 저장하는 벡터 return
}

vector<vector<string>>File::getUserData(string id) {
	//[UserID].txt
	//user 예약 정보 : 예약번호/예약날짜/시작시각/종료시각/방번호
	vector<vector<string>> data;
	ifstream datafile;
	try {
		datafile.open(".\\user\\" + id + ".txt");
		if (!datafile.is_open())	throw NotExistFileException(id + ".txt");
	}
	catch (exception& e) {
		exceptionMannager(e);
	}
	string line;
	while (1) {
		getline(datafile, line);
		if (line == "")	break;
		istringstream iss(line);
		string str_buf;
		vector<string> v;
		while (getline(iss, str_buf, '\t')) {
			v.push_back(str_buf);
		}
		data.push_back(v);
	}
	datafile.close();
	return data;	//해당 id를 가지는 유저의 예약 정보 전체 저장 벡터 return (한 행에 한 개)
}

vector<vector<string>>File::getBooking(string date) {//예약을 하고자 날짜를 인자로 받습니다
	//[YYYYMMDD].txt
	date.erase(remove(date.begin(), date.end(), '-'), date.end());//표준형식으로부터 변환
	ofstream file;
	if (!fs::exists(".\\book\\" + date + ".txt")) {//찾아보고 없으면 파일 생성(0으로 초기화)
		file.open(".\\book\\" + date + ".txt");
		for (int i = 0; i < 10; i++) {//방 1-9 (9개)
			for (int j = 0; j < 22; j++) {//30분 단위로 22칸
				file << "0\t";
			}
			file << "\n";
		}
		file.close();
	}
	ifstream datafile(".\\book\\" + date + ".txt");
	vector<vector<string>> data;
	string line;
	while (1) {
		getline(datafile, line);
		if (line == "")	break;
		istringstream iss(line);
		string str_buf;
		vector<string> v;
		while (getline(iss, str_buf, '\t')) {
			v.push_back(str_buf);
		}
		data.push_back(v);
	}
	datafile.close();
	return data; //해당 날짜의 예약 정보 전체 저장 벡터 return (한 행에 한 스터디룸)
}

void File::addNewUser(vector<string> newUser) {//새로운 user의 이름, 전화번호를 담고 있는 벡터
	ofstream file;
	vector<string> metaData = getMetaData();
	string num = "";
	//meta.txt 수정
	try {	//metadata 파일 format 확인
		if (metaData.size() != 4)	throw WrongFormatMetaFileException();
		num = to_string(stoi(metaData[2]) + 1);
		metaData[2] = num;
	}
	catch (exception &e) {
		exceptionMannager(e);
	}
	try {	//metadata 파일 존재 확인
		file.open(".\\resource\\meta.txt");
		if (!file.is_open())	throw NotExistMetaFileException();
		file << metaData[0] + "\t" + metaData[1] + "\n" + metaData[2] + "\n" + metaData[3];
		file.close();
	}
	catch(exception &e){
		exceptionMannager(e);
	}

	//[UserID].txt 파일 생성(빈 파일)
	file.open(".\\user\\" +num+".txt");
	file.close();

	//userdata.txt 마지막줄 추가
	try {
		string user = num + "\t" + newUser[0] + "\t" + newUser[1] + "\n";
		file.open(".\\resource\\userdata.txt", std::ios_base::app);
		if (!file.is_open())	throw NotExistFileException("userdata.txt");
		file << user;
		file.close();
	}
	catch (exception &e) {
		exceptionMannager(e);
	}
	
}

void File::setUserData(string id, vector<vector<string>> data) {//해당 user의 모든 예약 정보를 담은 벡터
	//[UserId].txt
	ofstream file;
	try {
		file.open(".\\user\\" + id + ".txt");
		if (!file.is_open())	throw NotExistFileException(id + ".txt");
	}
	catch(exception &e){
		exceptionMannager(e);
	}
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			file << data[i][j] + "\t";
		}
		file << "\n";
	}
	file.close();
}

void File::setBooking(string date, vector<vector<string>>data) {
	//[YYYYMMDD].txt
	//해당 날짜의 예약 정보 write
	date.erase(remove(date.begin(), date.end(), '-'), date.end());//표준형식으로부터 변환
	ofstream file(".\\book\\" + date + ".txt");
	if (!file.is_open()) {//찾아보고 없으면 파일 생성(0으로 초기화)
		ofstream file(".\\book\\" + date + ".txt");
		for (int i = 0; i < 10; i++) {//방 9개
			for (int j = 0; j < 22; j++) {//30분 단위로 22칸
				file << "0\t";
			}
			file << "\n";
		}
	}
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			file << data[i][j] + "\t";
		}
		file << "\n";
	}
	file.close();

	//meta 데이터의 마지막 예약 번호 증가
	vector<string> metaData;
	try {
		metaData = getMetaData();
		if (metaData.size() != 4)	throw WrongFormatMetaFileException();
		metaData[3] = to_string(stoi(metaData[3]) + 1);
		
	}
	catch (exception& e) {
		exceptionMannager(e);
	}
	try {
		file.open(".\\resource\\meta.txt");
		if (!file.is_open())	throw NotExistMetaFileException();
		file << metaData[0] + "\t" + metaData[1] + "\n" + metaData[2] + "\n" + metaData[3];
		file.close();
	}
	catch (exception& e) {
		exceptionMannager(e);
	}
}



