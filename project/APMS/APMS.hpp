#pragma once
#ifndef APMSDSA
#define APMSDSA
// #include <vector>
// #include <type_traits>
// #include <stdlib.h>
#include "misc/includes.hpp"
#include "misc/AvlTree.hpp"
#include "../lib/color.hpp"
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

  void save(string path) {
    cout << "Starting saving progress..." << endl;
    json j;
    wilayas.iterate([&j](Wilaya* wil) -> bool {
      j.push_back(*wil);
      return true;
    });
    rawFile.write(j, path);
  }

  void printLandWorkersByYear(int id, int year) {
    // Accessing the lands using the areas name using getById
    Area* area = areas.getById(id);
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

  void printMenu()
  {
    cout << setfill('=') << setw(60) << "" << endl
         << setfill(' ') << dye::yellow("** APMS System -- 1.3.77 -- All Rights Reserved") << endl
         << setfill('=') << setw(60) << dye::yellow("") << endl
         << setfill(' ') << dye::yellow("1: Access information") << endl
         << setfill(' ') << dye::yellow("2: Modify, add, or delete data") << endl
         << setfill(' ') << dye::yellow("3: Save changes into database") << endl
         << setfill(' ') << dye::yellow("0: Exit the terminal") << endl
         << setfill('=') << setw(60) << dye::yellow("") << endl;
  }

  void start() {
    int input = 0;
    printMenu();
    while(true) {
      promptAndValidate(input, "Enter query: ");
      switch (input) {
      case 1:
        readDataPrompt();
        break;
      case 2:
        getWinnerPrompt();
        break;
      
      default:
        cout << "This option does not exist. Try another one" << endl;
        input = 0;
        break;
      }
    }
  }

  void readDataPrompt() {
    int input = 0;
    cout << dye::blue("What would you like to access?") << endl
         << "1: Summarized information" << endl
         << "2: Detailed information" << endl
         << "3: Total sales" << endl
         << "4: Penalties" << endl
         << "5: Electricity Consumption" << endl
         << "6: Water Consumption" << endl;
    do {
      promptAndValidate(input, "Enter your query: ");
      switch(input) {
        case 1:
          cout << dye::blue("What information do you want to access?") << endl
               << "1: The entire database" << endl
               << "2: Information about a Wilaya" << endl
               << "3: Information about a City" << endl
               << "4: Information about an Area" << endl
               << "5: Information about a Land" << endl
               << "6: Information about a Farmer" << endl;
          do {
            promptAndValidate(input, "Enter your query: ");
            switch(input) {
              case 6:
                promptAndValidate(input, "Enter the farmer's ID: ");
                Farmer* desired = farmers.getById(input);
                if(desired) cout << *desired;
                else cout << "ERR: Farmer with this ID was not found" << endl;
            }
          } while(input);
      }
    } while(input);
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
    cout << dye::yellow("Winner in the ") << dye::green(category) << dye::yellow(" category:") << endl << *(winner->getFarmer()) << endl;
  }

  

  private:
    template <typename T>
    bool promptAndValidate(T& input, string message, bool is_integer = true/* , function<bool(T)> const& func */) {
      if(is_integer) {
        input = 0;
        while(!input) {
          cout << message;
          string str; size_t pos;
          getline(cin, str);
          // Check if string contains number so it can proceed
          bool contains_number = true;
          for(char ch: str) {
            if(!isdigit(ch)) {
              contains_number = false;
              break;
            }
          }
          if(contains_number) { 
            try {input = stoi(str, &pos);}
            catch(const std::out_of_range& e) {
              cout << dye::red("ERR: ID is beyond the range. Insert a more...logical number.") << endl;
              continue;
            }
            if(pos != str.size()) {
              // cin.clear();
              // #ifndef __INTELLISENSE__
              // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard input
              // #endif
              cout << dye::red("ERR: wrong input type. Please type again") << endl;
              input = 0;
            }
          } else {
            cout << dye::red("ERR: wrong input type. Please type again") << endl;
            input = 0;
          }
        }
      }
      return true;
    }

    void getWinnerPrompt() {
      int year = 0, month = 0, input = -1;
      while(input) {
        cout << dye::blue("How would you like to list the winners") << endl
             << "1: List all winners in all categories" << endl
             << "2: List all winner for a certain category" << endl
             << "3: List winners for a certain year" << endl
             << "4: List winners for a certain month" << endl;
        promptAndValidate(input, "Enter your query: ");
        switch(input) {
          case 4:
            while(!(year || month)) {
              promptAndValidate(year, "Enter the year: ");
              promptAndValidate(month, "Enter the month: ");
            }
            cout << "Select category from below: " << endl;
            int i = 1;
            for(string cat: categories) {
              cout << "Category " << i++ << ": " << cat << endl;
            }
            promptAndValidate(input, "Enter the category: ");
            while(input > 5 || input < 1) {
              cout << dye::red("ERR: input doesn't exist. Please try again");
              promptAndValidate(input, "Enter the category: ");
            }
            getWinner(year, month, categories[input - 1]);
            break;
        }
      }
    }

    void getLands() {
      int input = -1, year = 0, month = 0; Land* land = nullptr;
      cout << dye::blue("How would you like to access the lands? ") << endl
           << "1: List all lands" << endl
           << "2: List lands in a Wilaya" << endl
           << "3: List lands in a City" << endl
           << "4: List lands in a Area" << endl
           << "5: Access a specific land" << endl;
      while(input) {
        promptAndValidate(input, "Enter your query: ");
        switch (input)
        {
        case 1:
          cout << setfill('=') << setw(40) << "" << endl;
          wilayas.iterate([](Wilaya *wil) -> bool {
            cout << *wil << endl;
            return true; 
          });
          input = 0;
          break;
        case 5:
          int inputId;
          while(!land) {
            cout << dye::light_green("Enter the ID of the land: ");
            cin >> inputId;
            land = lands.getById(inputId);
            
            if(!land) cout << dye::red("ERR: Land not found") << endl;
          } 
          cout << *land;
          input = 0;
          break;


        default:
          break;
        }
      }
    } 

    
};



#endif