#pragma once
#ifndef DEFAULTCONFIGDSA
#define DEFAULTCONFIGDSA
#include "APMS.hpp"

void defaultConfig(APMS& apms) {
  apms.load();

  apms.addCategory("Fruit");
  apms.addCategory("Cereal");
  apms.addCategory("Vegetable");
  apms.addCategory("Date");
  apms.addCategory("Olive");
}


#endif