
#pragma once
#ifndef UTILDSA
#define UTILDSA
// #ifndef COLOR_HPP
#include <windows.h>
#include <string>
#include <sstream>
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
  if(repetitions < 1) repetitions = 60;
  stringstream oss;
  for(int i = 0; i < repetitions; i++) 
    oss << str;
  return oss.str();
}

#endif