#include "File.h"

using namespace std;
namespace fs = filesystem;

void File::start() {
    //���α׷� ���� ��, �� ���丮 ���� & meta.txt �̵�
    if (!fs::exists(rootPath + "book")) { fs::create_directory(rootPath + "book"); }
    if (!fs::exists(rootPath + "user")) { fs::create_directory(rootPath + "user"); }
    if (!fs::exists(rootPath + "resource")) { fs::create_directory(rootPath + "resource"); }
    if (!fs::exists(rootPath + "resource/userdata.txt")) { ofstream(rootPath + "resource/userdata.txt"); }
    if (!fs::exists(rootPath + "resource/resernum.txt")) {//resernum �ʱ�ȭ
        ofstream(rootPath + "resource/resernum.txt");
        ofstream datafile;
        datafile.open(rootPath + "resource/resernum.txt");
        datafile << "0   0\n"; //�����ο� �����Id
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
            cout << "meta.txt ��(��) �����ϴ��� Ȯ���մϴ�.";
            if (!fs::exists(rootPath + "resource/meta.txt")) {
                cout << endl;
                throw NotExistMetaFileException();
            }
            else cout << " ...����" << endl;
        }
        catch (exception &e) {
            exceptionMannager(e);
        }
        try {
            cout << "meta.txt ��(��) �ùٸ� ������ �����ϴ��� �����մϴ�." << endl;
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
            // 1. �̸� ����
            if (data[0].length() < 2 || 30 < data[0].length()) throw WrongFormatMetaFileException();
            for (char &ch: data[0]) {
                if (!isalpha(ch)) throw WrongFormatMetaFileException();
            }

            // 2. ��ȭ��ȣ ����
            if (data[1].length() < 7 || 20 < data[1].length()) throw WrongFormatMetaFileException();
            for (char &ch: data[1]) {
                if (!isdigit(ch)) throw WrongFormatMetaFileException();
            }
            // 3. ȸ�� ��, ���� �� ����
            for (char &ch: data[2]) {
                if (!isdigit(ch)) throw WrongFormatMetaFileException();
            }
            for (char &ch: data[3]) {
                if (!isdigit(ch)) throw WrongFormatMetaFileException();
            }
            //4. �� ���� �ο� �� ����
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
    return data;        //UserData ��ü return (�� �࿡ �� ��)
}

User File::getAdmin() {
    vector<string> metaData = getMetaData();
    return {metaData[0], metaData[1]};
}

vector<string> File::getMetaData() {
    //meta.txt
    //������ �̸�, ��ȭ��ȣ, ���� ȸ�� ��, ���� ��ȣ, �� �� ���� �ο�
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
    return data;//���� 5 ������ �����ϴ� ���� return
}

vector<vector<string>> File::getUserData(string id) {
    //[UserID].txt
    //user ���� ���� : �����ȣ/���೯¥/���۽ð�/����ð�/���ȣ
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
    return data;    //�ش� id�� ������ ������ ���� ���� ��ü ���� ���� return (�� �࿡ �� ��)
}

vector<vector<string>> File::getBooking(string date) {//������ �ϰ��� ��¥�� ���ڷ� �޽��ϴ�
    //[YYYYMMDD].txt
    date.erase(remove(date.begin(), date.end(), '-'), date.end());//ǥ���������κ��� ��ȯ
    ofstream file;
    if (!fs::exists(rootPath + "book/" + date + ".txt")) {//ã�ƺ��� ������ ���� ����(0���� �ʱ�ȭ)
        file.open(rootPath + "book/" + date + ".txt");
        for (int i = 0; i < 10; i++) {//�� 9��
            for (int j = 0; j < 22; j++) {//30�� ������ 22ĭ
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
    return data; //�ش� ��¥�� ���� ���� ��ü ���� ���� return (�� �࿡ �� ���͵��)
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

    //reserveId�� ��ġ�ϴ� ���� �ο� return
    return vec[stoi(reserveId)][0];
}

void File::addNewUser(vector<string> newUser) { //���ο� user�� �̸�, ��ȭ��ȣ�� ��� �ִ� ����
    ofstream file;
    vector<string> metaData = getMetaData();
    string num = "";
    //meta.txt ����
    try {    //metadata ���� format Ȯ��
        if (metaData.size() != 13) throw WrongFormatMetaFileException();
        num = to_string(stoi(metaData[2]) + 1);
        metaData[2] = num;
    }
    catch (exception &e) {
        exceptionMannager(e);
    }

    try {    //metadata ���� ���� Ȯ��
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

    //[UserID].txt ���� ����(�� ����)
    file.open(rootPath + "user/" + num + ".txt");
    file.close();

    //userdata.txt �������� �߰�
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

void File::setUserData(string id, vector<vector<string>> data) {//�ش� user�� ��� ���� ������ ���� ����
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
    //�ش� ��¥�� ���� ���� write
    date.erase(remove(date.begin(), date.end(), '-'), date.end());//ǥ���������κ��� ��ȯ
    ofstream file(rootPath + "book/" + date + ".txt");
    if (!file.is_open()) {//ã�ƺ��� ������ ���� ����(0���� �ʱ�ȭ)
        ofstream file(rootPath + "book/" + date + ".txt");
        for (int i = 0; i < 10; i++) {//�� 9��
            for (int j = 0; j < 22; j++) {//30�� ������ 22ĭ
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

    //meta �������� ������ ���� ��ȣ ����
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

void File::changeStudyRoom(vector<string> changeDate) {//reserveId, [date, time, changeStudyRoomId]�� ��� ����
    string user_id = getId(changeDate[0]);
    vector<vector<string>> data;
    int target;

    data = getUserData(user_id);

    for (target = 0; target < data.size(); target++) {
        if (data[target][0] == changeDate[0]) { // date & ���� �ð� ��
            break;
        }
    }

    data[target] = changeDate;

    setUserData(user_id, data);
}