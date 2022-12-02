#include "File.h"

using namespace std;
namespace fs = filesystem;

void File::start() {
    //프로그램 시작 시, 각 디렉토리 생성 & meta.txt 이동
    if (!fs::exists(rootPath + "book")) { fs::create_directory(rootPath + "book"); }
    if (!fs::exists(rootPath + "user")) { fs::create_directory(rootPath + "user"); }
    if (!fs::exists(rootPath + "resource")) { fs::create_directory(rootPath + "resource"); }
    if (!fs::exists(rootPath + "resource/userdata.txt")) { ofstream(rootPath + "resource/userdata.txt"); }
    if (!fs::exists(rootPath + "resource/resernum.txt")) {//resernum 초기화
        ofstream(rootPath + "resource/resernum.txt");
        ofstream datafile;
        datafile.open(rootPath + "resource/resernum.txt");
        datafile << "0   0\n"; //예약인원 사용자Id
        datafile.close();
    }
    if (fs::exists(rootPath + "meta.txt")) {
        if (!fs::exists(rootPath + "resource/meta.txt")) {
            fs::copy(rootPath + "meta.txt", rootPath + "resource/meta.txt");
        }
        fs::remove(rootPath + "meta.txt");
    }

    else {
        try {
            cout << "meta.txt 이(가) 존재하는지 확인합니다.";
            if (!fs::exists(rootPath + "resource/meta.txt")) {
                cout << endl;
                throw NotExistMetaFileException();
            }
            else cout << " ...성공" << endl;
        }
        catch (exception &e) {
            exceptionMannager(e);
        }
        try {
            cout << "meta.txt 이(가) 올바른 형식을 만족하는지 검증합니다." << endl;
            ifstream datafile;
            datafile.open(rootPath + "resource/meta.txt");

            vector<string> data;
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
            if (data.size() != 13) throw WrongFormatMetaFileException();
            // 1. 이름 검증
            if (data[0].length() < 2 || 30 < data[0].length()) throw WrongFormatMetaFileException();
            for (char &ch: data[0]) {
                if (!isalpha(ch)) throw WrongFormatMetaFileException();
            }

            // 2. 전화번호 검증
            if (data[1].length() < 7 || 20 < data[1].length()) throw WrongFormatMetaFileException();
            for (char &ch: data[1]) {
                if (!isdigit(ch)) throw WrongFormatMetaFileException();
            }
            // 3. 회원 수, 예약 수 검증
            for (char &ch: data[2]) {
                if (!isdigit(ch)) throw WrongFormatMetaFileException();
            }
            for (char &ch: data[3]) {
                if (!isdigit(ch)) throw WrongFormatMetaFileException();
            }
            //4. 방 수용 인원 수 검증
            for (int i = 0; i < data.size() - 4; i++) {
                for (char &ch: data[i + 4]) {
                    if (!isdigit(ch)) throw WrongFormatMetaFileException();
                }
            }
        } catch (exception &e) {
            exceptionMannager(e);
        }
    }
}

string File::getId(string reserveId) {
    //resource/resernum.txt
    ifstream datafile(rootPath + "resource/resernum.txt");
    vector<vector<string>> vec;
    string line;

    while (1) {
        getline(datafile, line);
        if (line == "") break;
        istringstream iss(line);
        string str_buf;
        vector<string> v;
        while (getline(iss, str_buf, '\t')) {
            v.push_back(str_buf);
        }
        vec.push_back(v);
    }
    datafile.close();
    return vec[stoi(reserveId)][1];
}

vector<vector<string>> File::getAllUsers() {
    //userdata.txt
    //UserData : userID, Name, phoneNum
    vector<vector<string>> data;
    ifstream datafile;
    try {
        datafile.open(rootPath + "resource/userdata.txt");
        if (!datafile.is_open())
            throw NotExistFileException("userdata.txt");
    }
    catch (exception &e) {
        exceptionMannager(e);
    }
    string line;
    while (1) {
        getline(datafile, line);
        if (line == "") break;
        istringstream iss(line);
        string str_buf;
        vector<string> v;
        while (getline(iss, str_buf, '\t')) {
            v.push_back(str_buf);
        }
        data.push_back(v);
    }
    datafile.close();
    return data;        //UserData 전체 return (한 행에 한 명씩)
}

User File::getAdmin() {
    vector<string> metaData = getMetaData();
    return {metaData[0], metaData[1]};
}

