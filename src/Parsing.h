#pragma once

#include <vector>
#include <string>

using namespace std;

class Parsing
{
private:
	vector<string> result;

public:
	Parsing() = default;
	vector<string>  split(vector<string> line);
	
};

