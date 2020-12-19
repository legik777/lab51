// Copyright 2020 Andreytorix

#ifndef PARSER_STUDENTS_H
#define PARSER_STUDENTS_H


#include <any>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"

using namespace std;
using namespace nlohmann;

struct student {
	string name;
	any group;
	any avg;
	any debt;
};
auto get_name(const json& j) -> std::string;
auto get_group(const json& j) -> std::any;
auto get_avg(const json& j) -> any;
auto getDebt(const json& j) ->any;
void from_Json(const json& j, student& s);
string gettypegroup(vector <student> st, int n);
string gettypeavg(vector <student> st, int n);
string gettypedebt(vector <student> st, int n);
vector<student> parseJS(json js);

#endif  
