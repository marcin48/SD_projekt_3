#pragma once
class Dictionary
{
public:
    virtual void insert(int key, int value)=0;
    virtual int search(int key)=0;
    virtual void remove(int key)=0;
    virtual int getRandomKey() = 0;
    virtual void display()=0;
};

