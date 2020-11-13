// Copyright 2020 mrmamongo
//
// Created by lamp on 09.11.2020.
//
#pragma once

#include <gtest/gtest.h>
#include "../include/table.h"

TEST(Student_Test, EmptyIndex){
string j_string =\
      R"({"name": "Ivanov Petr", "group": "1", "avg": "4.25", "debt": null})";
Student emptyStudent((Json::parse(j_string));

EXPECT_EQ(emptyStudent.imp->GetType(""), Null);
EXPECT_EQ(std::any_cast<std::nullptr_t>(emptyStudent.imp->GetField("")), \
      nullptr);
}

TEST(Student_Test, ParseFromString){
string j_string =\
      R"({"name": "Ivanov Petr", "group": "1", "avg": "4.25", "debt": null})";
Json j = Json::parse(j_string);
Student Petr(j);
EXPECT_TRUE(Petr.imp->GetType(name) == String);
EXPECT_TRUE(Petr.imp->GetType(group) ==  String);
EXPECT_TRUE(Petr.imp->GetType(avg) == String);
EXPECT_TRUE(Petr.imp->GetType(debt) == Null);
EXPECT_TRUE(std::any_cast<string>(Petr.imp->\
                                      GetField(name)) == "Ivanov Petr");
EXPECT_TRUE(std::any_cast<string>(Petr.imp->\
                                      GetField(group)) == "1");
EXPECT_TRUE(std::any_cast<string>(Petr.imp->\
                                      GetField(avg)) == "4.25");
EXPECT_TRUE(std::any_cast<std::nullptr_t>(Petr.imp->\
                                         GetField(debt)) == nullptr);

j_string =\
R"({"name": "Sidorov Ivan", "group": 31, "avg": 4, "debt": "C++"})";
j = Json::parse(j_string);
Student Ivan(j);
EXPECT_TRUE(Ivan.imp->GetType(name) == String);
EXPECT_TRUE(Ivan.imp->GetType(group) == Integer);
EXPECT_TRUE(Ivan.imp->GetType(avg) == Integer);
EXPECT_TRUE(Ivan.imp->GetType(debt) == String);
EXPECT_TRUE(std::any_cast<string>(Ivan.imp->\
                                      GetField(name)) == "Sidorov Ivan");
EXPECT_TRUE(std::any_cast<int>(Ivan.imp->\
                                      GetField(group)) == 31);
EXPECT_TRUE(std::any_cast<int>(Ivan.imp->\
                                      GetField(avg)) == 4);
EXPECT_TRUE(std::any_cast<string>(Ivan.imp->\
                                 GetField(debt)) == "C++");
j_string =\
R"({"name": "Petrov Nikita", "group": "IU8-31", "avg": 3.33, "debt": ["C++", "Linux", "Network"]})";
j = Json::parse(j_string);
Student Nikita(j);
EXPECT_TRUE(Nikita.imp->GetType(name) == String);
EXPECT_TRUE(Nikita.imp->GetType(group) == String);
EXPECT_TRUE(Nikita.imp->GetType(avg) ==  Double);
EXPECT_TRUE(Nikita.imp->GetType(debt) ==  Vector);
EXPECT_TRUE(std::any_cast<string>(Nikita.imp->\
                                GetField(name)) == "Petrov Nikita");
EXPECT_TRUE(std::any_cast<string>(Nikita.imp->\
                                      GetField(group)) == "IU8-31");
EXPECT_TRUE(std::any_cast<double>(Nikita.imp->\
                                      GetField(avg)) == 3.33);
EXPECT_TRUE((std::any_cast<std::vector<string>>(Nikita.imp->\
GetField(debt)) == std::vector<string> {"C++", "Linux", "Network"}));
}

TEST(Table_Test, EmptyStudents){
Table table(std::vector<Student>{});
std::stringstream ans;
table.Print(ans);
EXPECT_EQ(ans.str(), "");
EXPECT_EQ(table.impl->GetWidth(""), 0);
}
TEST(Table_Test, ConvertToString){
string j_string =\
R"({"name": "Petrov Nikita", "group": "IU8-31", "avg": 3.33, "debt": ["C++", "Linux", "Network"]})";
Json j = Json::parse(j_string);
Student Nikita(j);

j_string =\
R"({"name": "Sidorov Ivan", "group": 31, "avg": 4, "debt": "C++"})";
j = Json::parse(j_string);
Student Ivan(j);

j_string =\
      R"({"name": "Ivanov Petr", "group": "1", "avg": "4.25", "debt": null})";
j = Json::parse(j_string);
Student Petr(j);

Table table(std::vector<Student>{ Petr, Ivan, Nikita  });
std::stringstream ss;
table.Print(ss);

string ref_string =\
 R"(|-------------|------|----|-------|
|name         |group |avg |debt   |
|-------------|------|----|-------|
|Ivanov Petr  |1     |4.25|null   |
|-------------|------|----|-------|
|Sidorov Ivan |31    |4   |C++    |
|-------------|------|----|-------|
|Petrov Nikita|IU8-31|3.33|3 items|
|-------------|------|----|-------|
)";
EXPECT_EQ(ref_string, ss.str());
}

