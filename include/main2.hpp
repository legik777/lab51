// Copyright 2020 Andreytorix
#pragma once
#include <utility>
template <typename T>
class Stack_2
{
private:
    struct Node
    {
        Node* next; //указатель на следующий элемент списка
        T obj;
    };
public:
    Node* nodeHead;
    size_t length;
    Stack_2() {
        nodeHead = NULL;
        length = 0;
    }
    void push(T&& value) {
        Node* nd = new Node;
        nd->obj = std::move(value);
        nd->next = nodeHead;
        length++;
        nodeHead = nd;
    }
    template <typename ... Args> //{4,8,3,6,9,4,43,3,6,}
    void push_emplace(Args&&...  value) {
        T arr[] = { std::move(value)...};
        for (size_t i = 0; i < sizeof...(value); ++i) {
            push(std::move(arr[i]));
        }
    }
    size_t Length() {
        return length;
    }
    T pop() {
            T tmp = std::move(nodeHead->obj);
            nodeHead = std::move(nodeHead->next);
            length--;
            return tmp;
    }
   const T& head(){
       T& ref = nodeHead->obj;
        return ref;
    }
    void del(Node*& head)
    {
        if (head)
        {
            del(head->nodeHead);
            delete head;
        }
    }
};
