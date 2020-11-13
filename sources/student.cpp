// Copyright 2020 mrmamongo
//
// Created by lamp on 09.11.2020.
//
#pragma once
#include "../include/student.h"

Student::Student(const Student& student): imp(new Imp){
  imp->SetField(name, student.imp->GetField(name));
  imp->SetField(group, student.imp->GetField(group));
  imp->SetField(avg, student.imp->GetField(avg));
  imp->SetField(debt, student.imp->GetField(debt));
  imp->SetType(name,  student.imp->GetType(name));
  imp->SetType(group, student.imp->GetType(group));
  imp->SetType(avg, student.imp->GetType(avg));
  imp->SetType(debt,  student.imp->GetType(debt));
}

Student::Student(Json json): imp(new Imp) {
  imp->SetType(name, String);
  imp->SetField(name, string(json.at(name)));

  if (json.at(group).is_string()) {
    imp->SetType(group, String);
    imp->SetField(group, string(json.at(group)));
  } else if (json.at(group).is_number_integer()) {
    imp->SetType(group, Integer);
    imp->SetField(group, static_cast<int>(json.at(group)));
  }

  if (json.at(avg).is_string()) {
    imp->SetType(avg, String);
    imp->SetField(avg, string(json.at(avg)));
  } else if (json.at(avg).is_number_integer()) {
    imp->SetType(avg, Integer);
    imp->SetField(avg, static_cast<int>(json.at(avg)));
  } else if (json.at(avg).is_number_float()) {
    imp->SetType(avg, Double);
    imp->SetField(avg, static_cast<double>(json.at(avg)));
  }

  if (json.at(debt).is_string()) {
    imp->SetType(debt, String);
    imp->SetField(debt, string(json.at(debt)));
  } else if (json.at(debt).is_array()) {
    imp->SetType(debt, Vector);
    imp->SetField(debt, std::vector<string>(json.at(debt)));
  } else if (json.at(debt).is_null()) {
    imp->SetType(debt, Null);
    imp->SetField(debt, nullptr);
  }
}
string Student::ToString(const string& valueName) const {
  switch (imp->GetType(valueName)) {
    default:
    case Null:{
      return "null";
    }
    case String:
    {
      return std::any_cast<string>(imp->GetField(valueName));
    }
    case Double:
    {
      std::stringstream out;
      out << std::any_cast<double>(imp->GetField(valueName));
      return out.str();
    }
    case Integer:{
      std::stringstream out;
      out << std::any_cast<int>(imp->GetField(valueName));
      return out.str();
    }
    case Vector:{
      std::stringstream  out;
      out << std::any_cast<std::vector<string>>\
             (imp->GetField(valueName)).size();
      return out.str() + " items";
    }
  }
}
auto Student::Imp::GetType(const string& index) -> Type{
  if (index == name){
    return nameType;
  } else if (index == group){
    return groupType;
  } else if (index == avg){
    return avgType;
  } else if (index == debt){
    return debtType;
  } return Null;
}
auto Student::Imp::GetField(const string& index) -> any{
  if (index == name){
    return nameValue;
  } else if (index == group){
    return groupValue;
  } else if (index == avg){
    return avgValue;
  } else if (index == debt){
    return debtValue;
  } return nullptr;
}
void Student::Imp::SetType(const string& index, Type newType) {
  if (index == name){
    nameType = newType;
  } else if (index == group){
    groupType = newType;
  } else if (index == avg){
    avgType = newType;
  } else if (index == debt){
    debtType = newType;
  }
}
void Student::Imp::SetField(const string& index, const any& newValue){
  if (index == name){
    nameValue = newValue;
  } else if (index == group){
    groupValue = newValue;
  } else if (index == avg){
    avgValue = newValue;
  } else if (index == debt){
    debtValue = newValue;
  }
}
