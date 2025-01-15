#include "pch.h"

void f1(char*& s, long long &size) {
    long long step = 1;        // шаг для сортировки
    while (step < size)step = step << 1; // инициализация самого первого шага
    step = step >> 2;
    long long istep;
    // Сортировка Шелла с выбором шагов(расстояний) по Хиббарду: istep[i] = (2^i) - 1
    for (step, istep = step; istep > 0; step = step / 2, istep = step - 1) {
        for (int i = istep; i < size; ++i) {
            for (int j = i - istep; j >= 0 && s[j] < s[j + istep]; j = j - istep) {
                char temp = s[j];
                s[j] = s[j + istep];
                s[j + istep] = temp;
            }
        }
    }
    char* sub_s = new char[size];
    for (long long i = 0; i < size; ++i) {
        sub_s[i] = s[i];
    }
    delete[] s;
    s = new char[size = (size + (size >> 1) + (size & 1))];
    // замена чётных элементов на "КВ"
    for (long long i = 0, j = 1; i+2<size; j += 2, i += 3) {
        s[i] = 'K';
        s[i + 1] = 'B';
        s[i + 2] = sub_s[j];
    }
    s[size - 2] = 'K';
    s[size - 1] = 'B';
    delete[] sub_s;
}

long long f2(const char *&s, long long size) {
    if (size == 0)return 0;
    long long S = 0;  // Сумма
    char t;
    long long i = 0;
    long long N = 0;
    while (i < size) {
        t = s[i];
        N = 0;
        while (i < size && t >= '0' && t <= '9') {
            N = N * 10 + t - '0';
            i++;
            t = s[i];
        }
        i++;
        S = S + N;
    }
    return S;
}

bool f3(const char *&s, long long size) {
    return ((!(size & 31)) && ((size && 32) >> 5));
}