TEST(Table_Test, IncorrectString_ItemsWrongCount) {
string wrong_string =
    R"({
"items": [
{
"name": "Ivanov Petr",
"group": "1",
"avg": "4.25",
"debt": null
},
{
"name": "Petrov Nikita",
"group": "IU8-31",
"avg": "3.33",
"debt": ["C++", "Linux", "Network"]
}
],
"_meta": {
"count": 3
}
})";
try {
Table::ParseFromString(wrong_string);
} catch (const std::runtime_error& e) {
string ref_str = R"(incorrect JSON file: count field at meta
      should be equal items field size)";
EXPECT_EQ(e.what(), ref_str);
}
}

TEST(Table_Test, IncorrectString_ItemsNotArray) {
string wrong_string =
    R"(
{
"items": {
"name": "Ivanov Petr",
"group": "1",
"avg": "4.25",
"debt": null
}
})";
try {
Table::ParseFromString(wrong_string);
} catch (const std::runtime_error& e) {
string ref_str = R"(incorrect JSON file:
    items field should be an array)";
EXPECT_EQ(e.what(), ref_str);
}
}

TEST(Table_Test, IncorrctFile_FileNotFound){
try{
Table::ParseFromFile("incorrect.json");
} catch (const std::runtime_error& e) {
string ref_str = "unable to open json: incorrect.json";
EXPECT_EQ(e.what(), ref_str);
}
}

TEST(Table_Test, IncorrctFile_ItemsWrongCount) {
string wrong_string =
    R"({
"items": [
{
"name": "Ivanov Petr",
"group": "1",
"avg": "4.25",
"debt": null
},
{
"name": "Petrov Nikita",
"group": "IU8-31",
"avg": "3.33",
"debt": ["C++", "Linux", "Network"]
}
],
"_meta": {
"count": 3
}
})";
std::ofstream wrong_file;
wrong_file.open("wrong_file.json", std::ios::out);
wrong_file << wrong_string;
wrong_file.close();
try {
Table::ParseFromFile("wrong_file.json");
} catch (const std::runtime_error& e) {
string ref_str = R"(incorrect JSON file: count field at meta
     should be equal items field size)";
EXPECT_EQ(e.what(), ref_str);
}
}

TEST(Table_Test, IncorrectFile_ItemsNotArray) {
string wrong_string =
    R"(
{
"items": {
"name": "Ivanov Petr",
"group": "1",
"avg": "4.25",
"debt": null
}
})";
std::ofstream wrong_file;
wrong_file.open("wrong_file.json", std::ios::out);
wrong_file << wrong_string;
wrong_file.close();
try {
Table::ParseFromFile("wrong_file.json");
} catch (const std::runtime_error& e) {
string ref_str = R"(incorrect JSON file: items field should be an array)";
EXPECT_EQ(e.what(), ref_str);
}
}

TEST(FULL_CYCLE_TEST, FromFile){
string right_string =
    R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";
std::ofstream right_file;
right_file.open("right_file.json", std::ios::out);
right_file << right_string;
right_file.close();

Table table = Table::ParseFromFile("right_file.json");
std::stringstream ans;
table.Print(ans);
string ref_string =\
 R"(|-------------|------|----|-------|
|name         |group |avg |debt   |
|-------------|------|----|-------|
|Ivanov Petr  |1     |4.25|null   |
|-------------|------|----|-------|
|Sidorov Ivan |31    |4   |C++    |
|-------------|------|----|-------|
|Pertov Nikita|IU8-31|3.33|3 items|
|-------------|------|----|-------|
)";
EXPECT_EQ(ans.str(), ref_string);
}
TEST(FULL_CYCLE_TEST, FromString){
string right_string =
    R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";

Table table = Table::ParseFromString(right_string);
std::stringstream ans;
table.Print(ans);
string ref_string =\
 R"(|-------------|------|----|-------|
|name         |group |avg |debt   |
|-------------|------|----|-------|
|Ivanov Petr  |1     |4.25|null   |
|-------------|------|----|-------|
|Sidorov Ivan |31    |4   |C++    |
|-------------|------|----|-------|
|Pertov Nikita|IU8-31|3.33|3 items|
|-------------|------|----|-------|
)";
EXPECT_EQ(ans.str(), ref_string);
}
int main(int argc, char** argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
