#include "ExceptionClass.h"
#include <iostream>
#include <vector>

using namespace std;

//Ŭ���� ����
const char * CustomException::getError() const {
    return error.c_str();
}
void CustomException::setError(const string &error) {
    this->error = error;
}
const char * CustomException::what() const noexcept {
    return this->getError();
}

CommandException::CommandException(string command) : command(command) {
    this->setError("��ɾ� "+command+"(��)�� �߸��Ǿ����ϴ�.");
}
const string &CommandException::getCommand() const {
    return this->command;
}

ArgumentException::ArgumentException(string str) : str(str) {
    this->setError("���� "+str+"(��)�� �߸��Ǿ����ϴ�.");
}
const string &ArgumentException::getStr() const {
    return this->str;
}

FileException::FileException() {
    this->setError("���Ͽ� ������ �ֽ��ϴ�.");
}
const string &FileException::getFilePath()const {
    return this->filepath;
}
void FileException::setFilePath(const std::string &path) {
    this->filepath = path;
}

UnableCommandException::UnableCommandException(string command, string cmd) : CommandException(command), cmd(cmd) {
    this->setError("���� ���â "+this->cmd+"���� "+this->getCommand()+"��(��) ����� �� ���� ��ɾ��Դϴ�.");
}

WrongCommandException::WrongCommandException(string command) : CommandException(command) {
    this->setError("��ɾ� "+this->getCommand()+"��(��) �������� �ʴ� ��ɾ��Դϴ�.");
}

WrongNumArgumentException::WrongNumArgumentException(string command) : ArgumentException(command) {
    this->setError("��ɾ� "+this->getStr()+"(��)�� ���� �� �ִ� ������ ������ �ٸ��ϴ�.");
}

WrongCharArgumentException::WrongCharArgumentException(string argument, char ch) : ArgumentException(argument), ch(ch) {
    this->setError("�Է� ���� "+this->getStr()+"�� ����� �� ���� ���� \'"+this->ch+"\'(��)�� �����մϴ�.");
}

WrongLengthArgumentException::WrongLengthArgumentException(string argument, string length) : ArgumentException(argument), length(length) {
    this->setError("�Է� ���� "+this->getStr().substr(0, 10)+"�� ��� ������ ���� ���� ["+this->length+"] (��)�� ������ϴ�.");
}

WrongRuleArgumentException::WrongRuleArgumentException(string argument, string rule) : ArgumentException(argument), rule(rule) {
    this->setError("�Է� ���� "+this->getStr()+"(��)�� �ṉ̀�Ģ�� �������� ���մϴ�.\n��Ģ : "+this->rule);
}

NotExistFileException::NotExistFileException(string filepath) {
    this->setFilePath(filepath);
    this->setError("\'"+this->getFilePath()+"\'"+"(��)�� �������� �ʴ� �����Դϴ�.");
}

WrongFormatFileException::WrongFormatFileException(string filepath) {
    this->setFilePath(filepath);
    this->setError("\'"+this->getFilePath()+"\'"+"�� ����� ������ ���Ŀ� ������ �����մϴ�.");
}

NotExistMetaFileException::NotExistMetaFileException(string filepath) : NotExistFileException(filepath) { }

WrongFormatMetaFileException::WrongFormatMetaFileException(string filepath) : WrongFormatFileException(filepath) { }


//�޼ҵ� ����
void exceptionMannager(exception& e){
    string exceptionName = typeid(e).name();
    vector<string> helpExceptionList = { typeid(CommandException).name(), typeid(UnableCommandException).name(), typeid(WrongCommandException).name()};
    vector<string> exitExceptionList = { typeid(FileException).name(), typeid(NotExistMetaFileException).name(), typeid(WrongFormatMetaFileException).name(), typeid(NotExistFileException).name(), typeid(WrongFormatFileException).name()};
    cout << "[����] " << exceptionName << " ���ܰ� �߻��Ͽ����ϴ�." << endl;
    cout << e.what() << endl;  // ���� ����

    auto itHelp = find(helpExceptionList.begin(), helpExceptionList.end(), exceptionName);
    if (itHelp != helpExceptionList.end()){
        cout<<"������ ����մϴ�."<<endl;
        // help ȣ��
    }
    auto itExit = find(exitExceptionList.begin(), exitExceptionList.end(), exceptionName);
    if (itExit != exitExceptionList.end()){
        cout<<"���α׷��� �����մϴ�."<<endl;
        exit(EXIT_FAILURE);
    }
}