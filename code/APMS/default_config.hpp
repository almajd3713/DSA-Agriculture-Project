#pragma once
#ifndef DEFAULTCONFIGDSA
#define DEFAULTCONFIGDSA
#include "APMS.hpp"

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

// enum prompts {
//   MENU, 
//   INFO, MODIFY,
//   WILAYAS, CITIES, AREAS, LANDS, FARMERS,
//   WINNERS, PENALTIES,
//   TOTAL_SALES
// };

void testProgram(const string &path, int iterations)
{
  cout << "Test1: Average time to load the data into memory" << endl;
  auto time = benchmark<milliseconds>((size_t)iterations, [&path]
                                      {
    cout << "iteration: " << endl;
    auto time2 = benchmark<milliseconds>((size_t)1, [&path] {
      APMSBST apms(path);
      apms.load();
    });
    cout << "iteration took " << time2.count() << " ms" << endl; });
  cout << "Time taken on average For BST to load and destruct: " << time.count() << endl;

  time = benchmark<milliseconds>((size_t)iterations, [&path]
                                 {
    cout << "iteration: " << endl;
    auto time2 = benchmark<milliseconds>((size_t)1, [&path] {
      APMSAVL apms(path);
      apms.load();
    });
    cout << "iteration took " << time2.count() << " ms" << endl; });
  cout << "Time taken on average For Avl to load and destruct: " << time.count() << endl;
}

void startProgram(const string &path)
{
    APMSBST apms(path);
    defaultConfig(apms);
    apms.start();
  
}

#endif