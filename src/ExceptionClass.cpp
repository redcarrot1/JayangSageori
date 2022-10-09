#include "ExceptionClass.h"
#include <iostream>
#include <vector>

using namespace std;

//클래스 정의
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
    this->setError("명령어 "+command+"(이)가 잘못되었습니다.");
}
const string &CommandException::getCommand() const {
    return this->command;
}

ArgumentException::ArgumentException(string str) : str(str) {
    this->setError("인자 "+str+"(이)가 잘못되었습니다.");
}
const string &ArgumentException::getStr() const {
    return this->str;
}

FileException::FileException() {
    this->setError("파일에 문제가 있습니다.");
}
const string &FileException::getFilePath()const {
    return this->filepath;
}
void FileException::setFilePath(const std::string &path) {
    this->filepath = path;
}

UnableCommandException::UnableCommandException(string command, string cmd) : CommandException(command), cmd(cmd) {
    this->setError("현재 명령창 "+this->cmd+"에서 "+this->getCommand()+"은(는) 사용할 수 없는 명령어입니다.");
}

WrongCommandException::WrongCommandException(string command) : CommandException(command) {
    this->setError("명령어 "+this->getCommand()+"은(는) 존재하지 않는 명령어입니다.");
}

WrongNumArgumentException::WrongNumArgumentException(string command) : ArgumentException(command) {
    this->setError("명령어 "+this->getStr()+"(이)가 가질 수 있는 인자의 개수와 다릅니다.");
}

WrongCharArgumentException::WrongCharArgumentException(string argument, char ch) : ArgumentException(argument), ch(ch) {
    this->setError("입력 인자 "+this->getStr()+"에 사용할 수 없는 문자 \'"+this->ch+"\'(이)가 존재합니다.");
}

WrongLengthArgumentException::WrongLengthArgumentException(string argument, string length) : ArgumentException(argument), length(length) {
    this->setError("입력 인자 "+this->getStr().substr(0, 10)+"가 허용 가능한 길이 범위 ["+this->length+"] (을)를 벗어났습니다.");
}

WrongRuleArgumentException::WrongRuleArgumentException(string argument, string rule) : ArgumentException(argument), rule(rule) {
    this->setError("입력 인자 "+this->getStr()+"(이)가 의미규칙을 만족하지 못합니다.\n규칙 : "+this->rule);
}

NotExistFileException::NotExistFileException(string filepath) {
    this->setFilePath(filepath);
    this->setError("\'"+this->getFilePath()+"\'"+"(은)는 존재하지 않는 파일입니다.");
}

WrongFormatFileException::WrongFormatFileException(string filepath) {
    this->setFilePath(filepath);
    this->setError("\'"+this->getFilePath()+"\'"+"에 저장된 내용의 형식에 문제가 존재합니다.");
}

NotExistMetaFileException::NotExistMetaFileException(string filepath) : NotExistFileException(filepath) { }

WrongFormatMetaFileException::WrongFormatMetaFileException(string filepath) : WrongFormatFileException(filepath) { }


//메소드 정의
void exceptionMannager(exception& e){
    string exceptionName = typeid(e).name();
    vector<string> helpExceptionList = { typeid(CommandException).name(), typeid(UnableCommandException).name(), typeid(WrongCommandException).name()};
    vector<string> exitExceptionList = { typeid(FileException).name(), typeid(NotExistMetaFileException).name(), typeid(WrongFormatMetaFileException).name(), typeid(NotExistFileException).name(), typeid(WrongFormatFileException).name()};
    cout << "[오류] " << exceptionName << " 예외가 발생하였습니다." << endl;
    cout << e.what() << endl;  // 세부 정보

    auto itHelp = find(helpExceptionList.begin(), helpExceptionList.end(), exceptionName);
    if (itHelp != helpExceptionList.end()){
        cout<<"도움말을 출력합니다."<<endl;
        // help 호출
    }
    auto itExit = find(exitExceptionList.begin(), exitExceptionList.end(), exceptionName);
    if (itExit != exitExceptionList.end()){
        cout<<"프로그램을 종료합니다."<<endl;
        exit(EXIT_FAILURE);
    }
}