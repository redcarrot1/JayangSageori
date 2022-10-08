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
		if (end == line.length() - 1) {//공백류 or 저장해야 할 값
			if (line[start] == '\t' || line[start] == ' ') {
				break;
			}
			else {
				result.push_back(line.substr(start, end - start+1));//end가 공백이 아닌 글자를 가리키고있음
				break;
			}
		}
		if (line[end] == '\t' || line[end] == ' ') {
			if (line[start] == '\t' || line[start] == ' '){
			//공백이 연속으로 2개가 들어온 경우 하나로 간주
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