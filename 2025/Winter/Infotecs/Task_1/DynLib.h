#pragma once

#ifdef DYNLIB_EXPORT
#define DYNLIB_API __declspec(dllexport)
#else
#define DYNLIB_API __declspec(dllimport)
#endif 

extern "C" DYNLIB_API void f1(char*&, long long&);

extern "C" DYNLIB_API long long f2(const char*&, long long);

extern "C" DYNLIB_API bool f3(const char*&, long long);
