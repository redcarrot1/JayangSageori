#pragma once

#include <exception>
#include <string>
#include <iostream>

using std::string;
using std::exception;

/*클래스 선언*/
class CustomException : public exception {
private:
    string error = "default error Message";
public:
    const char * getError() const;
    void setError(const string &error);
    const char * what() const noexcept override;
};

// 1단계 상속
class CommandException : public CustomException {   // 생성자 인자 string 1개로 정의
private:
    string command;
public:
    CommandException(string command);
    const string &getCommand() const;
};

class ArgumentException : public CustomException {
private:
    string str;
public:
    ArgumentException(string str);
    const string &getStr() const;
};

class FileException : public CustomException {
private:
    string filepath = "filepath"; //기본값
public:
    FileException();
    const string &getFilePath() const;
    void setFilePath(const string &path);
};

// 2단계 상속
class UnableCommandException : public CommandException {
private:
    string cmd;
public:
    UnableCommandException(string command, string cmd);
};

class WrongCommandException : public CommandException {
public:
    WrongCommandException(string command);
};

class WrongNumArgumentException : public ArgumentException {
public:
    WrongNumArgumentException(string command);
};

class WrongCharArgumentException : public ArgumentException {
private:
    char ch;
public:
    WrongCharArgumentException(string argument, char ch);
};

class WrongLengthArgumentException : public ArgumentException {
private:
    string length;
public:
    WrongLengthArgumentException(string argument, string length);
};

class WrongRuleArgumentException : public ArgumentException{
private:
    string rule;
public:
    WrongRuleArgumentException(string argument, string rule);
};

class NotExistFileException : public FileException {
public:
    NotExistFileException(string filepath);
};

class WrongFormatFileException : public FileException {
public:
    WrongFormatFileException(string filepath);
};

// 3단계 상속 (File)

class NotExistMetaFileException : public NotExistFileException {
public:
    NotExistMetaFileException(string filepath = "meta.txt");
};

class WrongFormatMetaFileException : public WrongFormatFileException {
public:
    WrongFormatMetaFileException(string filepath = "meta.txt");
};

/*메소드 선언*/
void exceptionMannager(exception& e);
//void exceptionMannager(string exceptionName);