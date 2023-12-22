#pragma once
#ifndef APMSDSA
#define APMSDSA
// #include <vector>
// #include <type_traits>
// #include <stdlib.h>
#include "../lib/plot/pbPlots.hpp"
#include "../lib/plot/supportLib.hpp"
#include "misc/AvlTree.hpp"
// #include <color.hpp>
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

class APMS
{
  DBMS rawFile;
  BSTree<Wilaya *> wilayas;
  BSTree<City *> cities;
  BSTree<Area *> areas;
  BSTree<Land *> lands;
  BSTree<Farmer *> farmers;
  vector<string> categories;
  int start_year = 0;
  int end_year = 0;

  // vector<City>& addCities(auto cities) {

  // }

public:
  APMS() : wilayas{BSTree<Wilaya *>()}, cities{BSTree<City *>()}, areas{BSTree<Area *>()}, lands{BSTree<Land *>()}, rawFile{DBMS()}, farmers{BSTree<Farmer *>()}, categories{vector<string>()} {}
  APMS(const string &fpath) : rawFile{DBMS{fpath}}, wilayas{BSTree<Wilaya *>()}, cities{BSTree<City *>()}, areas{BSTree<Area *>()}, lands{BSTree<Land *>()}, farmers{BSTree<Farmer *>()}, categories{vector<string>()} {}

