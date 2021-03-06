// Copyright 2020 Andreytorix
#pragma once
#include <utility>
template <typename T>
class Stack
{
private:
    struct Node
    {
        Node* next; //указатель на следующий элемент списка
        T obj; //хранит данные
    };
public:
    Node* nodeHead;
    size_t length;
    Stack() {
        nodeHead = nullptr;
        length = 0;
    }
    ~Stack() {
    }
    void push(T&& value) { //push - передаём rvalue сслыку на объект
        Node* nd = new Node;
        nd->obj = std::move(value);
        nd->next = nodeHead;
        ++length;
        nodeHead = std::move(nd);
        nd = nullptr;
        delete nd;
    }
    void push(const T& value) { //push - передаём lvalue сслыку на объект
        Node* nd = new Node;
        nd->obj = std::move(value);
        nd->next = std::move(nodeHead);
        ++length;
        nodeHead = std::move(nd);
        nd = nullptr;
        delete nd;
    }

    size_t Length() {
        return length;
    }
    void pop() { //снимаем верхний элемент стэка (удаляем)
        if (nodeHead){
        Node* tmp = nodeHead;
        nodeHead =  nodeHead->next;
        delete tmp;
        //T tmp = std::move(nodeHead->obj);
        //nodeHead = std::move(tmp);
        length--;
        }
    }
    const T& head() const { //возвращает ссылку на шапку стэка
        T& ref = nodeHead->obj;
        return ref;
    }
};

