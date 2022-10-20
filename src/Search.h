#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "File.h"
#include "Parsing.h"

using namespace std;

class Search {
public:
    static void searchAll();
    static void searchByName(string name);
    static void searchByNameAndPhone(string name, string phone);
};