  void load()
  {
    rawFile.read();
    for (auto wil = rawFile.getFileData().begin(); wil != rawFile.getFileData().end(); wil++)
    {
      Wilaya *wilaya = new Wilaya();
      wilaya->setName((*wil)["name"]);
      wilaya->setId((*wil)["id"]);
      wilayas.insert(wilaya);
      for (auto city = (*wil)["cities"].begin(); city != (*wil)["cities"].end(); city++)
      {
        City *cit = new City();
        wilaya->addCity(cit);
        cit->setName((*city)["name"]);
        cit->setCityId((*city)["id"]);
        cities.insert(cit);
        for (auto area = (*city)["areas"].begin(); area != (*city)["areas"].end(); area++)
        {
          Area *ar = new Area();
          cit->addArea(ar);
          ar->setId((*area)["id"]);
          ar->setName((*area)["name"]);
          areas.insert(ar);
          for (auto land = (*area)["lands"].begin(); land != (*area)["lands"].end(); land++)
          {
            Land *lnd = new Land();
            ar->addLand(lnd);
            lnd->setId((*land)["id"]);
            Farmer *frmr = new Farmer(
                (*land)["farmer"]["id"],
                (*land)["farmer"]["age"],
                (*land)["farmer"]["name"],
                (*land)["farmer"]["gender"],
                lnd);
            lnd->setFarmer(frmr);
            farmers.insert(frmr);
            lands.insert(lnd);

            for (auto year = (*land)["report"].begin(); year != (*land)["report"].end(); year++)
            {
              AnnualReport *report = new AnnualReport();
              lnd->addYear(report);
              report->setYear((*year)["year"]);

              if(!start_year)
                start_year = (*year)["year"];
              if((*year)["year"] < start_year)
                start_year = (*year)["year"];
              if (!end_year)
                end_year = (*year)["year"];
              if ((*year)["year"] > end_year)
                end_year = (*year)["year"];
              for (auto worker = (*year)["workers"].begin(); worker != (*year)["workers"].end(); worker++)
              {
                Worker *wkr = new Worker(
                    (*worker)["id"],
                    (*worker)["age"],
                    (*worker)["name"],
                    (*worker)["gender"]);
                report->addWorker(wkr);
              }
              for (auto month = (*year)["months"].begin(); month != (*year)["months"].end(); month++)
              {
                MonthlyReport *mo = new MonthlyReport();
                report->addMonth(mo);
                mo->setMonth((*month)["month"]);
                auto landData = (*month)["data"];
                Production *lndData = new Production();
                mo->setProduction(lndData);
                unordered_map<string, ProductCategory *> prod;
                for (auto product = landData["products"].begin(); product != landData["products"].end(); product++)
                {
                  prod[(string)(*product)["name"]] = new ProductCategory(
                      (string)(*product)["name"],
                      (double)(*product)["basePrice"],
                      (double)(*product)["production"],
                      (PesticideSeverity)(*product)["pesticideSeverity"]);
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
          for (auto worker = (*report)->getWorkers().begin(); worker != (*report)->getWorkers().end(); worker++)
          {
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
         << setfill(' ') << dye::yellow("2: Save changes into database") << endl
         << setfill(' ') << dye::yellow("0: Exit the terminal") << endl
         << setfill('=') << setw(60) << dye::yellow("") << endl;
  }

  void start() {
    int input = 0; bool displayMenu = true;
    while(true) {
      if(displayMenu) {
        printMenu();
        displayMenu = false;
      }
      promptAndValidate(input, "Enter query: ");
      switch (input) {
      case 1:
        readDataPrompt(displayMenu);
        break;

      default:
        cout << "This option does not exist. Try another one" << endl;
        input = 0;
        break;
      }
    }
  }

  void readDataPrompt(bool& displayMenu) {
    int input = 0, input2,  year, month, isDetailed;
    cout << dye::blue("What would you like to access?") << endl
         << "1: General information" << endl
         << "2: Sales" << endl
         << "3: Penalties" << endl
         << "4: Winners in the monthly competition" << endl
         << "0: Return to main menu" << endl;
    do {
      Farmer* desired;
      promptAndValidate(input, "Enter your query: ");
      switch(input) {
        case 1:
          cout << dye::blue("What information do you want to access?") << endl
               << "1: Information about a Wilaya" << endl
               << "2: Information about a City" << endl
               << "3: Information about an Area" << endl
               << "4: Information about a Land" << endl
               << "5: Information about a Farmer" << endl
               << "6: Information about the entire Database" << endl
               << "0: Return to the main menu" << endl;
          do {
            promptAndValidate(input, "Enter your query: ", 0, 6);
            switch(input) {
              case 1:
                cout << dye::blue("How would you like to access the Wilaya information?") << endl
                     << "1: Data for a specific month" << endl
                     << "2: Data for a specific year" << endl
                     << "3: All available data" << endl;
                while(input) {
                  promptAndValidate(input, "Enter your query: ");
                  switch(input) {
                    case 1:
                      promptAndValidate(input2, "Enter the ID of the wilaya you want: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      promptAndValidate(month, "Enter the month you want: ");
                      promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                      if(isDetailed == 2) {
                        print_monthly_wilaya_info(input2, year, month - 1);
                      } else {
                         print_monthly_wilaya_summarized(input2, year, month - 1);
                      }
                      displayMenu = true;
                      return;
                    case 2:
                      promptAndValidate(input, "Enter the ID of the wilaya you want: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                      if(isDetailed == 2) {
                        print_yearly_wilaya_info(input, year, isDetailed - 1);
                      } else {
                        print_yearly_wilaya_summarized(input, year);
                      }
                      displayMenu = true;
                      return;
                    case 3:
                      promptAndValidate(input, "Enter the ID of the wilaya you want: ");
                      Wilaya* wil = wilayas.getById(input);
                      if(wil) {
                        cout << *wil << endl;
                        displayMenu = true;
                        return;
                      }
                      else {
                        cout << "Sorry, couldn't find the Wilaya you're looking for.";
                        displayMenu = true;
                        return;
                      }
                  }
                }
                return;
              case 2:
                cout << dye::blue("How would you like to access the City information?") << endl
                     << "1: Data for a specific month" << endl
                     << "2: Data for a specific year" << endl
                     << "3: All available data" << endl;
                while (input)
                {
                  promptAndValidate(input, "Enter your query: ");
                  switch (input)
                  {
                  case 1:
                    promptAndValidate(input2, "Enter the ID of the city you want: ");
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(month, "Enter the month you want: ");
                    promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                    if (isDetailed == 2)
                    {
                      print_monthly_city_info(input2, year, month - 1);
                    }
                    else
                    {
                      print_monthly_city_summarized(input2, year, month - 1);
                    }
                    displayMenu = true;
                    return;
                  case 2:
                    promptAndValidate(input, "Enter the ID of the city you want: ");
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                    if (isDetailed == 2)
                    {
                      print_yearly_city_info(input, year, isDetailed - 1);
                    }
                    else
                    {
                      print_yearly_city_summarized(input, year);
                    }
                    displayMenu = true;
                    return;
                  case 3:
                    promptAndValidate(input, "Enter the ID of the city you want: ");
                    City *cit = cities.getById(input);
                    if (cit)
                    {
                      cout << *cit << endl;
                      displayMenu = true;
                      return;
                    }
                    else
                    {
                      cout << "Sorry, couldn't find the City you're looking for.";
                      displayMenu = true;
                      return;
                    }
                  }
                }
                return;
              case 3:
                cout << dye::blue("How would you like to access the Area information?") << endl
                     << "1: Data for a specific month" << endl
                     << "2: Data for a specific year" << endl
                     << "3: All available data" << endl;
                while (input)
                {
                  promptAndValidate(input, "Enter your query: ");
                  switch (input)
                  {
                  case 1:
                    promptAndValidate(input2, "Enter the ID of the area you want: ");
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(month, "Enter the month you want: ");
                    promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                    if (isDetailed == 2)
                    {
                      print_monthly_area_info(input2, year, month - 1);
                    }
                    else
                    {
                      print_monthly_area_summarized(input2, year, month - 1);
                    }
                    displayMenu = true;
                    return;
                  case 2:
                    promptAndValidate(input, "Enter the ID of the area you want: ");
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                    if (isDetailed == 2)
                    {
                      print_yearly_area_info(input, year, isDetailed);
                    }
                    else
                    {
                      print_yearly_area_summarized(input, year);
                    }
                    displayMenu = true;
                    return;
                  case 3:
                    promptAndValidate(input, "Enter the ID of the area you want: ");
                    Area *ar = areas.getById(input);
                    if (ar)
                    {
                      cout << *ar << endl;
                      displayMenu = true;
                      return;
                    }
                    else
                    {
                      cout << "Sorry, couldn't find the Area you're looking for.";
                      displayMenu = true;
                      return;
                    }
                  }
                }
                return;
              case 4:
                cout << dye::blue("How would you like to access the Land information?") << endl
                     << "1: Data for a specific month" << endl
                     << "2: Data for a specific year" << endl
                     << "3: All available data" << endl;
                while (input)
                {
                  promptAndValidate(input, "Enter your query: ");
                  switch (input)
                  {
                  case 1:
                    promptAndValidate(input2, "Enter the ID of the land you want: ");
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(month, "Enter the month you want: ");
                    promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                    if (isDetailed == 2)
                    {
                      print_monthly_land_info(input2, year, month - 1);
                    }
                    else
                    {
                      print_monthly_land_summarized(input2, year, month - 1);
                    }
                    displayMenu = true;
                    return;
                  case 2:
                    promptAndValidate(input, "Enter the ID of the land you want: ");
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                    if (isDetailed == 2)
                    {
                      print_yearly_land_info(input, year, isDetailed - 1);
                    }
                    else
                    {
                      List_yearly_farmer_sales(input, year);
                    }
                    displayMenu = true;
                    return;
                  case 3:
                    promptAndValidate(input, "Enter the ID of the land you want: ");
                    Land *land = lands.getById(input);
                    if (land)
                    {
                      cout << *land << endl;
                      displayMenu = true;
                      return;
                    }
                    else
                    {
                      cout << "Sorry, couldn't find the Land you're looking for.";
                      displayMenu = true;
                      return;
                    }
                  }
                }
                return;
              case 5:
                promptAndValidate(input, "Enter the farmer's ID: ");
                desired = farmers.getById(input);
                if(desired) cout << *desired;
                else cout << "ERR: Farmer with this ID was not found" << endl;
                displayMenu = true;
                return;
              case 6:
                cout << dye::red_on_white("WARNING: ") << "This will print the entire database, resulting in " << dye::green("MILLIONS") << " of lines. Depending on your hardware, " << dye::black_on_white("the 3ND 0F TH3 UN1V3RS3") << " may come before its done printing. Are you sure you want to proceed? (1 for yes, 0 for no)" << endl;
                promptAndValidate(input, "Proceed?", 0, 1);
                switch(input) {
                  case 1:
                    cout << dye::blue("How would you like to access the Country information?") << endl
                         << "1: Data for a specific month" << endl
                         << "2: Data for a specific year" << endl
                         << "3: All available data" << endl;
                    while (input)
                    {
                      promptAndValidate(input, "Enter your query: ");
                      switch (input)
                      {
                      case 1:
                        promptAndValidate(year, "Enter the year you want: ");
                        promptAndValidate(month, "Enter the month you want: ");
                        promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                        if (isDetailed == 2)
                        {
                          print_monthly_country_info(year, month);
                        }
                        else
                        {
                          print_monthly_country_summarized(year, month);
                        }
                        displayMenu = true;
                        return;
                      case 2:
                        promptAndValidate(year, "Enter the year you want: ");
                        promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                        if (isDetailed - 1)
                        {
                          print_yearly_country_info(year, isDetailed - 1);
                        }
                        else
                        {
                          print_yearly_country_summarized(year);
                        }
                        displayMenu = true;
                        return;
                      case 3:
                        print_yearly_country_info(-1, 1);
                        break;
                      }
                    }
                    return;
                } 
            }
          } while(input);
          break;
        case 2:
          cout << dye::blue("What sales do you want to acesss?") << endl
               << "1: Sales in the Entire Country" << endl
               << "2: Sales in a Wilaya" << endl
               << "3: Sales in a City" << endl
               << "4: Sales in an Area" << endl
               << "5: Sales in a Land" << endl
               << "0: Return to the main menu" << endl;
          do {
            promptAndValidate(input, "Enter your query: ", 0, 5);
            switch(input) {
              case 1:
                cout << dye::red_on_white("WARNING: ") << "This will print the entire database, resulting in " << dye::green("MILLIONS") << " of lines. Depending on your hardware, " << dye::black_on_white("the 3ND 0F TH3 UN1V3RS3") << " may come before its done printing. Are you sure you want to proceed? (1 for yes, 0 for no)" << endl;
                promptAndValidate(input, "Proceed?", 0, 1);
                if(input) {
                  cout << dye::blue("What sales would you like to list?") << endl
                       << "1: Sales in a specific month" << endl
                       << "2: Sales for a specific year" << endl
                       << "0: Return to the main menu" << endl;
                       promptAndValidate(input, "Enter your query: ", 0, 4);
                       switch(input) {
                       case 1:
                         promptAndValidate(year, "Enter the year you want: ");
                         promptAndValidate(month, "Enter the month you want: ");
                         List_monthly_farmer_sales_in_country(year, month);
                         displayMenu = true;
                         return;
                       case 2:
                         promptAndValidate(year, "Enter the year you want: ");
                         List_yearly_farmer_sales_in_country(year);
                         displayMenu = true;
                         return;
                       }
                } else {
                  displayMenu = true;
                  return;
                }
              case 2:
                cout << dye::blue("What sales would you like to list?") << endl
                     << "1: Sales in a specific month" << endl
                     << "2: Sales for a specific year" << endl
                     << "3: All Sales" << endl;

                do {
                  promptAndValidate(input, "Enter your query: ", 1, 3);
                  switch(input) {
                    case 1:
                      promptAndValidate(input, "Enter the ID of the wilaya you want: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      promptAndValidate(month, "Enter the month you want: ");
                      List_monthly_farmer_sales_in_wilaya(input, year, month - 1);
                      displayMenu = true;
                      return;
                    case 2:
                      promptAndValidate(input, "Enter the ID of the wilaya you want: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      List_yearly_farmer_sales_in_wilaya(input, year);
                      displayMenu = true;
                      return;
                    case 3:
                      promptAndValidate(input, "Enter the ID of the wilaya you want: ");
                      List_yearly_farmer_sales_in_wilaya(input, -1);
                      displayMenu = true;
                      return;
                  }
                } while(input);
              case 3:
                cout << dye::blue("What sales would you like to list?") << endl
                     << "1: Sales in a specific month" << endl
                     << "2: Sales for a specific year" << endl
                     << "3: All Sales" << endl;

                do {
                  promptAndValidate(input, "Enter your query: ", 1, 3);
                  switch(input) {
                    case 1:
                      promptAndValidate(input, "Enter the ID of the City: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      promptAndValidate(month, "Enter the month you want: ");
                      List_monthly_farmer_sales_in_city(input, year, month - 1);
                      displayMenu = true;
                      return;
                    case 2:
                      promptAndValidate(input, "Enter the ID of the City");
                      promptAndValidate(year, "Enter the year you want: ");
                      List_yearly_farmer_sales_in_city(input, year);
                      displayMenu = true;
                      return;
                    case 3:
                      promptAndValidate(input, "Enter the ID of the City: ");
                      List_yearly_farmer_sales_in_city(input, -1);
                      displayMenu = true;
                      return;
                  }
                } while(input);
              case 4:
                cout << dye::blue("What sales would you like to list?") << endl
                     << "1: Sales in a specific month" << endl
                     << "2: Sales for a specific year" << endl
                     << "3: All Sales" << endl;

                do {
                  promptAndValidate(input, "Enter your query: ", 1, 3);
                  switch(input) {
                    case 1:
                      promptAndValidate(input, "Enter the ID of the Area: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      promptAndValidate(month, "Enter the month you want: ");
                      List_monthly_farmer_sales_in_area(input, year, month - 1);
                      displayMenu = true;
                      return;
                    case 2:
                      promptAndValidate(input, "Enter the ID of the Area");
                      promptAndValidate(year, "Enter the year you want: ");
                      List_yearly_farmer_sales_in_area(input, year);
                      displayMenu = true;
                      return;
                    case 3:
                      promptAndValidate(input, "Enter the ID of the Area: ");
                      List_yearly_farmer_sales_in_area(input, -1);
                      displayMenu = true;
                      return;
                  }
                } while(input);
              case 5:
                cout << dye::blue("What sales would you like to list?") << endl
                     << "1: Sales in a specific month" << endl
                     << "2: Sales for a specific year" << endl
                     << "3: All Sales" << endl;

                do {
                  promptAndValidate(input, "Enter your query: ", 1, 3);
                  switch(input) {
                    case 1:
                      promptAndValidate(input, "Enter the ID of the Land: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      promptAndValidate(month, "Enter the month you want: ");
                      List_monthly_farmer_sales(input, year, month - 1);
                      displayMenu = true;
                      return;
                    case 2:
                      promptAndValidate(input, "Enter the ID of the Land");
                      promptAndValidate(year, "Enter the year you want: ");
                      List_yearly_farmer_sales(input, year);
                      displayMenu = true;
                      return;
                    case 3:
                      promptAndValidate(input, "Enter the ID of the Land: ");
                      List_yearly_farmer_sales(input, -1);
                      displayMenu = true;
                      return;
                  }
                } while(input);
            }
          } while(input);
        case 3:
          cout << dye::blue("What Penalties would you like to access") << endl
               << "1: Penalties in the Whole Country" << endl
               << "2: Penalties in a Wilaya" << endl
               << "3: Penalties in a City" << endl
               << "4: Penalties in an Area" << endl
               << "5: Penalties in a Land" << endl
               << "0: Return to the main menu" << endl;
          do {
            promptAndValidate(input, "Enter your query: ", 0, 5);
            switch(input) {
              case 1:
                do
                {
                  cout << dye::red_on_white("WARNING: ") << "This will print the entire database, resulting in " << dye::green("MILLIONS") << " of lines. Depending on your hardware, " << dye::black_on_white("the 3ND 0F TH3 UN1V3RS3") << " may come before its done printing. Are you sure you want to proceed? (1 for yes, 0 for no)" << endl;
                  promptAndValidate(input, "Proceed?", 0, 1);
                  if (input)
                  {
                    cout << dye::blue("How would you like to access the Penalties?") << endl
                         << "1: Show Penalties in a specific month" << endl
                         << "2: Show Penalties in a specific year" << endl
                         << "0: Return to the main menu" << endl;
                    do
                    {
                      promptAndValidate(input, "Enter your query: ", 0, 3);
                      switch (input)
                      {
                      case 1:
                        promptAndValidate(year, "Enter the year you want");
                        promptAndValidate(month, "Enter the month you want");
                        cout << "In what category should the Penalties be for?" << endl;
                        for(int i = 0; i < categories.size(); i)
                          cout << i + 1 << ": " << categories[i] << endl;
                        cout << categories.size() << ": show all categories" << endl;
                        cout << "0: Return to the main menu" << endl;
                        promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                        if(input == categories.size())
                          for(const string& cat: categories)
                            List_country_monthly_farmers_penalties(year, month, cat);
                        else List_country_monthly_farmers_penalties(year, month, categories[input - 1]);
                        displayMenu = true;
                        return;
                      case 2:
                        promptAndValidate(year, "Enter the year you want");
                        cout << "In what category should the Penalties be for?" << endl;
                        for (int i = 0; i < categories.size(); ++i)
                          cout << i << ": " << categories[i] << endl;
                        cout << categories.size() << ": show all categories" << endl;
                        cout << "0: Return to the main menu" << endl;
                        promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                        if (input == categories.size())
                          for (const string &cat : categories)
                            List_country_monthly_farmers_penalties(year, month, cat);
                        else
                          List_country_monthly_farmers_penalties(year, month, categories[input - 1]);
                        return;
                        return;
                      }
                    } while (input);
                  }
                  else
                  {
                    displayMenu = true;
                    return;
                  }
                } while (input);
              case 2:
                promptAndValidate(input2, "Enter the ID of the wilaya: ");
                cout << dye::blue("How would you like to access the Penalties?") << endl
                     << "1: Show Penalties in a specific month" << endl
                     << "2: Show Penalties in a specific year" << endl
                     << "0: Return to the main menu" << endl;
                do
                {
                  promptAndValidate(input, "Enter your query: ", 0, 3);
                  switch (input)
                  {
                  case 1:
                    promptAndValidate(year, "Enter the year you want");
                    promptAndValidate(month, "Enter the month you want");
                    cout << "In what category should the Penalties be for?" << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_wilaya_monthly_farmers_penalties(input2, year, month - 1, cat);
                    else
                      List_wilaya_monthly_farmers_penalties(input2, year, month - 1, categories[input - 1]);
                    displayMenu = true;
                    return;
                  case 2:
                    promptAndValidate(year, "Enter the year you want");
                    cout << "In what category should the Penalties be for?" << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_wilaya_monthly_farmers_penalties(input2, year, month - 1, cat);
                    else
                      List_wilaya_monthly_farmers_penalties(input2, year, month - 1, categories[input - 1]);
                    displayMenu = true;
                    return;
                  }
                } while (input);
              case 3:
                promptAndValidate(input2, "Enter the ID of the city: ");
                cout << dye::blue("How would you like to access the Penalties?") << endl
                     << "1: Show Penalties in a specific month" << endl
                     << "2: Show Penalties in a specific year" << endl
                     << "0: Return to the main menu" << endl;
                do
                {
                  promptAndValidate(input, "Enter your query: ", 0, 3);
                  switch (input)
                  {
                  case 1:
                    promptAndValidate(year, "Enter the year you want");
                    promptAndValidate(month, "Enter the month you want");
                    cout << "In what category should the Penalties be for?" << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i << ": " << categories[i] << endl;
                     cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_city_monthly_farmers_penalties(input2, year, month - 1, cat);
                    else
                      List_city_monthly_farmers_penalties(input2, year, month - 1, categories[input - 1]);
                    displayMenu = true;
                    return;
                  case 2:
                    promptAndValidate(year, "Enter the year you want");
                    cout << "In what category should the Penalties be for?" << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_city_monthly_farmers_penalties(input2, year, month - 1, cat);
                    else
                      List_city_monthly_farmers_penalties(input2, year, month - 1, categories[input - 1]);
                    displayMenu = true;
                    return;
                  }
                } while (input);
              case 4:
                promptAndValidate(input2, "Enter the ID of the area: ");
                cout << dye::blue("How would you like to access the Penalties?") << endl
                     << "1: Show Penalties in a specific month" << endl
                     << "2: Show Penalties in a specific year" << endl
                     << "0: Return to the main menu" << endl;
                do
                {
                  promptAndValidate(input, "Enter your query: ", 0, 3);
                  switch (input)
                  {
                  case 1:
                    promptAndValidate(year, "Enter the year you want");
                    promptAndValidate(month, "Enter the month you want");
                    cout << "In what category should the Penalties be for?" << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_area_monthly_farmers_penalties(input2, year, month - 1, cat);
                    else
                      List_area_monthly_farmers_penalties(input2, year, month - 1, categories[input - 1]);
                    displayMenu = true;
                    return;
                  case 2:
                    promptAndValidate(year, "Enter the year you want");
                    cout << "In what category should the Penalties be for?" << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_area_monthly_farmers_penalties(input2, year, month - 1, cat);
                    else
                      List_area_monthly_farmers_penalties(input2, year, month - 1, categories[input - 1]);
                    displayMenu = true;
                    return;
                  }
                } while (input);
              case 5:
                promptAndValidate(input2, "Enter the ID of the land: ");
                cout << dye::blue("How would you like to access the Penalties?") << endl
                     << "1: Show Penalties in a specific month" << endl
                     << "2: Show Penalties in a specific year" << endl
                     << "0: Return to the main menu" << endl;
                do
                {
                  promptAndValidate(input, "Enter your query: ", 0, 3);
                  switch (input)
                  {
                  case 1:
                    promptAndValidate(year, "Enter the year you want");
                    promptAndValidate(month, "Enter the month you want");
                    cout << "In what category should the Penalties be for?" << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_monthly_farmer_penalty(input2, year, month - 1, cat);
                    else
                      List_monthly_farmer_penalty(input2, year, month - 1, categories[input - 1]);
                    return;
                  case 2:
                    promptAndValidate(year, "Enter the year you want");
                    cout << "In what category should the Penalties be for?" << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_monthly_farmer_penalty(input2, year, month - 1, cat);
                    else
                      List_monthly_farmer_penalty(input2, year, month - 1, categories[input - 1]);
                    return;
                    displayMenu = true;
                    return;
                  }
                } while (input);
              }
          } while(input);
        case 4:
          cout << dye::blue("Which category you want to list the winners of?") << endl;
          for(int i = 0; i < categories.size(); i++) 
            cout << i + 1 << ": " << categories[i] << endl;
          cout << categories.size() << ": Show for all categories" << endl;
          promptAndValidate(input, "Enter your query: ");
          promptAndValidate(year, "Enter the year you want: ");
          promptAndValidate(month,"Enter the month you want: ");
          if(input == categories.size())
            for(const string& cat: categories) 
              getWinner(year, month, cat);
          else 
            getWinner(year, month, categories[input - 1]);
        }
    } while(input);
  }

  void addCategory(string cat) {
    categories.push_back(cat);
  }

  void getWinner(int year, int month, string category)
  {
    // check if cateogries exists to begin with
    if (find(categories.begin(), categories.end(), category) == categories.end())
      return;

    Land *winner = nullptr;
    double ratio = 0;
    cout << "start winners loop..." << endl;
    lands.iterate([year, month, category, &winner, &ratio](Land *land) -> bool
      {
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
      return true; });
    cout << "Final Winner of the month is " << winner->getFarmer()->getName() << "!"
         << "They got a ratio of " << ratio << endl;
  }

private:
  void getLandsPrompt()
  {
    int input = -1, year = 0, month = 0;
    while (input)
    {
      cout << "How would you like to access the lands? " << endl
           << "1: List all lands" << endl
           << "2: List lands in a Wilaya" << endl
           << "3: List lands in a City" << endl
           << "4: List lands in a Area" << endl
           << "5: Access a specific land" << endl
           << "Enter your query number: ";
      cin >> input;
      switch (input)
      {
      case 1:
        cout << setfill('=') << setw(40) << "" << endl;
        wilayas.iterate([](Wilaya *wil) -> bool
                        {
            cout << *wil << endl;
            return true; });
        input = 0;
        break;

      default:
        break;
      }
    }
  }
  void getwilayas()
  {
    int input = -1;
    while (input)
    {
      cout << "How would you like to access the wilayas? " << endl
           << "1: List all wilayas" << endl
           << "2: Access a specific wilaya" << endl
           << "Enter your query number: ";
      cin >> input;
      switch (input)
      {
      case 1:
        cout << setfill('=') << setw(40) << "" << endl;
        wilayas.iterate([](Wilaya *wil) -> bool
                        {
            cout << *wil << endl;
            return true; });
        input = 0;
        break;
      case 2:
        cout << "Enter the wilaya id: ";
        cin >> input;
        cout << *wilayas.getById(input) << endl;
        input = 0;
        break;
      default:
        break;
      }
    }
  }

  void getcities()
  {
    int input = -1;
    while (input)
    {
      cout << "How would you like to access the cities? " << endl
           << "1: List all cities" << endl
           << "2: Access a specific city" << endl
           << "Enter your query number: ";
      cin >> input;
      switch (input)
      {
      case 1:
        cout << setfill('=') << setw(40) << "" << endl;
        cities.iterate([](City *city) -> bool
                       {
            cout << *city << endl;
            return true; });
        input = 0;
        break;
      case 2:
        cout << "Enter the city id: ";
        cin >> input;
        cout << *cities.getById(input) << endl;
        input = 0;
        break;
      default:
        break;
      }
    }
  }

  void getAreas()
  {
    int input = -1;
    while (input)
    {
      cout << "How would you like to access the areas? " << endl
           << "1: List all areas" << endl
           << "2: Access a specific area" << endl
           << "Enter your query number: ";
      cin >> input;
      switch (input)
      {
      case 1:
        cout << setfill('=') << setw(40) << "" << endl;
        areas.iterate([](Area *area) -> bool
                      {
            cout << *area << endl;
            return true; });
        input = 0;
        break;
      case 2:
        cout << "Enter the area id: ";
        cin >> input;
        cout << *areas.getById(input) << endl;
        input = 0;
        break;
      default:
        break;
      }
    }
  }
  // print land detailed info by  month
  void print_monthly_land_info(int landId, int year, int month)
  {
    Land *land = lands.getById(landId);
    //cheking if the land exists
    if (land != nullptr)
    {  cout << "Land ID: " << landId<< endl;
       cout << "Farmer: " << land->getFarmer()->getName() << endl;
       cout << setfill('=') << setw(40) << "" << endl;
      land->printMonthlyReport(year, month);
    }
    else
    {
      cout << "the land with ID " << landId << " doesn't exist" << endl;
    }
  }
  // print land detailed info by  year
  void print_yearly_land_info(int landId, int year,int choice)
  {
    Land *land = lands.getById(landId);
    //cheking if the land exists
    if (land != nullptr)
    {  
       if(year==-1)
       {
        //printing the info of the land in all the years using cout operator
        cout<<*land<<endl;

       }
      land->printAnnualReport(year,choice);
    }
    else
    {
      cout << "the land with ID " << landId << " doesn't exist" << endl;
    }
  }
  // print land summary info by  month
  void print_monthly_land_sales(int landid, int year, int month)
  {
    Land *land =lands.getById(landid);
    //cheking if the land exists
    if(land == nullptr) {
      cout << "the land with ID " << landid << " doesn't exist" << endl;
    }
    else{
    int result = land->get_land_total_sales_per_month(year, month); // contains the check if the land exists
    if (result != 0)
      cout << "the total sales of the land " << landid << " in the month " << month << " of the year " << year << " is :" << result << " DA" << endl;
    else
      cout << "  the land  " << landid << " has no sales in this month " << endl;
    }
  }
  // print land summary info by  year
  void print_yearly_land_sales(int landid, int year)
  {
    Land *land = lands.getById(landid);
    //cheking if the land exists
    if (land == nullptr)
    {
      cout << "the land with ID " << landid << " doesn't exist" << endl;
    }
    else
    {
      int result = land->get_land_total_sales_per_year(year); // contains the check if the land exists
      if (result != 0)
        cout << "the total sales of the land " << landid << " in the year " << year << " is :" << result << " DA" << endl;
      else
        cout << "  the land  " << landid << " has no sales in this year " << endl;
    }
  }

  // print area detailed info by  month
  void print_monthly_area_info(int areaId, int year, int month)
  {
    Area *area = areas.getById(areaId);
    //cheking if the area exists
    if (area != nullptr)
    {
      //printing the info of the area in all the years using cout operator
      if(year==-1)
      {
        cout<<*area<<endl;
        return;
      }
      cout << "Area ID: " << areaId<< endl;
      cout << "Area: " << area->getName() << endl;
      area->Print_Area_By_month(year, month);
    }
    else
    {
      cout << "the area with ID " << areaId << " doesn't exist" << endl;
    }
  }

  // print area detailed info by  year
  void print_yearly_area_info(int areaId, int year,int choice)
  {
    Area *area = areas.getById(areaId);
    //cheking if the area exists
    if (area != nullptr)
    {
      area->Print_Area_By_Year(year,choice);
    }
    else
    {
      cout << "the area with ID " << areaId << " doesn't exist" << endl;
    }
  
  }

  // print area summary info by  month
  void print_monthly_area_sales(int areaid, int year, int month)
  {
    Area *area = areas.getById(areaid);
    //cheking if the area exists
    if(area == nullptr) {
      cout << "the area with ID " << areaid << " doesn't exist" << endl;
    }
    else{
    int result = area->get_area_total_sales_per_month(year, month); // contains the check if the area exists
    if (result != 0)
      cout << "the total sales of the area " << area->getName() << "with ID : " << areaid << " in the month " << month << " of the year " << year << " is :" << result << " DA" << endl;
    else
      cout << "  the area  " << area->getName() << "with ID : " << areaid << " has no sales in this month " << endl;
  }
  }
  // print area summary info by  year
  void print_yearly_area_sales(int areaid, int year)
  {
    Area *area = areas.getById(areaid);
    //cheking if the area exists
    if(area == nullptr) {
      cout << "the area with ID " << areaid << " doesn't exist" << endl;
    }
    else{
    int result = area->get_area_total_sales_per_year(year); // contains the check if the area exists
    if (result != 0)
      cout << "the total sales of the area " << area->getName() << "with ID : " << areaid << " of the year " << year << " is :" << result << " DA" << endl;
    else
      cout << "  the area  " << area->getName() << "with ID : " << areaid << " has no sales in this month " << endl;
  }
  }

  // print city detailed info by  month
  void print_monthly_city_info(int cityId, int year, int month)
  {
    City *city = cities.getById(cityId);
    //cheking if the city exists
    if (city != nullptr)
    {
      //printing the info of the city in all the years using cout operator
      if(year==-1)
      {
        cout<<*city<<endl;
        return;
      }
       cout<<" city name :"<<city->getName()<<endl;
      cout<< " city id : "<< city->getId()<<endl;
      city->print_city_by_month(year, month);
    }
    else
    {
      cout << "the city with ID " << cityId << " doesn't exist" << endl;
    }
  }

  // print city detailed info by  year
  void print_yearly_city_info(int cityId, int year,int choice)
  {
    City *city = cities.getById(cityId);
    //cheking if the city exists
    if (city != nullptr)
    {   
      cout<<" city name :"<<city->getName()<<endl;
      cout<< " city id : "<< city->getId()<<endl;

      city->print_city_by_year(year,choice);
    }
    else
    {
      cout << "the city with ID " << cityId << " doesn't exist" << endl;
    }
   
  }

  // print city summary info by  month
  void print_monthly_city_sales(int cityid, int year, int month)
  {
    City *city = cities.getById(cityid);
    //cheking if the city exists
    if(city == nullptr) {
      cout << "the city with ID " << cityid << " doesn't exist" << endl;
    }
    else{
      
    int result = city->get_city_total_sales_per_month(year, month); // contains the check if the city exists
    if (result != 0)
      cout << "the total sales of the city " << city->getName() << "with ID : " << cityid << " in the month " << month << " of the year " << year << " is :" << result << " DA" << endl;
    else
      cout << "  the city  " << city->getName() << "with ID : " << cityid << " has no sales in this month " << endl;
  }
  }

  // print city summary info by  year
  void print_yearly_city_sales(int cityid, int year)
  {
    City *city = cities.getById(cityid);
    //cheking if the city exists
    if(city == nullptr) {
      cout << "the city with ID " << cityid << " doesn't exist" << endl;
    }
    else{
    int result = city->get_city_total_sales_per_year(year); // contains the check if the city exists
    if (result != 0)
      cout << "the total sales of the city " << city->getName() << "with ID : " << cityid << " in the year " << year << " is :" << result << " DA" << endl;
    else
      cout << "  the city  " << city->getName() << "with ID : " << cityid << " has no sales in this year " << endl;
  }
  }
  // print wilaya detailed info by  month
  void print_monthly_wilaya_info(int wilayaId, int year, int month)
  {
    Wilaya *wilaya = wilayas.getById(wilayaId);
    //cheking if the wilaya exists
    if (wilaya != nullptr)
    {
      //printing the info of the wilaya in all the years using cout operator
      if(year==-1)
      {
        cout<<*wilaya<<endl;
        return;
      }
      wilaya->print_wilaya_by_month(year, month);
    }
    else
    {
      cout << "the wilaya with ID " << wilayaId << " doesn't exist" << endl;
    }
  }

  // print wilaya detailed info by  year
  void print_yearly_wilaya_info(int wilayaId, int year,int choice)
  {
    Wilaya *wilaya = wilayas.getById(wilayaId);
    //cheking if the wilaya exists
    if (wilaya != nullptr)
    {
      wilaya->print_wilaya_by_year(year,choice);
    }
    else
    {
      cout << "the wilaya with ID " << wilayaId << " doesn't exist" << endl;
    }
  }

  // print wilaya summary info by  month
  void print_monthly_wilaya_sales(int wilayaid, int year, int month)
  {
    Wilaya *wilaya = wilayas.getById(wilayaid);
    //cheking if the wilaya exists
    if(wilaya == nullptr) {
      cout << "the wilaya with ID " << wilayaid << " doesn't exist" << endl;
    }
    else{
    int result = wilaya->get_wilaya_total_sales_per_month(year, month); // contains the check if the wilaya exists
    if (result != 0)
      cout << "the total sales of the wilaya " << wilaya->getName() << "with ID : " << wilayaid << " in the month " << month << " of the year " << year << " is :" << result << " DA" << endl;
    else
      cout << "  the wilaya  " << wilaya->getName() << "with ID : " << wilayaid << " has no sales in this month " << endl;
  }
  }

  // print wilaya summary info by  year
  void print_yearly_wilaya_sales(int wilayaid, int year)
  {
    Wilaya *wilaya = wilayas.getById(wilayaid);
    //cheking if the wilaya exists
    if(wilaya == nullptr) {
      cout << "the wilaya with ID " << wilayaid << " doesn't exist" << endl;
    }
    else{
    int result = wilaya->get_wilaya_total_sales_per_year(year); // contains the check if the wilaya exists
    if (result != 0)
      cout << "the total sales of the wilaya " << wilaya->getName() << "with ID : " << wilayaid << " in the year " << year << " is :" << result << " DA" << endl;
    else
      cout << "  the wilaya  " << wilaya->getName() << "with ID : " << wilayaid << " has no sales in this year " << endl;
  }
  }
  // print country detailed info by  month
  void print_monthly_country_info(int year, int month)
  {
    // iterating over all the wilayas
    int sum2=0;
      int sum1=0;
      int sum3=0;
    wilayas.iterate([year, month,&sum1,&sum2,&sum3](Wilaya *wilaya) -> bool
       {
      wilaya->print_wilaya_by_month(year, month);
      sum1+=wilaya->get_wilaya_total_sales_per_month(year, month);
      sum2+=wilaya->get_wilaya_monthly_water_consumption(year, month);
      sum3+=wilaya->get_wilaya_monthly_electricity_consumption(year, month);
      return true; });
      //printing the sums
      cout<<"the total sales of the country in the month "<<month<<" of the year "<<year<<" is :"<<sum1<<" DA"<<endl;
      cout<<"the total water consumption of the country in the month "<<month<<" of the year "<<year<<" is :"<<sum2<<" m³"<<endl;
      cout<<"the total electricity consumption of the country in the month "<<month<<" of the year "<<year<<" is :"<<sum3<<" KWh"<<endl;
  }
  // print country detailed info by  year
  void print_yearly_country_info(int year,int choice)
  {
     int sum2=0;
      int sum1=0;
      int sum3=0;
    // iterating over all the wilayas
    wilayas.iterate([year,choice,&sum1,&sum2,&sum3](Wilaya *wilaya) -> bool
     {
      wilaya->print_wilaya_by_year(year,choice);
      sum1+=wilaya->get_wilaya_total_sales_per_year(year);
      sum2+=wilaya->get_wilaya_yearly_water_consumption(year);
      sum3+=wilaya->get_wilaya_yearly_electricity_consumption(year);


      return true;
      });
      //printing the sums
      cout<<"the total sales of the country in the year "<<year<<" is :"<<sum1<<" DA"<<endl;
      cout<<"the total water consumption of the country in the year "<<year<<" is :"<<sum2<<" m³"<<endl;
      cout<<"the total electricity consumption of the country in the year "<<year<<" is :"<<sum3<<" KWh"<<endl;
  }
  // print country summary info by  month
  void print_monthly_country_sales(int year, int month)
  {
    int result = 0;
    // iterating over all the wilayas
    wilayas.iterate([year, month, &result](Wilaya *wilaya) -> bool
                    {
      result+=wilaya->get_wilaya_total_sales_per_month(year,month);
      return true; });
    if (result != 0)
      cout << "the total sales of the country in the month " << month << " of the year " << year << " is :" << result << " DA" << endl;
    else
      cout << "  the country has no sales in this month " << endl;
  }
  // print country summary info by  year
  void print_yearly_country_sales(int year)
  {
    int result = 0;
    // iterating over all the wilayas
    wilayas.iterate([year, &result](Wilaya *wilaya) -> bool
                    {
      result+=wilaya->get_wilaya_total_sales_per_year(year);
      return true; });
    if (result != 0)
      cout << "the total sales of the country in the year " << year << " is :" << result << " DA" << endl;
    else
      cout << "  the country has no sales in this year " << endl;
  }

  // Listing the sales of a farmer in a land in a month
  void List_monthly_farmer_sales(int LandID, int year, int month)
  {
    Land *land = lands.getById(LandID);
    //cheking if the land exists
    if (land != nullptr)
    {
      land->print_monthly_farmer_sales(year, month);
    }
    else
    {
      cout << "the land with ID " << LandID << " doesn't exist" << endl;
    }
  }
  // Listing all the sales of a farmer in a land in a year
  void List_yearly_farmer_sales(int LandID, int year)
  {
    Land *land = lands.getById(LandID);
    //cheking if the land exists
    if (land != nullptr)
    {
      land->print_yearly_farmer_sales(year);
    }
    else
    {
      cout << "the land with ID " << LandID << " doesn't exist" << endl;
    }
  }
  // Listing all the sales of a farmer in a area in a month
  void List_monthly_farmer_sales_in_area(int areaID, int year, int month)
  {
    Area *area = areas.getById(areaID);
    //cheking if the area exists
    if (area != nullptr)
    {
      area->print_area_monthly_farmer_sales(year, month);
    }
    else
    {
      cout << "the area with ID " << areaID << " doesn't exist" << endl;
    }
  }
  // Listing all the sales of a farmer in a area in a year
  void List_yearly_farmer_sales_in_area(int areaID, int year)
  {
    Area *area = areas.getById(areaID);
    //cheking if the area exists
    if (area != nullptr)
    {
      area->print_area_yearly_farmer_sales(year);
    }
    else
    {
      cout << "the area with ID " << areaID << " doesn't exist" << endl;
    }
  }
  // Listing all the sales of a farmer in a city in a month
  void List_monthly_farmer_sales_in_city(int cityID, int year, int month)
  {
    City *city = cities.getById(cityID);
    //cheking if the city exists
    if (city != nullptr)
    {
      city->print_city_monthly_farmer_sales(year, month);
    }
    else
    {
      cout << "the city with ID " << cityID << " doesn't exist" << endl;
    }
  }
  // Listing all the sales of a farmer in a city in a year
  void List_yearly_farmer_sales_in_city(int cityID, int year)
  {
    City *city = cities.getById(cityID);
    //cheking if the city exists
    if (city != nullptr)
    {
      city->print_city_yearly_farmer_sales(year);
    }
    else
    {
      cout << "the city with ID " << cityID << " doesn't exist" << endl;
    }
  }
  // Listing all the sales of a farmer in a wilaya in a month
  void List_monthly_farmer_sales_in_wilaya(int wilayaID, int year, int month)
  {
    Wilaya *wilaya = wilayas.getById(wilayaID);
    //cheking if the wilaya exists
    if (wilaya != nullptr)
    {
      wilaya->print_wilaya_monthly_farmer_sales(year, month);
    }
    else
    {
      cout << "the wilaya with ID " << wilayaID << " doesn't exist" << endl;
    }
  }
  // Listing all the sales of a farmer in a wilaya in a year
  void List_yearly_farmer_sales_in_wilaya(int wilayaID, int year)
  {
    Wilaya *wilaya = wilayas.getById(wilayaID);
    //cheking if the wilaya exists
    if (wilaya != nullptr)
    {
      wilaya->print_wilaya_yearly_farmer_sales(year);
    }
    else
    {
      cout << "the wilaya with ID " << wilayaID << " doesn't exist" << endl;
    }
  }
  // Listing all the sales of a farmer in a country in a month
  void List_monthly_farmer_sales_in_country(int year, int month)
  {
    // iterating over all the wilayas
    wilayas.iterate([year, month](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_monthly_farmer_sales(year,month);
      return true; });
  }
  // Listing all the sales of a farmer in a country in a year
  void List_yearly_farmer_sales_in_country(int year)
  {
    // iterating over all the wilayas
    wilayas.iterate([year](Wilaya *wilaya) -> bool {
      wilaya->print_wilaya_yearly_farmer_sales(year);
      return true; 
      });
    }
    


  

  private:
    template <typename T>
    bool promptAndValidate(T& input, string message, int min = 0, int max = 10000000, bool is_integer = true/* , function<bool(T)> const& func */) {
      if(is_integer) {
        input = 0;
        while(!input) {
          cout << message;
          string str; size_t pos;
          getline(cin, str);
          // Check if string contains number so it can proceed
          bool contains_number = true;
          if(!str.size()) contains_number = false;
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
      if(input > max || input < min) {
        cout << dye::red("ERR: input is outside of range, please type again") << endl;
        input = 0;
      }
      return true;
    }

    void getWinnerPrompt(bool& displayMenu) {
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
            displayMenu = true;
            break;
        }
      }
    }

    // void getLands() {
    //   int input = -1, year = 0, month = 0; Land* land = nullptr;
    //   cout << dye::blue("How would you like to access the lands? ") << endl
    //        << "1: List all lands" << endl
    //        << "2: List lands in a Wilaya" << endl
    //        << "3: List lands in a City" << endl
    //        << "4: List lands in a Area" << endl
    //        << "5: Access a specific land" << endl;
    //   while(input) {
    //     promptAndValidate(input, "Enter your query: ");
    //     switch (input)
    //     {
    //     case 1:
    //       cout << setfill('=') << setw(40) << "" << endl;
    //       wilayas.iterate([](Wilaya *wil) -> bool {
    //         cout << *wil << endl;
    //         return true; 
    //       });
    //       input = 0;
    //       break;
    //     case 5:
    //       int inputId;
    //       while(!land) {
    //         cout << dye::light_green("Enter the ID of the land: ");
    //         cin >> inputId;
    //         land = lands.getById(inputId);
            
    //         if(!land) cout << dye::red("ERR: Land not found") << endl;
    //       } 
    //       cout << *land;
    //       input = 0;
    //       break;


    //     default:
    //       break;
    //     }
    //   }
    // } 

  
  
  
  //listing the penalties of a farmer  in a month in a specific category
  void List_monthly_farmer_penalty(int landID, int year, int month, string category)
  {
    Land *land = lands.getById(landID);
    //cheking if the land exists
    if (land != nullptr)
    {
      land->print_Land_monthly_penalty(year, month, category);
    }
    else
    {
      cout << "the land with ID " << landID << " doesn't exist" << endl;
    }
  }
  //listing the penalties of a farmer  in a year in a specific category
  void List_yearly_farmer_penalty(int landID, int year, string category)
  {
    Land *land = lands.getById(landID);
    //cheking if the land exists
    if (land != nullptr)
    {
      land->print_Land_yearly_penalty(year, category);
    }
    else
    {
      cout << "the land with ID " << landID << " doesn't exist" << endl;
    }
  }
  //listing the penalties of a farmer  in a month in a specific category
  void List_area_monthly_farmers_penalties(int areaID, int year, int month, string category)
  {
    Area *area = areas.getById(areaID);
    //cheking if the area exists
    if (area != nullptr)
    {
      area->print_Area_monthly_penalty(year, month, category);
    }
    else
    {
      cout << "the area with ID " << areaID << " doesn't exist" << endl;
    }
  }
  //listing the penalties of a farmer  in a year in a specific category
  void List_area_yearly_farmers_penalties(int areaID, int year, string category)
  {
    Area *area = areas.getById(areaID);
    //cheking if the area exists
    if (area != nullptr)
    {
      area->print_Area_yearly_penalty(year, category);
    }
    else
    {
      cout << "the area with ID " << areaID << " doesn't exist" << endl;
    }
  }
  //listing the penalties of a farmer  in a month in a specific category
  void List_city_monthly_farmers_penalties(int cityID, int year, int month, string category)
  {
    City *city = cities.getById(cityID);
    //cheking if the city exists
    if (city != nullptr)
    {
      city->print_city_monthly_penalty(year, month, category);
    }
    else
    {
      cout << "the city with ID " << cityID << " doesn't exist" << endl;
    }
  }
  //listing the penalties of a farmer  in a year in a specific category
  void List_city_yearly_farmers_penalties(int cityID, int year, string category)
  {
    City *city = cities.getById(cityID);
    //cheking if the city exists
    if (city != nullptr)
    {
      city->print_city_yearly_penalty(year, category);
    }
    else
    {
      cout << "the city with ID " << cityID << " doesn't exist" << endl;
    }
  }
  //listing the penalties of a farmer  in a month in a specific category
  void List_wilaya_monthly_farmers_penalties(int wilayaID, int year, int month, string category)
  {
    Wilaya *wilaya = wilayas.getById(wilayaID);
    //cheking if the wilaya exists
    if (wilaya != nullptr)
    {
      wilaya->print_wilaya_monthly_penalty(year, month, category);
    }
    else
    {
      cout << "the wilaya with ID " << wilayaID << " doesn't exist" << endl;
    }
  }
  //listing the penalties of a farmer  in a year in a specific category
  void List_wilaya_yearly_farmers_penalties(int wilayaID, int year, string category)
  {
    Wilaya *wilaya = wilayas.getById(wilayaID);
    //cheking if the wilaya exists
    if (wilaya != nullptr)
    {
      wilaya->print_wilaya_yearly_penalty(year, category);
    }
    else
    {
      cout << "the wilaya with ID " << wilayaID << " doesn't exist" << endl;
    }
  }
  //listing the penalties of a farmer  in a month in a specific category
  void List_country_monthly_farmers_penalties(int year, int month, string category)
  {
    // iterating over all the wilayas
    wilayas.iterate([year, month, category](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_monthly_penalty(year, month, category);
      return true; });
  }
  //listing the penalties of a farmer  in a year in a specific category
  void List_country_yearly_farmers_penalties(int year, string category)
  {
    // iterating over all the wilayas
    wilayas.iterate([year, category](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_yearly_penalty(year, category);
      return true; });
  }

  //functions to print the summarized reports

  void print_monthly_land_summarized(int landID, int year,int month)
  {
    Land *land = lands.getById(landID);
    //cheking if the land exists
    if (land != nullptr)
    {
      land->print_monthly_summarized_report(year,month);
    }
    else
    {
      cout << "the land with ID " << landID << " doesn't exist" << endl;
    }
  }
  void print_yearly_land_summarized(int landID, int year)
  {
    Land *land = lands.getById(landID);
    //cheking if the land exists
    if (land != nullptr)
    {
      land->print_yearly_summarized_report(year);
    }
    else
    {
      cout << "the land with ID " << landID << " doesn't exist" << endl;
    }
  }

  void print_monthly_area_summarized(int areaID, int year,int month)
  {
    Area *area = areas.getById(areaID);
    //cheking if the area exists
    if (area != nullptr)
    {
      area->print_area_summerized_by_month(year,month);
    }
    else
    {
      cout << "the area with ID " << areaID << " doesn't exist" << endl;
    }
  }

  void print_yearly_area_summarized(int areaID, int year)
  {
    Area *area = areas.getById(areaID);
    //cheking if the area exists
    if (area != nullptr)
    {
      area->print_area_summerized_by_year(year);
    }
    else
    {
      cout << "the area with ID " << areaID << " doesn't exist" << endl;
    }
  }

  void print_monthly_city_summarized(int cityID, int year,int month)
  {
    City *city = cities.getById(cityID);
    //cheking if the city exists
    if (city != nullptr)
    {
      city->print_city_summarized_by_month(year,month);
    }
    else
    {
      cout << "the city with ID " << cityID << " doesn't exist" << endl;
    }
  }

  void print_yearly_city_summarized(int cityID, int year)
  {
    City *city = cities.getById(cityID);
    //cheking if the city exists
    if (city != nullptr)
    {
      city->print_city_summarized_by_year(year);
    }
    else
    {
      cout << "the city with ID " << cityID << " doesn't exist" << endl;
    }
  }

  void print_monthly_wilaya_summarized(int wilayaID, int year,int month)
  {
    Wilaya *wilaya = wilayas.getById(wilayaID);
    //cheking if the wilaya exists
    if (wilaya != nullptr)
    {
      wilaya->print_wilaya_summarized_by_month(year,month);
    }
    else
    {
      cout << "the wilaya with ID " << wilayaID << " doesn't exist" << endl;
    }
  }

  void print_yearly_wilaya_summarized(int wilayaID, int year)
  {
    Wilaya *wilaya = wilayas.getById(wilayaID);
    //cheking if the wilaya exists
    if (wilaya != nullptr)
    {
      wilaya->print_wilaya_summarized_by_year(year);
    }
    else
    {
      cout << "the wilaya with ID " << wilayaID << " doesn't exist" << endl;
    }
  }

  void print_monthly_country_summarized(int year,int month)
  {
    // iterating over all the wilayas
    wilayas.iterate([year, month](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_summarized_by_month(year,month);
      return true; });
  }

  void print_yearly_country_summarized(int year)
  {
    // iterating over all the wilayas
    wilayas.iterate([year](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_summarized_by_year(year);
      return true; });
  }


  void generatePlot(Land* land, int year) {
    vector<double> x, y;
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    AnnualReport* ar = land->getAnnualReport(year);
    if(!ar) {
      cout << dye::red("ERR: Data for this year doesn't exist. Perhaps the farmer/land started after it?") << endl;
      return;
    }
    for(int i = 0; i <ar->getMonths().size(); i++) {
      x.push_back(ar->getMonthlyReport(i)->getMonth());
      y.push_back(land->get_land_total_sales_per_month(year, i));
    }

    ScatterPlotSeries* series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    str << "Sales per year from " << land->getFarmer()->getName() << "'s Land over the year of " << year;
    settings->title = toVector(std::wstring(str.str().begin(), str.str().end()).c_str());
    settings->xLabel = toVector(L"Years");
    settings->yLabel = toVector(L"Sales");
    settings->scatterPlotSeries->push_back(series);
    StringReference* err = CreateStringReferenceLengthValue(0, L' ');
    bool success = DrawScatterPlotFromSettings(imageRef, settings, err);

    if(success) {
      cout << dye::green("Plot created successfully, generating...");
      vector<double>* pngdata = ConvertToPNG(imageRef->image);
      stringstream file_name;
      file_name << land->getId() << "_" << year << "_sales.png";
      // string file_name = land->getId() + "_" + year + "_sales.png";
      WriteToFile(pngdata, file_name.str());
      DeleteImage(imageRef->image);
      cout << dye::green("Plot Generated! opening...");
      system(file_name.str().c_str());
    }
  }

  void generatePlot(Land *land)
  {
    vector<double> x, y;
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    for (int i = 0; i < land->getReports().size(); i++)
    {
      x.push_back(land->getReports()[i]->getYear());
      y.push_back(land->get_land_total_sales_per_year(land->getReports()[i]->getYear()));
    }

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    str << "Sales per year from " << land->getFarmer()->getName() << "'s Land";
    settings->title = toVector(std::wstring(str.str().begin(), str.str().end()).c_str());
    settings->xLabel = toVector(L"Years");
    settings->yLabel = toVector(L"Sales");
    settings->scatterPlotSeries->push_back(series);
    StringReference *err = CreateStringReferenceLengthValue(0, L' ');
    bool success = DrawScatterPlotFromSettings(imageRef, settings, err);

    if (success)
    {
      cout << dye::green("Plot created successfully, generating...");
      vector<double> *pngdata = ConvertToPNG(imageRef->image);
      stringstream file_name;
      file_name << land->getId() << "_" << "_sales.png";
      // string file_name = land->getId() + "_" + year + "_sales.png";
      WriteToFile(pngdata, file_name.str());
      DeleteImage(imageRef->image);
      cout << dye::green("Plot Generated! opening...");
      system(file_name.str().c_str());
    }
  }
  void generatePlot(Area *area, int year)
  {
    vector<double> x, y;
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    // AnnualReport *ar = land->getAnnualReport(year);
    // if (!ar)
    // {
    //   cout << dye::red("ERR: Data for this year doesn't exist. Perhaps the farmer/land started after it?") << endl;
    //   return;
    // }
    for (int i = 0; i < 12; i++)
    {
      x.push_back(i + 1);
      y.push_back(area->get_area_total_sales_per_month(year, i));
    }

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    str << "Sales per year from area of " << area->getName() << " over the year of " << year;
    settings->title = toVector(std::wstring(str.str().begin(), str.str().end()).c_str());
    settings->xLabel = toVector(L"Years");
    settings->yLabel = toVector(L"Sales");
    settings->scatterPlotSeries->push_back(series);
    StringReference *err = CreateStringReferenceLengthValue(0, L' ');
    bool success = DrawScatterPlotFromSettings(imageRef, settings, err);

    if (success)
    {
      cout << dye::green("Plot created successfully, generating...");
      vector<double> *pngdata = ConvertToPNG(imageRef->image);
      stringstream file_name;
      file_name << area->getId() << "_" << year << "_sales.png";
      // string file_name = land->getId() + "_" + year + "_sales.png";
      WriteToFile(pngdata, file_name.str());
      DeleteImage(imageRef->image);
      cout << dye::green("Plot Generated! opening...");
      system(file_name.str().c_str());
    }
  }

  void generatePlot(Area *area)
  {
    vector<double> x, y;
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    // AnnualReport *ar = land->getAnnualReport(year);
    // if (!ar)
    // {
    //   cout << dye::red("ERR: Data for this year doesn't exist. Perhaps the farmer/land started after it?") << endl;
    //   return;
    // }
    for (int i = start_year; i < end_year; i++)
    {
      x.push_back(i);
      y.push_back(area->get_area_total_sales_per_year(i));
    }

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    str << "Sales per year from area of " << area->getName();
    settings->title = toVector(std::wstring(str.str().begin(), str.str().end()).c_str());
    settings->xLabel = toVector(L"Years");
    settings->yLabel = toVector(L"Sales");
    settings->scatterPlotSeries->push_back(series);
    StringReference *err = CreateStringReferenceLengthValue(0, L' ');
    bool success = DrawScatterPlotFromSettings(imageRef, settings, err);

    if (success)
    {
      cout << dye::green("Plot created successfully, generating...");
      vector<double> *pngdata = ConvertToPNG(imageRef->image);
      stringstream file_name;
      file_name << area->getId() << "_" << "_sales.png";
      // string file_name = land->getId() + "_" + year + "_sales.png";
      WriteToFile(pngdata, file_name.str());
      DeleteImage(imageRef->image);
      cout << dye::green("Plot Generated! opening...");
      system(file_name.str().c_str());
    }
  }
  void generatePlot(City *city, int year)
  {
    vector<double> x, y;
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    // AnnualReport *ar = land->getAnnualReport(year);
    // if (!ar)
    // {
    //   cout << dye::red("ERR: Data for this year doesn't exist. Perhaps the farmer/land started after it?") << endl;
    //   return;
    // }
    for (int i = 0; i < 12; i++)
    {
      x.push_back(i + 1);
      y.push_back(city->get_city_total_sales_per_month(year, i));
    }

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    str << "Sales per year from area of " << city->getName() << " over the year of " << year;
    settings->title = toVector(std::wstring(str.str().begin(), str.str().end()).c_str());
    settings->xLabel = toVector(L"Years");
    settings->yLabel = toVector(L"Sales");
    settings->scatterPlotSeries->push_back(series);
    StringReference *err = CreateStringReferenceLengthValue(0, L' ');
    bool success = DrawScatterPlotFromSettings(imageRef, settings, err);

    if (success)
    {
      cout << dye::green("Plot created successfully, generating...");
      vector<double> *pngdata = ConvertToPNG(imageRef->image);
      stringstream file_name;
      file_name << city->getId() << "_" << year << "_sales.png";
      // string file_name = land->getId() + "_" + year + "_sales.png";
      WriteToFile(pngdata, file_name.str());
      DeleteImage(imageRef->image);
      cout << dye::green("Plot Generated! opening...");
      system(file_name.str().c_str());
    }
  }

  void generatePlot(City *city)
  {
    vector<double> x, y;
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    // AnnualReport *ar = land->getAnnualReport(year);
    // if (!ar)
    // {
    //   cout << dye::red("ERR: Data for this year doesn't exist. Perhaps the farmer/land started after it?") << endl;
    //   return;
    // }
    for (int i = start_year; i < end_year; i++)
    {
      x.push_back(i);
      y.push_back(city->get_city_total_sales_per_year(i));
    }

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    str << "Sales per year from area of " << city->getName();
    settings->title = toVector(std::wstring(str.str().begin(), str.str().end()).c_str());
    settings->xLabel = toVector(L"Years");
    settings->yLabel = toVector(L"Sales");
    settings->scatterPlotSeries->push_back(series);
    StringReference *err = CreateStringReferenceLengthValue(0, L' ');
    bool success = DrawScatterPlotFromSettings(imageRef, settings, err);

    if (success)
    {
      cout << dye::green("Plot created successfully, generating...");
      vector<double> *pngdata = ConvertToPNG(imageRef->image);
      stringstream file_name;
      file_name << city->getId() << "_" << "_sales.png";
      // string file_name = land->getId() + "_" + year + "_sales.png";
      WriteToFile(pngdata, file_name.str());
      DeleteImage(imageRef->image);
      cout << dye::green("Plot Generated! opening...");
      system(file_name.str().c_str());
    }
  }
  void generatePlot(Wilaya *wilaya, int year)
  {
    vector<double> x, y;
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    // AnnualReport *ar = land->getAnnualReport(year);
    // if (!ar)
    // {
    //   cout << dye::red("ERR: Data for this year doesn't exist. Perhaps the farmer/land started after it?") << endl;
    //   return;
    // }
    for (int i = 0; i < 12; i++)
    {
      x.push_back(i + 1);
      y.push_back(wilaya->get_wilaya_total_sales_per_month(year, i));
    }

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    str << "Sales per year from area of " << wilaya->getName() << " over the year of " << year;
    settings->title = toVector(std::wstring(str.str().begin(), str.str().end()).c_str());
    settings->xLabel = toVector(L"Years");
    settings->yLabel = toVector(L"Sales");
    settings->scatterPlotSeries->push_back(series);
    StringReference *err = CreateStringReferenceLengthValue(0, L' ');
    bool success = DrawScatterPlotFromSettings(imageRef, settings, err);

    if (success)
    {
      cout << dye::green("Plot created successfully, generating...");
      vector<double> *pngdata = ConvertToPNG(imageRef->image);
      stringstream file_name;
      file_name << wilaya->getId() << "_" << year << "_sales.png";
      // string file_name = land->getId() + "_" + year + "_sales.png";
      WriteToFile(pngdata, file_name.str());
      DeleteImage(imageRef->image);
      cout << dye::green("Plot Generated! opening...");
      system(file_name.str().c_str());
    }
  }

  void generatePlot(Wilaya *wilaya)
  {
    vector<double> x, y;
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    // AnnualReport *ar = land->getAnnualReport(year);
    // if (!ar)
    // {
    //   cout << dye::red("ERR: Data for this year doesn't exist. Perhaps the farmer/land started after it?") << endl;
    //   return;
    // }
    for (int i = start_year; i < end_year; i++)
    {
      x.push_back(i);
      y.push_back(wilaya->get_wilaya_total_sales_per_year(i));
    }

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    str << "Sales per year from area of " << wilaya->getName();
    settings->title = toVector(std::wstring(str.str().begin(), str.str().end()).c_str());
    settings->xLabel = toVector(L"Years");
    settings->yLabel = toVector(L"Sales");
    settings->scatterPlotSeries->push_back(series);
    StringReference *err = CreateStringReferenceLengthValue(0, L' ');
    bool success = DrawScatterPlotFromSettings(imageRef, settings, err);

    if (success)
    {
      cout << dye::green("Plot created successfully, generating...");
      vector<double> *pngdata = ConvertToPNG(imageRef->image);
      stringstream file_name;
      file_name << wilaya->getId() << "_"
                << "_sales.png";
      // string file_name = land->getId() + "_" + year + "_sales.png";
      WriteToFile(pngdata, file_name.str());
      DeleteImage(imageRef->image);
      cout << dye::green("Plot Generated! opening...");
      system(file_name.str().c_str());
    }
  }
};

// void testPlot()
// {
//   // PlotConfig con("years", 2000.0, 2023.0, 200, "sales", 0.0, 5e+12);
//   // CustomPlot plot = createPlot("years", "sales", 2000, 2023, 0, 3e+5);
//   Land *land = lands.getById(216326);
//   vector<double> y, x;
//   RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
//   for (AnnualReport *rep : land->getReports())
//   {
//     cout << land->get_land_total_sales_per_year(rep->getYear()) << endl;
//     y.push_back(land->get_land_total_sales_per_year(rep->getYear()));
//     x.push_back(rep->getYear());
//   }
//   ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
//   series->xs = &x;
//   series->ys = &y;
//   series->lineThickness = 2;
//   ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
//   settings->height = 1024;
//   settings->width = 1024;
//   settings->title = toVector(L"Sales per year for farm");
//   settings->xLabel = toVector(L"Years");
//   settings->yLabel = toVector(L"Sales");
//   settings->scatterPlotSeries->push_back(series);
//   StringReference *idk = CreateStringReferenceLengthValue(0, L' ');
//   bool success = DrawScatterPlotFromSettings(imageRef, settings, idk);
//   cout << success;
//   if (success)
//   {
//     vector<double> *pngdata = ConvertToPNG(imageRef->image);
//     WriteToFile(pngdata, "test.png");
//     DeleteImage(imageRef->image);
//   }
//   FreeAllocations();
// }

#endif