vector<string> File::getMetaData() {
    //meta.txt
    //관리자 이름, 전화번호, 현재 회원 수, 예약 번호, 방 별 수용 인원
    vector<string> data;
    ifstream datafile;
    try {
        datafile.open(rootPath + "resource/meta.txt");
        if (!datafile.is_open()) throw NotExistMetaFileException();
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
    return data;//정보 5 종류를 저장하는 벡터 return
}

vector<vector<string>> File::getUserData(string id) {
    //[UserID].txt
    //user 예약 정보 : 예약번호/예약날짜/시작시각/종료시각/방번호
    vector<vector<string>> data;
    ifstream datafile;
    try {
        datafile.open(rootPath + "user/" + id + ".txt");
        if (!datafile.is_open()) throw NotExistFileException(id + ".txt");
    }
    catch (exception &e) {
        exceptionMannager(e);
    }
    string line;
    while (1) {
        getline(datafile, line);
        if (line == "") break;
        istringstream iss(line);
        string str_buf;
        vector<string> v;
        while (getline(iss, str_buf, '\t')) {
            v.push_back(str_buf);
        }
        data.push_back(v);
    }
    datafile.close();
    return data;    //해당 id를 가지는 유저의 예약 정보 전체 저장 벡터 return (한 행에 한 개)
}

vector<vector<string>> File::getBooking(string date) {//예약을 하고자 날짜를 인자로 받습니다
    //[YYYYMMDD].txt
    date.erase(remove(date.begin(), date.end(), '-'), date.end());//표준형식으로부터 변환
    ofstream file;
    if (!fs::exists(rootPath + "book/" + date + ".txt")) {//찾아보고 없으면 파일 생성(0으로 초기화)
        file.open(rootPath + "book/" + date + ".txt");
        for (int i = 0; i < 10; i++) {//방 9개
            for (int j = 0; j < 22; j++) {//30분 단위로 22칸
                file << "0\t";
            }
            file << "\n";
        }
        file.close();
    }
    ifstream datafile(rootPath + "book/" + date + ".txt");
    vector<vector<string>> data;
    string line;
    while (1) {
        getline(datafile, line);
        if (line == "") break;
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

string File::getReserNum(string reserveId) {
    //resource/resernum.txt
    ifstream datafile(rootPath + "resource/resernum.txt");
    vector<vector<string>> vec;
    string line;

    while (1) {
        getline(datafile, line);
        if (line == "") break;
        istringstream iss(line);
        string str_buf;
        vector<string> v;
        while (getline(iss, str_buf, '\t')) {
            v.push_back(str_buf);
        }
        vec.push_back(v);
    }
    datafile.close();

    //reserveId와 일치하는 예약 인원 return
    return vec[stoi(reserveId)][0];
}

void File::addNewUser(vector<string> newUser) { //새로운 user의 이름, 전화번호를 담고 있는 벡터
    ofstream file;
    vector<string> metaData = getMetaData();
    string num = "";
    //meta.txt 수정
    try {    //metadata 파일 format 확인
        if (metaData.size() != 13) throw WrongFormatMetaFileException();
        num = to_string(stoi(metaData[2]) + 1);
        metaData[2] = num;
    }
    catch (exception &e) {
        exceptionMannager(e);
    }

    try {    //metadata 파일 존재 확인
        file.open(rootPath + "resource/meta.txt");
        if (!file.is_open()) throw NotExistMetaFileException();
        file << metaData[0] + "\t" + metaData[1] + "\n" + metaData[2] + "\n" + metaData[3] + "\n";
        for (int i = 4; i < 13; ++i) {
            file << metaData[i] << "\t";
        }
        file << "\n";
        file.close();
    }
    catch (exception &e) {
        exceptionMannager(e);
    }

    //[UserID].txt 파일 생성(빈 파일)
    file.open(rootPath + "user/" + num + ".txt");
    file.close();

    //userdata.txt 마지막줄 추가
    try {
        string user = num + "\t" + newUser[0] + "\t" + newUser[1] + "\n";
        file.open(rootPath + "resource/userdata.txt", std::ios_base::app);
        if (!file.is_open()) throw NotExistFileException("userdata.txt");
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
        file.open(rootPath + "user/" + id + ".txt");
        if (!file.is_open()) throw NotExistFileException(id + ".txt");
    }
    catch (exception &e) {
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

void File::setBooking(string date, vector<vector<string>> data) {
    //[YYYYMMDD].txt
    //해당 날짜의 예약 정보 write
    date.erase(remove(date.begin(), date.end(), '-'), date.end());//표준형식으로부터 변환
    ofstream file(rootPath + "book/" + date + ".txt");
    if (!file.is_open()) {//찾아보고 없으면 파일 생성(0으로 초기화)
        ofstream file(rootPath + "book/" + date + ".txt");
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
        if (metaData.size() != 13) throw WrongFormatMetaFileException();
        metaData[3] = to_string(stoi(metaData[3]) + 1);
    }
    catch (exception &e) {
        exceptionMannager(e);
    }

    try {
        file.open(rootPath + "resource/meta.txt");
        if (!file.is_open()) throw NotExistMetaFileException();
        file << metaData[0] + "\t" + metaData[1] + "\n" + metaData[2] + "\n" + metaData[3] + "\n";
        for (int i = 4; i < 13; ++i) {
            file << metaData[i] << "\t";
        }
        file << "\n";
        file.close();
    }
    catch (exception &e) {
        exceptionMannager(e);
    }
}

string File::getRoomCapacity(string roomNum) {
    return getMetaData()[3 + stoi(roomNum)];
}

void File::addReserNum(string num, string userId) {
    //resource/resernum.txt
    ofstream file;
    file.open(rootPath + "resource/resernum.txt", ios::out | ios::app);
    file.seekp(-1, ios::end);
    file << num << "\t" << userId << "\n";
    file.close();
}

void File::changeStudyRoom(vector<string> changeDate) {//reserveId, [date, time, changeStudyRoomId]가 담긴 벡터
    string user_id = getId(changeDate[0]);
    vector<vector<string>> data;
    int target;

    data = getUserData(user_id);

    for (target = 0; target < data.size(); target++) {
        if (data[target][0] == changeDate[0]) { // date & 시작 시간 비교
            break;
        }
    }

    data[target] = changeDate;

    setUserData(user_id, data);
}