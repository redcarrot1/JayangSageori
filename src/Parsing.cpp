#include "Parsing.h"

#include <iostream>
using namespace std;
vector<string> Parsing::split(vector<string> line)
{
	int start = 0, end = 0;
	string target = line.at(0);
	while (true) {
		if (target[end] == '\t' || target[end] == ' ') {
			if (target[start] == '\t' || target[start] == ' '){
			//������ �������� 2���� ���� ��� �ϳ��� ����
			}
			else
			{
				result.push_back(target.substr(start, end - start));
			}
			start = end + 1;
		}

		if (end++ == target.length()-1) {
			if (target[start-1] == '\t' || target[start-1] == ' ') {
				break;
			}
			else
			{
				result.push_back(target.substr(start, end - start));
			}
			break;
		}
	}
	return result;
}