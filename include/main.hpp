// Copyright 2020 Andreytorix
#pragma once
#include <utility>
template <typename T>
class Stack
{
private:
    struct Node
    {
        Node(): next(NULL){}; //указатель на следующий элемент списка
        Node(const T& value) : obj(value), next(NULL){}
        T obj; //хранит данные
        Node* next;
    };
public:
    Node* nodeHead;
    size_t length;
    Stack() {
        nodeHead = NULL;
        length = 0;
    }
    ~Stack() {
        //void del();
    }
    /*void del() {
        while (nodeHead) {
            Node* tmp = nodeHead;
            nodeHead = nodeHead->next;
            delete tmp;
            void del();
       }
    }*/
    void push(T&& value) { //push - передаём rvalue сслыку на объект
        Node* nd = new Node;
        nd->obj = std::move(value);
        nd->next = nodeHead;
        ++length;
        nodeHead = std::move(nd);
        //nd = NULL;
        //delete nd;
    }
    void push(const T& value) { //push - передаём lvalue сслыку на объект
        if(Node* nd = new Node(value)){
        ++length;
        nodeHead = std::move(nd);
        }
        //Node* nd = new Node;
        //nd->obj = std::move(value);
        //nd->next = std::move(nodeHead);
        //nd = NULL;
        //delete nd;
    }

    size_t Length() {
        return length;
    }
    void pop() { //снимаем верхний элемент стэка (удаляем)
        if (nodeHead){
        Node* tmp = nodeHead->next;
        delete nodeHead;
        //T tmp = std::move(nodeHead->obj);
        nodeHead = std::move(tmp);
        length--;
        }
    }
    const T& head() const { //возвращает ссылку на шапку стэка
        T& ref = nodeHead->obj;
        return ref;
    }
};

