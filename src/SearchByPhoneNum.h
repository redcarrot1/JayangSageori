#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <ctime>

//#include "File.h"
#include "Parsing.h"
#include "ExceptionClass.h"
#include "File.h"

using std::cout;
using std::string;
using std::vector;

class SearchByPhoneNum
{
public:
	SearchByPhoneNum() = default;
	void search(string phoneNum, string name);
};

