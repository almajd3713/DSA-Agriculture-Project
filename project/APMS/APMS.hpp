#pragma once
#ifndef APMSDSA
#define APMSDSA
#include <vector>
#include <type_traits>
#include <iomanip>
#include <stdlib.h>
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
  vector<string> categories;

  // vector<City>& addCities(auto cities) {

  // }


public:
  APMS(): wilayas{BSTree<Wilaya*>()}, cities{BSTree<City*>()}, areas{BSTree<Area*>()}, lands{BSTree<Land*>()}, rawFile{DBMS()}, farmers{BSTree<Farmer*>()}, categories{vector<string>()} {}
  APMS(const string &fpath) : rawFile{DBMS{fpath}}, wilayas{BSTree<Wilaya*>()}, cities{BSTree<City*>()}, areas{BSTree<Area*>()}, lands{BSTree<Land*>()}, farmers{BSTree<Farmer*>()}, categories{vector<string>()} {}
  
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
                (*land)["farmer"]["gender"],
                lnd
            );
            lnd->setFarmer(frmr);
            farmers.insert(frmr);
            lands.insert(lnd);

            for(auto year = (*land)["report"].begin(); year != (*land)["report"].end(); year++) {
              AnnualReport* report = new AnnualReport();
              lnd->addYear(report);
              report->setYear((*year)["year"]);
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
                mo->setProduction(lndData);
                unordered_map<string, ProductCategory*> prod;
                for(auto product = landData["products"].begin(); product != landData["products"].end(); product++) {
                  prod[(string)(*product)["name"]] = new ProductCategory(
                    (string)(*product)["name"],
                    (double)(*product)["basePrice"],
                    (double)(*product)["production"],
                    (PesticideSeverity)(*product)["pesticideSeverity"]
                  );
                }
                lndData->setCategories(prod);
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
      for(auto report = (*land)->getReports().begin(); report != (*land)->getReports().end(); report++) {
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

  

  void start() {
    int input;
    int year, month;
    while(true) {
      switch (input)
      {
      case 3:
        cout << "Enter Year and Month: ";
        cin >> year >> month;

        break;
      
      default:
        defaultPrompt(input);
        break;
      }
    }
  }

  void addCategory(string cat) {
    categories.push_back(cat);
  }


  void getWinner(int year, int month, string category) {
    // check if cateogries exists to begin with
    if(find(categories.begin(), categories.end(), category) == categories.end()) return;

    Land* winner = nullptr;
    double ratio = 0;
    cout << "start winners loop..." << endl;
    lands.iterate([year, month, category, &winner, &ratio](Land* land) -> bool {
      AnnualReport* y = land->getAnnualReport(year);
      if(y) {
        MonthlyReport* m = y->getMonthlyReport(month);
        if(m) {
          Production* prod = m->getProduction();
          ProductCategory* cat = prod->getCategory(category);
          if(cat) {
            // cout << land->getFarmer()->getName() << ": " << cat->getRatio(prod->getWaterConsumption()) << endl;
            if(
              !winner || (
                ratio < cat->getRatio(prod->getWaterConsumption())
              )) {
              winner = land;
              ratio = cat->getRatio(prod->getWaterConsumption());
            }
          }
        }
      }
      return true;
    });
    cout << "Final Winner of the month is " << winner->getFarmer()->getName() << "!" << "They got a ratio of " << ratio << endl;
  }

  private:
    void defaultPrompt(int &input)
    {
      system("cls");
      cout << setfill('=') << setw(40) << "" << endl
           << setfill(' ') << "** APMS System -- 1.3.77 -- All Rights Reserved" << endl
           << setfill('=') << setw(40) << "" << endl
           << setfill(' ') << "1: Print all lands" << endl
           << setfill('=') << setw(40) << "" << endl;
      while (std::cout << "Enter query: " && !(std::cin >> input))
      {
        std::cin.clear();                                                   // clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard input
        std::cout << endl
                  << "Invalid input; please re-enter.\n";
      }
    }
};



#endif