#include "File.h"

using namespace std;

vector<vector<string>> File::readSplit(string path){	//파일 읽어서 이차원 벡터에 집어넣어 return
	vector<vector<string>> data;
	ifstream datafile;
	datafile.open(path);
	int i = 0;
	while (1) {
		string line;
		getline(datafile, line);
		if (line == "")
			break;
		istringstream iss(line);
		string str_buf;
		while (getline(iss, str_buf, '\t')) {
			vector<string> v;
			data.push_back(v);
			data[i].push_back(str_buf);
		}
		i++;
	}
	datafile.close();
	return data;
}

void File::start() {
	//프로그램 시작 시, 각 디렉토리 생성 & meta.txt 이동
	_mkdir("resource"); _mkdir("user"); _mkdir("book");	//없으면 생성, 있으면 넘어감
	ifstream in("meta.txt");
	if (in.is_open()) {	//처음 실행 시
		ofstream out(".\\resource\\userdata.txt");
		out.close();
		out.open(".\\resource\\meta.txt");
		out << in.rdbuf();
		out.close();
		in.close();
		_unlink("meta.txt");	//배포된 외부의 meta.txt 삭제 (resource 폴더 안으로 이동)
	}
}

vector<vector<string>>File::getAllUsers() {
	//userdata.txt
	//UserData : userID, Name, phoneNum
	ifstream datafile;
	try {
		datafile.open(".\\resource\\userdata.txt");
		if (!datafile.is_open()) {
			throw NotExistFileException("userdata.txt");
		}
		
	}
	catch(exception &e){
		cout << e.what() << endl;
	}
	return  readSplit(".\\resource\\userdata.txt");		//UserData 전체 return (한 행에 한 명씩)
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
		cout << e.what() << endl;
	}

	int i = 0;
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
		i++;
	}
	datafile.close();
	return data;//정보 4개를 저장하는 벡터 return
}

vector<vector<string>>File::getUserData(string id) {
	//[UserID].txt
	//user 예약 정보 : 예약번호/예약날짜/시작시각/종료시각/방번호
	ifstream datafile;
	try {
		datafile.open(".\\user\\" + id + ".txt");
		if (!datafile.is_open()) {
			throw NotExistFileException(id + ".txt");
		}

	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	return readSplit(".\\user\\" + id + ".txt");	//해당 id를 가지는 유저의 예약 정보 전체 저장 벡터 return (한 행에 한 개)
}

vector<vector<string>>File::getBooking(string date) {//예약을 하고자 날짜를 인자로 받습니다
	//[YYYYMMDD].txt
	string ymd = date.substr(0,4) + date.substr(5,2) + date.substr(8,2);//표준형식으로부터 변환
	ifstream datafile;
	datafile.open(".\\book\\" + ymd+ ".txt");
	if (!datafile.is_open()) {//찾아보고 없으면 파일 생성(0으로 초기화)
		ofstream file(".\\book\\" +ymd+".txt");
		for (int i = 0; i < 9; i++) {//방 9개
			for (int j = 0; j < 22; j++) {//30분 단위로 22칸
				file << "0\t";
			}
			file << "\n";
		}
	}
	return readSplit(".\\book\\" + ymd + ".txt"); //해당 날짜의 예약 정보 전체 저장 벡터 return (한 행에 한 스터디룸)
}

void File::addNewUser(vector<string> newUser) {//새로운 user의 이름, 전화번호를 담고 있는 벡터
	//meta.txt 수정
	vector<string> metaData = getMetaData();
	string num = to_string(stoi(metaData[2]) + 1);
	metaData[2] = num;
	ofstream file(".\\resource\\meta.txt");
	file << metaData[0] + "\t" + metaData[1] + "\n" + metaData[2] + "\n" + metaData[3];
	file.close();

	//[UserID].txt 파일 생성(빈 파일)
	file.open(".\\user\\" +num+".txt");
	file.close();

	//userdata.txt 마지막줄 추가
	string user = num + "\t" + newUser[0] + "\t" + newUser[1] + "\n";
	file.open(".\\resource\\userdata.txt", std::ios_base::app);
	file << user;
	file.close();
}

void File::setUserData(string id, vector<vector<string>> data) {//해당 user의 모든 예약 정보를 담은 벡터
	//[UserId].txt
	ofstream file(".\\user\\" + id + ".txt");
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
	string ymd = date.substr(0, 4) + date.substr(5, 2) + date.substr(8, 2);
	ofstream file(".\\book\\" + ymd + ".txt");
	if (!file.is_open()) {//찾아보고 없으면 파일 생성(0으로 초기화)
		ofstream file(".\\book\\" + ymd + ".txt");
		for (int i = 0; i < 9; i++) {//방 9개
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
	vector<string> metaData = getMetaData();
	metaData[3] = to_string(stoi(metaData[3]) + 1);
	file.open(".\\resource\\meta.txt");
	file << metaData[0] + "\t" + metaData[1] + "\n" + metaData[2] + "\n" + metaData[3];
	file.close();
}



