//
// Created by lamp on 09.11.2020.
//

#ifndef PARSER_STUDENTS_H
#define PARSER_STUDENTS_H


#include <any>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "nlohmann/json.hpp"


using Json = nlohmann::json;
using string = std::string;
using std::cout;
using std::any;
// Public constants
static const string name = "name";
static const string group = "group";
static const string avg = "avg";
static const string debt = "debt";
// Public Unions

enum Type{
  String,
  Integer,
  Double,
  Vector,
  Null
};

class Student {
 public: // Enum

 public: // Ctors
  Student(const Student& student);
  explicit Student(Json json);
 public: // Funcs
  string ToString(const string& valueName) const;


 public:
  struct Imp{// Implementation
   private:
    Type nameType;
    Type groupType;
    Type avgType;
    Type debtType;

    any nameValue;
    any groupValue;
    any avgValue;
    any debtValue;

   public:
    // "Get" Funcs
    auto GetType(const string& index) -> Type;
    auto GetField(const string& index) -> any;
    void SetType(const string& index, Type newType);
    void SetField(const string& index, const any& newValue);
  };


  std::unique_ptr<Imp> imp;
};



#endif  // PARSER_STUDENTS_H
