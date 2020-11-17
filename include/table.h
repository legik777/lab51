//
// Created by lamp on 09.11.2020.
//

#ifndef PARSER_JSONTABLE_H
#define PARSER_JSONTABLE_H

#include "../include/student.h"

union Widths{
  size_t name;
  size_t group;
  size_t avg;
  size_t debt;
};
class Table {
 public: // Ctors
  Table(const std::vector<Student>& students_);
  Table() = default;

 public: // Fields
  struct Impl{ // Implementation
   private:
    size_t name_w = 4;
    size_t group_w = 5;
    size_t avg_w = 3;
    size_t debt_w = 4;
    std::vector<Student> students;
   public: // "Get" Funcs
    auto GetWidth(const string& index) const -> size_t;
    void SetWidth(const string& index, size_t newValue);
    auto GetVector() -> std::vector<Student>;
    void SetVector(std::vector<Student> newVector);
  };
 public: // Funcs
  void Print(std::ostream& os) const;
  void Print(const Student& student, std::ostream& os) const;
  void Filler(std::ostream& os) const;

  static void Filler(size_t size, size_t len, std::ostream& os) ;
  static Table ParseFromFile(const string& jsonPath);

  static Table ParseFromString(const string& jsonString);

  friend std::ostream& operator<<(std::ostream& os,const Table& table) ;

  std::unique_ptr<Impl> impl;
};

#endif  // PARSER_JSONTABLE_H
