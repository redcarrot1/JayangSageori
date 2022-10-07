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
			//공백이 연속으로 2개가 들어온 경우 하나로 간주
				start = end + 1;
			}
			else {
				result.push_back(target.substr(start, end - start));
				start = end + 1;
			}
		}

		if (end++ == target.length()-1) {
			result.push_back(target.substr(start, end - start));
			cout << end << '\t' << result.size();
			break;
		}
	}
	return result;
}
