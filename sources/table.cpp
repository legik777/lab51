// Copyright 2020 mrmamongo
//
// Created by lamp on 09.11.2020.
//
#include "../include/table.h"
#include <utility>

Table::Table(const std::vector<Student>& students_)
    :impl(new Impl){
  impl->SetVector(students_);
  for (const auto& student : students_) {
    if (student.ToString(name).length() >\
      impl->GetWidth(name))
      impl->SetWidth(name, student.ToString(name).length());
    if (student.ToString(group).length() >\
      impl->GetWidth(group))
      impl->SetWidth(group, student.ToString(group).length());
    if (student.ToString(avg).length() >\
      impl->GetWidth(avg))
      impl->SetWidth(avg, student.ToString(avg).length());
    if (student.ToString(debt).length() >\
      impl->GetWidth(debt))
      impl->SetWidth(debt, student.ToString(debt).length());
  }
}



Table Table::ParseFromFile(const string& jsonPath){
  std::ifstream file(jsonPath);
  if (!file) {
    throw std::runtime_error{"unable to open json: " + jsonPath};
  }
  Json data;
  file >> data;
  if (!data.at("items").is_array()){
    throw std::runtime_error
        { "incorrect JSON file: items field should be an array"};
  }
  if (data.at("items").size() !=\
      data.at("_meta").at("count").get<size_t>()) {
    throw std::runtime_error
        {
            R"(incorrect JSON file: count field at meta
     should be equal items field size)"
        };
  }
  std::vector<Student> newStudents;
  for ( const auto& item : data.at("items") ){
    Student newStudent(item);
    newStudents.push_back(newStudent);
  }
  return Table(newStudents);
}
Table Table::ParseFromString(const string& jsonString){
  Json data = Json::parse(jsonString);
  if (!data.at("items").is_array()){
    throw std::runtime_error
        { R"(incorrect JSON file:
    items field should be an array)"};
  }
  if (data.at("items").size() !=\
      data.at("_meta").at("count").get<size_t>()){
    throw std::runtime_error
        {
            R"(incorrect JSON file: count field at meta
      should be equal items field size)"};
  }
  std::vector<Student> newStudents;
  for ( const auto& item : data.at("items") ){
    Student newStudent(item);
    newStudents.push_back(newStudent);
  }
  return Table(newStudents);
}

void Table::Filler(std::ostream &os) const{
  os << "|";
  for (size_t i = 0; i < impl->GetWidth(name); ++i){
    os << "-";
  }
  os << "|";
  for (size_t i = 0; i < impl->GetWidth(group); ++i){
    os << "-";
  }
  os << "|";
  for (size_t i = 0; i < impl->GetWidth(avg); ++i){
    os << "-";
  }
  os << "|";
  for (size_t i = 0; i < impl->GetWidth(debt); ++i){
    os << "-";
  }
  os << "|" << std::endl;
}

void Table::Filler(size_t size, size_t len, std::ostream &os) {
  for (size_t i = 0; i < size - len; ++i){
    os << " ";
  }
}

void Table::Print(std::ostream &os) const {
  if (impl->GetVector().empty()) {
    return;
  }
  Filler(os);
  std::stringstream header;
  header << "|" << name;
  for (size_t i = 0; i < impl->GetWidth(name) - name.length(); ++i){
    header << " ";
  }
  header << "|" << group;
  for (size_t i = 0; i < impl->GetWidth(group) - group.length(); ++i){
    header << " ";
  }
  header << "|" << avg;
  for (size_t i = 0; i < impl->GetWidth(avg) - avg.length(); ++i){
    header << " ";
  }
  header << "|" << debt;
  for (size_t i = 0; i < impl->GetWidth(debt) - debt.length(); ++i){
    header << " ";
  }
  header << "|";
  os << header.str() << std::endl;

  for (const auto& student : impl->GetVector()) {
    Print(student, os);
  }
  Filler(os);
}
void Table::Print(const Student& student, std::ostream& os) const{
  Filler(os);
  os << "|" << student.ToString(name);
  Filler(impl->GetWidth(name), student.ToString(name).length(), os);
  os << "|" << student.ToString(group);
  Filler(impl->GetWidth(group), student.ToString(group).length(), os);
  os << "|" << student.ToString(avg);
  Filler(impl->GetWidth(avg), student.ToString(avg).length(), os);
  os << "|" << student.ToString(debt);
  Filler(impl->GetWidth(debt), student.ToString(debt).length(), os);
  os << "|" << std::endl;
}
auto Table::Impl::GetWidth(const string& index) const -> size_t {
  if ( index == name ){
    return name_w;
  } else if ( index == group ){
    return group_w;
  } else if ( index == avg ){
    return avg_w;
  } else if ( index == debt ){
    return debt_w;
  } return 0;
}
void Table::Impl::SetWidth(const string& index, size_t newValue) {
  if ( index == name ){
    name_w = newValue;
  } else if ( index == group ){
    group_w = newValue;
  } else if ( index == avg ){
    avg_w = newValue;
  } else if ( index == debt ){
    debt_w = newValue;
  }
}
auto Table::Impl::GetVector() -> std::vector<Student> {
  return students;
}
void Table::Impl::SetVector(std::vector<Student> newVector) {
  students = std::move(newVector);
}
