// Copyright 2020 Andreytorix
#include <gtest/gtest.h>
#include <utility>
//#include "../include/main.hpp"
#include "../include/main2.hpp"


//
//

TEST(class_Stack, Test1) {
   StackList<int> SL;
  SL.Print("SL");

  SL.Push(8);
  SL.Push(5);
  SL.Push(10);
  SL.Push(7);
  SL.Print("SL");

  // проверка конструктора копирования
  StackList<int> SL2 = SL;
  SL2.Print("SL2");

  SL.Empty();
  SL.Print("SL");

  SL = SL2;
  SL.Print("SL = SL2");

  StackList<int> SL3;
  SL3.Push(1);
  SL3.Push(2);
  SL3.Push(3);
  SL3.Print("SL3");

  SL = SL2 = SL3;
  SL.Print("SL");
  SL2.Print("SL2");

  int d = SL2.Pop();

  cout << "d = " << d << endl;
  SL2.Print("SL2-1");

  d = SL2.Pop();
  SL2.Print("SL2-2");

  d = SL2.Pop();
  SL2.Print("SL2-3");

  d = SL2.Pop();
  cout << "d = " << d << endl;
  SL2.Print("SL2----");
     EXPECT_EQ(1, 1);
    //EXPECT_EQ(obj1.head(), 3);
   
    //EXPECT_EQ(obj1.head(), 2);
    
    //EXPECT_EQ(obj1.head(), 1);
    //void del();
}
/*
TEST(class_Stack, Test2) {
    Stack<MyClass> obj1;
    MyClass x1;
    MyClass x2(10, "lala");
    MyClass x3(11, "hihi");
    obj1.push(x1);
    obj1.push(x2);
    obj1.push(x3);
    EXPECT_EQ(obj1.Length(), 3);
    EXPECT_EQ(obj1.head().GetName(), "hihi");
    EXPECT_EQ(obj1.head().GetValue(), 11);
    obj1.pop();
    EXPECT_EQ(obj1.Length(), 2);
    EXPECT_EQ(obj1.head().GetName(), "lala");
    EXPECT_EQ(obj1.head().GetValue(), 10);
    obj1.pop();
    EXPECT_EQ(obj1.Length(), 1);
    EXPECT_EQ(obj1.head().GetName(), "EMPTY");
    EXPECT_EQ(obj1.head().GetValue(), 0);
    //void del();
}

TEST(class_Stack_2, Test1) {
    Stack_2<int> sp;
    sp.push_emplace(5, 8, 2, 5, 8);
    EXPECT_EQ(sp.pop(), 8);
    EXPECT_EQ(sp.pop(), 5);
    EXPECT_EQ(sp.pop(), 2);
    EXPECT_EQ(sp.pop(), 8);
    EXPECT_EQ(sp.pop(), 5);
    void del_2();
}

TEST(class_Stack_2, Test2) {
    Stack_2<MyClass> obj2;
    MyClass x1;
    MyClass x2(10, "lala");
    MyClass x3(11, "hihi");
    obj2.push_emplace(x1, x2, x3);
    EXPECT_EQ(obj2.Length(), 3);
    MyClass ptr = obj2.pop();
    EXPECT_EQ(obj2.Length(), 2);
    EXPECT_EQ(ptr.GetName(), "hihi");
    EXPECT_EQ(ptr.GetValue(), 11);
    ptr = obj2.pop();
    EXPECT_EQ(obj2.Length(), 1);
    EXPECT_EQ(ptr.GetName(), "lala");
    EXPECT_EQ(ptr.GetValue(), 10);
    ptr = obj2.pop();
    EXPECT_EQ(obj2.Length(), 0);
    EXPECT_EQ(ptr.GetName(), "EMPTY");
    EXPECT_EQ(ptr.GetValue(), 0);
    void del_2();
}*/

