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
  BSTree<Farmer*> farmers;

  // vector<City>& addCities(auto cities) {

  // }


public:
  APMS(): wilayas{BSTree<Wilaya*>()}, cities{BSTree<City*>()}, areas{BSTree<Area*>()}, lands{BSTree<Land*>()}, rawFile{DBMS()}, farmers{BSTree<Farmer*>()} {}
  APMS(const string &fpath) : rawFile{DBMS{fpath}}, wilayas{BSTree<Wilaya*>()}, cities{BSTree<City*>()}, areas{BSTree<Area*>()}, lands{BSTree<Land*>()}, farmers{BSTree<Farmer*>()} {}
  
  void load() {
    rawFile.read();
    for(auto wil = rawFile.getFileData().begin(); wil != rawFile.getFileData().end(); wil++) {
      Wilaya* wilaya = new Wilaya();
      wilaya->setName((*wil)["name"]);
      wilaya->setId((*wil)["id"]);
      wilayas.insert(wilaya);
      for(auto city = (*wil)["cities"].begin(); city != (*wil)["cities"].end(); city++) {
        City* cit = new City();
        cities.insert(cit);
        wilaya->addCity(cit);
        cit->setName((*city)["name"]);
        cit->setCityId((*city)["id"]);
        for (auto area = (*city)["areas"].begin(); area != (*city)["areas"].end(); area++) {
          Area* ar = new Area();
          cit->addArea(ar);
          ar->setId((*area)["id"]);
          ar->setName((*area)["name"]);
          areas.insert(ar);
          for(auto land = (*area)["lands"].begin(); land != (*area)["lands"].end(); land++) {
            Land* lnd = new Land();
            ar->addLand(lnd);
            lnd->setId((*land)["id"]);
            Farmer *frmr = new Farmer(
                (*land)["farmer"]["id"],
                (*land)["farmer"]["age"],
                (*land)["farmer"]["name"],
                (*land)["farmer"]["gender"]
            );
            lnd->setFarmer(frmr);
            farmers.insert(frmr);
            lands.insert(lnd);

            for(auto year = (*land)["report"].begin(); year != (*land)["report"].end(); year++) {
              AnnualReport* report = new AnnualReport();
              lnd->addYear(report);
              report->setYear((*year)["year"]);
              // Farmer* frmr = new Farmer(
                // (*year)["farmer"]["id"],
                // (*year)["farmer"]["age"],
                // (*year)["farmer"]["name"],
                // (*year)["farmer"]["gender"]
              // );
              // frmr->setId((*year)["farmer"]["id"]);
              // frmr->setAge((*year)["farmer"]["age"]);
              // frmr->setName((*year)["farmer"]["name"]);
              // lnd->setFarmer(frmr);
              for(auto worker = (*year)["workers"].begin(); worker != (*year)["workers"].end(); worker++) {
                Worker* wkr = new Worker(
                  (*worker)["id"],
                  (*worker)["age"],
                  (*worker)["name"],
                  (*worker)["gender"]
                );
                report->addWorker(wkr);
              }
              for(auto month = (*year)["months"].begin(); month != (*year)["months"].end(); month++) {
                MonthlyReport* mo = new MonthlyReport();
                report->addMonth(mo);
                mo->setMonth((*month)["month"]);
                auto landData = (*month)["data"];
                Production* lndData = new Production();
                mo->setLandData(lndData);
                unordered_map<string, ProductCategory> prod;
                for(auto product = landData["products"].begin(); product != landData["products"].end(); product++) {
                  prod[(string)(*product)["name"]] = ProductCategory(
                    (string)(*product)["name"],
                    (double)(*product)["basePrice"],
                    (double)(*product)["production"],
                    (PesticideSeverity)(*product)["pesticideSeverity"]
                  );
                }
                lndData->setProducts(prod);
                lndData->setWaterConsumption(landData["waterConsumption"]);
                lndData->setElectricityConsumption(landData["electricityConsumption"]);
              }
            }
          }
        }
      }
    }
  }

  void printLandWorkersByYear(int id, int year) {
    // Accessing the lands using the areas name using getById
    Area* area = *areas.getById(id);
    for(auto land = area->getLands().begin(); land != area->getLands().end(); land++) {
      for(auto report = (*land)->getReport().begin(); report != (*land)->getReport().end(); report++) {
        if((*report)->getYear() == year) {
          cout << "Land ID: " << (*land)->getId() << endl;
          cout << "Land Farmer: " << (*land)->getFarmer()->getName() << endl;
          cout << "Land Workers: " << endl;
          for(auto worker = (*report)->getWorkers().begin(); worker != (*report)->getWorkers().end(); worker++) {
            cout << (*worker)->getName() << endl;
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