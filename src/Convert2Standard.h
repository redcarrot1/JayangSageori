#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "WindowEnum.h"

using std::string;
using std::vector;

/* 인자로 전달한 데이터 요소를 표준형식으로 변환하는 메소드를 가지는 클래스 */
class Convert2Standard {
private:
    static vector<string> split(string s, string pattern);     // 구분자 처리를 간편하게 할 수 있도록 하는 split 메소드
    static string stdPhoneNum(string phoneNum);  //전화번호를 표준형식으로 바꾸는 메소드
    static string stdName(string name);      //이름을 표준형식으로 바꾸는 메소드
    static string stdDate(string date);      //날짜를 표준형식으로 바꾸는 메소드
    static string stdTime(string time);      //시간을 표준형식으로 바꾸는 메소드
    static string correctTime(string time);  //시간 보정 메소드
    static string stdRoomID(string roomID);    //방 번호를 표준형식으로 바꾸는 메소드
    static string stdPersonNum(string person);      //예약인원을 표준형식으로 바꾸는 메소드
public:
    Convert2Standard() = delete;
    static string stdCommand(string command, Window window);
    static vector<string> convertSign(vector<string> argv);    // 회원가입, 로그인 string name, string phoneNum
    static vector<string> convertBook(vector<string> argv);    // 예약하기 string date, string roomID, string startTime, string endTime
    static vector<string> convertList(vector<string> argv);    // 예약 상태 확인 string date
    static vector<string> convertSearch(vector<string> argv);  // 회원 정보 검색 vector<string> argument (1개일수도, 2개일수도)
};