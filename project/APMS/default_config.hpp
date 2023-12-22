#pragma once
#ifndef DEFAULTCONFIGDSA
#define DEFAULTCONFIGDSA
#include "APMSBST.hpp"
// #include "APMSAVL.hpp"

void defaultConfig(APMSBST& apms) {
  apms.load();

  apms.addCategory("Fruit");
  apms.addCategory("Cereal");
  apms.addCategory("Vegetable");
  apms.addCategory("Date");
  apms.addCategory("Olive");
}

// void defaultConfig(APMSAVL &apms)
// {
//   apms.load();

//   apms.addCategory("Fruit");
//   apms.addCategory("Cereal");
//   apms.addCategory("Vegetable");
//   apms.addCategory("Date");
//   apms.addCategory("Olive");
// }

enum prompts {
  MENU, 
  INFO, MODIFY,
  WILAYAS, CITIES, AREAS, LANDS, FARMERS,
  WINNERS, PENALTIES,
  TOTAL_SALES
};




#endif