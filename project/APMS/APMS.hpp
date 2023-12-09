#pragma once
#ifndef APMSDSA
#define APMSDSA
#include <vector>
#include <type_traits>
#include "misc/AvlTree.hpp"
#include "misc/BinarySearchTree.h"
#include "misc/DBMS.hpp"
#include "classes/wilaya.hpp"

// template<>
// class APMS<int> {
//   DBMS rawData;
//   BSTree<Wilaya>* data;

//   public:
//     APMS(string fpath);

//     void startup();
// };

// template<typename Comparable>
// class APMS {
//   // To force the use of Avl or BST
//   static_assert(
//     std::is_same<Comparable, AvlTree<Wilaya>>::value || std::is_same<Comparable, BSTree<Wilaya>>::value,
//     "Error: Cannot use any storage types other than BSTree or AvlTree"
//   );  

//   DBMS rawData;
//   Comparable wilayas;
//   Comparable cities;
//   Comparable areas;
//   Comparable lands;

//   public: 
//     APMS();
//     APMS(const string& fpath);
// };


class APMS {
  DBMS rawFile;
  BSTree<Wilaya*> wilayas;
  BSTree<City*> cities;
  BSTree<Area*> areas;
  BSTree<Land*> lands;

  // vector<City>& addCities(auto cities) {

  // }


public:
  APMS(): wilayas{BSTree<Wilaya*>()}, cities{BSTree<City*>()}, areas{BSTree<Area*>()}, lands{BSTree<Land*>()}, rawFile{DBMS()} {}
  APMS(const string &fpath) : rawFile{DBMS{fpath}}, wilayas{BSTree<Wilaya*>()}, cities{BSTree<City*>()}, areas{BSTree<Area*>()}, lands{BSTree<Land*>()} {}
  
  void load() {
    rawFile.read();
    for(auto wil = rawFile.getFileData().begin(); wil != rawFile.getFileData().end(); wil++) {
      Wilaya* wilaya = new Wilaya();
      wilayas.insert(wilaya);
      wilaya->setName((*wil)["name"]);
      wilaya->setId((*wil)["id"]);
      for(auto city = (*wil)["cities"].begin(); city != (*wil)["cities"].end(); city++) {
        City* cit = new City();
        cities.insert(cit);
        wilaya->addCity(cit);
        cit->setName((*city)["name"]);
        cit->setCityId((*city)["id"]);
        for (auto area = (*city)["areas"].begin(); area != (*city)["areas"].end(); area++) {
          Area* ar = new Area();
          areas.insert(ar);
          cit->addArea(ar);
          ar->setId((*area)["id"]);
          ar->setName((*area)["name"]);
          for(auto land = (*area)["lands"].begin(); land != (*area)["lands"].end(); land++) {
            Land* lnd = new Land();
            ar->addLand(lnd);
            lands.insert(lnd);
            lnd->setId((*land)["id"]);
            
            for(auto year = (*land)["report"].begin(); year != (*land)["report"].end(); year++) {
              AnnualReport* report = new AnnualReport();
              lnd->addYear(report);
              report->setYear((*year)["year"]);
              for(int month = 0; month < 12; month++) {
                MonthlyReport* mo = new MonthlyReport();
                report->addMonth(mo);
                mo->setMonth(month + 1);    
              }
            }
          }
        }
      }
    }
  }


  // BSTree<Wilaya> getWilayas() const {
  //   return wilayas;
  // }
};






#endif