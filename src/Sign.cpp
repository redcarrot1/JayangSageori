#include "Sign.h"
#include "File.h"
#include<string>


using namespace std;


//회원가입 메소드
void SignUp::signup(vector<string> v1) {
	
	this->name = v1[0];
	this->phNum = v1[1];
	vector<vector<string>> v2= File::getAllUsers();
	for (int i = 0; i < v2.size(); i++)
	{
		for (int j = 0; j < v2[i].size(); j++)
		{
			if (this->phNum == v2[i][j])
			{
				throw WrongRuleArgumentException(v2[i][j], "이미 회원가입이 되어있습니다.\n");
			}
		}
	
	}
	File::addNewUser(v1) ;
	cout << "회원가입이 완료되었습니다.\n";
	cout << "사용자 이름: " << this->name << "\n";
	cout << "사용자 전화번호: " << this->phNum << "\n";

	}




//로그인 메소드
void SignIn::signin(vector <string> v1) {
	this->name = v1[0];
	this->phNum = v1[1];
	vector<vector<string>> v2 = File::getAllUsers();
	vector<string> admin = File::getMetaData();
	for (int i = 0; i < v2.size(); i++)
	{
		for (int j = 0; j < v2[i].size(); j++)
		{
			if (this->phNum == v2[i][j] && this->name == v2[i][j])
			{
				cout << "사용자로 로그인 되었습니다.";
			}
			else if (admin[0] == v2[i][j] && admin[1] == v2[i][j])
			{
				cout << "관리자로 로그인 되었습니다.";
			}
			else
			{
				throw WrongRuleArgumentException("회원정보", "존재하지 않는 회원입니다.\n");
			}
		}

	}

	
	}
