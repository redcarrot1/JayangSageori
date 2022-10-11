#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "File.h"
#include "Parsing.h"

using std::cout;
using std::string;
using std::vector;

class SearchByName
{
public:
	SearchByName() = default;
	void search(string name);
};

