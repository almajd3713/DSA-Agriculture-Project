
#pragma once
#ifndef UTILDSA
#define UTILDSA
// #ifndef COLOR_HPP
#include <windows.h>
#include <string>
#include <sstream>
#include <chrono>
#include <functional>
using std::function;
using namespace std::chrono;
using std::string, std::stringstream;
// #endif

inline int getConsoleWidth()
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

inline string stringRepeat(const string& str, int repetitions)
{
  if(repetitions < 1 || repetitions > 200) repetitions = 80;
  stringstream oss;
  for(int i = 0; i < repetitions; i++) 
    oss << str;
  return oss.str();
}

template <typename T>
auto benchmark(size_t iterations, std::function<void()> func_to_test)
{
  auto start = std::chrono::high_resolution_clock::now();

  for (size_t i = 0; i < iterations; ++i)
    func_to_test();

  auto end = std::chrono::high_resolution_clock::now();

  return std::chrono::duration_cast<T>(end - start) / iterations;
}

#endif