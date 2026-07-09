#include <iostream>

struct Foo
{
    void Subscribe();
    void BecomeAPatron();
    void WhatTheHell();
    void Okey()
    {
        int a = 10;
        std::cout << "a :" << a << std::endl;
    }
};

int main()
{
    std::cout << "Size of Foo :" << sizeof(Foo) << std::endl;
    Foo f;
    f.Okey();
    std::cout << "Size of Foo :" << sizeof(Foo) << std::endl;

    return 0;
}