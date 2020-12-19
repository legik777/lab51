// Copyright 2020 Andreytorix

#include "../include/student.h"


auto get_name(const nlohmann::json& j) -> std::string {
    return j.get<std::string>();
}
auto get_group(const nlohmann::json& j) -> std::any {
    if (j.is_string())
        return j.get<std::string>();
    else
        return j.get<size_t>();
}

auto get_avg(const nlohmann::json& j) -> std::any {
    if (j.is_null())
        return nullptr;
    else if (j.is_string())
        return j.get<std::string>();
    else if (j.is_number_float())
        return j.get<double>();
    else
        return j.get<size_t>();
}

auto getDebt(const nlohmann::json& j) ->std::any {
    if (j.is_null()) {
        return nullptr;
    }
    else if (j.is_string()) {
        return j.get<std::string>();
    }
    else {
        return j.get<std::vector<std::string>>();
    }
}

void from_Json(const nlohmann::json& j, student& s) {

    s.name = get_name(j.at("name"));
    s.group = get_group(j.at("group"));
    s.avg = get_avg(j.at("avg"));
    s.debt = getDebt(j.at("debt"));
}
std::string gettypegroup(std::vector <student> st, int n) {
    if (st[n].group.type().name() == typeid (std::string).name())
    {
        return std::any_cast <std::string> (st[n].group);

    }
    else if (st[n].group.type().name() == typeid (unsigned int).name()) {
        return std::to_string(std::any_cast <unsigned int> (st[n].group));
    }
    else {
        return "null";
    }
}

std::string gettypeavg(std::vector <student> st, int n) {
    if (st[n].avg.type().name() == typeid (std::string).name())
    {
        return std::any_cast <std::string> (st[n].avg);
    }
    else if (st[n].avg.type().name() == typeid (unsigned int).name()) {
        return std::to_string(std::any_cast <unsigned int> (st[n].avg));


    }
    else if (st[n].avg.type().name() == typeid (double).name()) {
        return std::to_string(std::any_cast <double> (st[n].avg));
    }
    else {
        return "null";
    }
}

std::string gettypedebt(std::vector <student> st, int n) {
    if (st[n].debt.type().name() == typeid (nullptr_t).name()) {
        return "null";
    }
    if (st[n].debt.type().name() == typeid (std::string).name())
    {
        return std::any_cast <std::string> (st[n].debt);
    }
    else {
        return  std::to_string(std::any_cast<std::vector<std::string>>(st[n].debt).size()) + " items";
    }
}

std::vector<student> parseJS(nlohmann::json js) {
    int length = js["_meta"]["count"];

    int checkLength = 0;
    for (nlohmann::json::iterator i = js["items"].begin(); i != js["items"].end(); i++) {
        checkLength++;
    }

    if (length != checkLength) {
        std::cout << "_meta: count != items.count" << std::endl;
        throw new std::runtime_error("meta: count != items.count");
    }


    std::vector<student> students;

    std::cout << "|" << std::setw(18) << std::left << " name" << "|" << std::setw(8)
        << " group" << "|" << std::setw(8) << " avg" << "|" << std::setw(18) << " dept" << "|" << std::endl;
    std::string stemp = "|------------------|--------|--------|------------------|";
    std::cout << stemp << std::endl;
    for (int i = 0; i < length; i++) {
        student p;

        from_Json((js["items"][i]), p);
        students.push_back(p);
    }


    for (int i = 0; i < length; i++) {
        std::cout << "|" << std::setw(18) << std::left << students[i].name << "|" << std::setw(8)
            << gettypegroup(students, i) << "|" << std::setw(8) << gettypeavg(students, i) << "|" << std::setw(18) << gettypedebt(students, i) << "|" << std::endl;
        std::cout << stemp << std::endl;
    }
    return students;
}

