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

struct student {
std::string name;
std::any group;
std::any avg;
std::any debt;
};
auto get_name(const nlohmann::json& j)->std::string;
auto get_group(const nlohmann::json& j)->std::any;
auto get_avg(const nlohmann::json& j)->std::any;
auto getDebt(const nlohmann::json& j)->std::any;
void from_Json(const nlohmann::json& j, student& s);
std::string gettypegroup(std::vector <student> st, int n);
std::string gettypeavg(std::vector <student> st, int n);
std::string gettypedebt(std::vector <student> st, int n);
std::vector<student> parseJS(nlohmann::json js);

#endif  
