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
		if (line[end] == '\t' || line[end] == ' ') {
			if (start == end) {
				result.push_back("");
			}
			else {
				result.push_back(line.substr(start, end - start));
			}

			if (end == line.length() - 1) {
				break;
			}

			start = end + 1;
		}
		else if (end == line.length() - 1) {
			result.push_back(line.substr(start, end - start + 1));
			break;
		}
		end++;
	}
	return result;
}