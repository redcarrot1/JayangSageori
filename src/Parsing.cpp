#include "Parsing.h"

#include <iostream>
using namespace std;
vector<string> Parsing::split(string line)
{
	vector<string> result;
	int start = 0, end = 0;
	if (line.length() == 0) {
		return result;
	}
	while (true) {
		if (end == line.length() - 1) {//����� or �����ؾ� �� ��
			if (line[start] == '\t' || line[start] == ' ') {
				break;
			}
			else {
				result.push_back(line.substr(start, end - start+1));//end�� ������ �ƴ� ���ڸ� ����Ű������
				break;
			}
		}
		if (line[end] == '\t' || line[end] == ' ') {
			if (line[start] == '\t' || line[start] == ' '){
			//������ �������� 2���� ���� ��� �ϳ��� ����
			}
			else
			{
				result.push_back(line.substr(start, end - start));
			}
			start = end + 1;
		}
		end++;
	}
	return result;
}