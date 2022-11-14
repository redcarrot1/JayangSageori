#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "WindowEnum.h"

using std::string;
using std::vector;

/* ���ڷ� ������ ������ ��Ҹ� ǥ���������� ��ȯ�ϴ� �޼ҵ带 ������ Ŭ���� */
class Convert2Standard {
private:
    static vector<string> split(string s, string pattern);     // ������ ó���� �����ϰ� �� �� �ֵ��� �ϴ� split �޼ҵ�
    static string stdPhoneNum(string phoneNum);  //��ȭ��ȣ�� ǥ���������� �ٲٴ� �޼ҵ�
    static string stdName(string name);      //�̸��� ǥ���������� �ٲٴ� �޼ҵ�
    static string stdDate(string date);      //��¥�� ǥ���������� �ٲٴ� �޼ҵ�
    static string stdTime(string time);      //�ð��� ǥ���������� �ٲٴ� �޼ҵ�
    static string correctTime(string time);  //�ð� ���� �޼ҵ�
    static string stdRoomID(string roomID);    //�� ��ȣ�� ǥ���������� �ٲٴ� �޼ҵ�
    static string stdPersonNum(string person);      //�����ο��� ǥ���������� �ٲٴ� �޼ҵ�
public:
    Convert2Standard() = delete;
    static string stdCommand(string command, Window window);
    static vector<string> convertSign(vector<string> argv);    // ȸ������, �α��� string name, string phoneNum
    static vector<string> convertBook(vector<string> argv);    // �����ϱ� string date, string roomID, string startTime, string endTime
    static vector<string> convertList(vector<string> argv);    // ���� ���� Ȯ�� string date
    static vector<string> convertSearch(vector<string> argv);  // ȸ�� ���� �˻� vector<string> argument (1���ϼ���, 2���ϼ���)
};