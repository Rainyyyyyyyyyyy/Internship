#include <iostream>
#include "DynLib.h"

int main()
{
    char* s = new char[13];
    long long  size = 13;
    for (int i = 0; i < 13; i++)s[i] = 'A' + i;
    for (int i = 0; i < 13; i++)std::cout << "'" << s[i] << "' ";
    std::cout << std::endl;

    f1(s, size);
    for (int i = 0; i < size; i++)std::cout << "'" << s[i] << "' ";
    std::cout << std::endl;
}

