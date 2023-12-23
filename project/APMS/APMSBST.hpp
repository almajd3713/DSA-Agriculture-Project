#pragma once
#ifndef APMSDSA
#define APMSDSA
// #include <vector>
// #include <type_traits>
// #include <stdlib.h>
#include "../lib/plot/supportLib.hpp"
// #include "misc/AvlTree.hpp"
// #include <color.hpp>
#include "misc/Trees.h"
#include "misc/DBMS.hpp"
#include "classes/wilaya.hpp"
#include <time.h>


class APMSBST
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
  APMSBST() : wilayas{BSTree<Wilaya *>()}, cities{BSTree<City *>()}, areas{BSTree<Area *>()}, lands{BSTree<Land *>()}, rawFile{DBMS()}, farmers{BSTree<Farmer *>()}, categories{vector<string>()} {}
  APMSBST(const string &fpath) : rawFile{DBMS{fpath}}, wilayas{BSTree<Wilaya *>()}, cities{BSTree<City *>()}, areas{BSTree<Area *>()}, lands{BSTree<Land *>()}, farmers{BSTree<Farmer *>()}, categories{vector<string>()} {}

  void load()
  {
    // std::time t1;
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
    cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl
    << setfill(' ') << dye::yellow("** APMSBST System -- 1.3.77 -- All Rights Reserved") << endl
    << dye::yellow("1: Access information") << endl
    << dye::yellow("2: Save changes into database") << endl
    << setfill(' ') << dye::yellow("0: Exit the terminal") << endl
    << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
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
    int input = 0, input2,  year, month, monthEnd, yearEnd, isDetailed;
    Wilaya* wil; City* cit; Area* ar; Land* land;
    cout << dye::blue("What would you like to access?") << endl
         << "1: General information" << endl
         << "2: Sales" << endl
         << "3: Penalties" << endl
         << "4: Winners in the monthly competition" << endl
         << "0: Return to main menu" << endl;
      Farmer* desired;
      promptAndValidate(input, "Enter your query: ", 0, 4);
      switch(input) {
        default:
          displayMenu = true;
          return;
        case 1:
          cout << dye::blue("What information do you want to access?") << endl
               << "1: Information about a Wilaya" << endl
               << "2: Information about a City" << endl
               << "3: Information about an Area" << endl
               << "4: Information about a Land" << endl
               << "5: Information about a Farmer" << endl
               << "6: Information about the entire Database" << endl
               << "0: Return to the main menu" << endl;
            promptAndValidate(input, "Enter your query: ", 0, 6);
            switch(input) {
              default:
                displayMenu = true;
                return;
              case 1:
                cout << dye::blue("How would you like to access the Wilaya information?") << endl
                     << "1: Data for a specific month" << endl
                     << "2: Data for a specific year" << endl
                     << "3: All available data" << endl
                     << "4: Data for a period" << endl
                     << "0: Return to the main menu" << endl;
                  promptAndValidate(input, "Enter your query: ", 0, 4);
                  switch(input) {
                    default:
                      displayMenu = true;
                      return;
                    case 1:
                      promptAndValidate(input2, "Enter the ID of the wilaya you want: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      promptAndValidate(month, "Enter the month you want: ", 1, 12);
                      promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                      if(isDetailed == 2) {
                        print_monthly_wilaya_info(input2, year, month);
                      } else {
                         print_monthly_wilaya_summarized(input2, year, month);
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
                      wil = wilayas.getById(input);
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
                    case 4:
                      promptAndValidate(input2, "Enter the ID of the wilaya you want: ");
                      promptAndValidate(year, "Enter the year you want to start with: ");
                      promptAndValidate(month, "Enter the month you want to start with: ");
                      promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                      promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                      promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                      if (isDetailed == 2)
                      {
                        print_period_wilaya_summarized(input2, year, month, yearEnd, monthEnd);
                      }
                      else
                      {
                        print_period_wilaya_info(input2, year, month, yearEnd, monthEnd);
                      }
                      displayMenu = true;
                      return;
                  }
                return;
              case 2:
                cout << dye::blue("How would you like to access the City information?") << endl
                     << "1: Data for a specific month" << endl
                     << "2: Data for a specific year" << endl
                     << "3: All available data" << endl
                     << "4: Data for a period" << endl
                     << "0: Return to the main menu" << endl;
                promptAndValidate(input, "Enter your query: ", 0, 4);
                switch (input)
                {
                  default:
                    displayMenu = true;
                    return;
                  case 1:
                    promptAndValidate(input2, "Enter the ID of the city you want: ");
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(month, "Enter the month you want: ", 1, 12);
                    promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                    if (isDetailed == 2)
                    {
                      print_monthly_city_info(input2, year, month);
                    }
                    else
                    {
                      print_monthly_city_summarized(input2, year, month);
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
                    cit = cities.getById(input);
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
                  case 4:
                    promptAndValidate(input2, "Enter the ID of the city you want: ");
                    promptAndValidate(year, "Enter the year you want to start with: ");
                    promptAndValidate(month, "Enter the month you want to start with: ");
                    promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                    promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                    promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                    if (isDetailed == 2)
                    {
                      print_period_city_summarized(input2, year, month, yearEnd, monthEnd);
                    }
                    else
                    {
                      print_period_city_info(input2, year, month, yearEnd, monthEnd);
                    }
                    displayMenu = true;
                    return;
                  }
                return;
              case 3:
                cout << dye::blue("How would you like to access the Area information?") << endl
                     << "1: Data for a specific month" << endl
                     << "2: Data for a specific year" << endl
                     << "3: All available data" << endl
                     << "4: Data for a period" << endl
                     << "0: Return to the main menu" << endl;
                promptAndValidate(input, "Enter your query: ", 0, 4);
                switch (input)
                {
                  default:
                    displayMenu = true;
                    return;
                  case 1:
                    promptAndValidate(input2, "Enter the ID of the area you want: ");
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(month, "Enter the month you want: ", 1, 12);
                    promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                    if (isDetailed == 2)
                    {
                      print_monthly_area_info(input2, year, month);
                    }
                    else
                    {
                      print_monthly_area_summarized(input2, year, month);
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
                    ar = areas.getById(input);
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
                  case 4:
                    promptAndValidate(input2, "Enter the ID of the area you want: ");
                    promptAndValidate(year, "Enter the year you want to start with: ");
                    promptAndValidate(month, "Enter the month you want to start with: ");
                    promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                    promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                    promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                    if (isDetailed == 2)
                    {
                      print_period_area_summarized(input2, year, month, yearEnd, monthEnd);
                    }
                    else
                    {
                      print_period_area_info(input2, year, month, yearEnd, monthEnd);
                    }
                    displayMenu = true;
                    return;
                  }
                return;
              case 4:
                cout << dye::blue("How would you like to access the Land information?") << endl
                     << "1: Data for a specific month" << endl
                     << "2: Data for a specific year" << endl
                     << "3: All available data" << endl
                     << "4: Data for a period" << endl
                     << "0: Return to the main menu" << endl;
                promptAndValidate(input, "Enter your query: ", 0, 4);
                switch (input)
                {
                  default:
                    displayMenu = true;
                    return;
                  case 1:
                    promptAndValidate(input2, "Enter the ID of the land you want: ");
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(month, "Enter the month you want: ", 1, 12);
                    promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                    if (isDetailed == 2)
                    {
                      print_monthly_land_info(input2, year, month);
                    }
                    else
                    {
                      print_monthly_land_summarized(input2, year, month);
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
                    land = lands.getById(input);
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
                  case 4:
                    promptAndValidate(input2, "Enter the ID of the land you want: ");
                    promptAndValidate(year, "Enter the year you want to start with: ");
                    promptAndValidate(month, "Enter the month you want to start with: ");
                    promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                    promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                    promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                    if (isDetailed == 2)
                    {
                      print_period_land_summarized(input2, year, month, yearEnd, monthEnd);
                    }
                    else
                    {
                      print_period_land_info(input2, year, month, yearEnd, monthEnd);
                    }
                    displayMenu = true;
                    return;
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
                         << "3: All available data" << endl
                         << "4: Data for a period" << endl
                         << "0: Return to the main menu" << endl;
                    while (input)
                    {
                      promptAndValidate(input, "Enter your query: ", 0, 4);
                      switch (input)
                      {
                        default:
                          displayMenu = true;
                          return;
                        case 1:
                          promptAndValidate(year, "Enter the year you want: ");
                          promptAndValidate(month, "Enter the month you want: ", 1, 12);
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
                          displayMenu = true;
                        case 4:
                          promptAndValidate(year, "Enter the year you want to start with: ");
                          promptAndValidate(month, "Enter the month you want to start with: ");
                          promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                          promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                          promptAndValidate(isDetailed, "Do you want the summarized or detailed version? (2 for detailed, 1 for summarized): ", 1, 2);
                          if (isDetailed == 2)
                          {
                            print_period_country_summarized( year, month, yearEnd, monthEnd);
                          }
                          else
                          {
                            print_period_country_info(year, month, yearEnd, monthEnd);
                          }
                          displayMenu = true;
                          return;
                      }
                    }
                    return;
                } 
                
            }
          break;
        case 2:
          cout << dye::blue("What sales do you want to acesss?") << endl
               << "1: Sales in the Entire Country" << endl
               << "2: Sales in a Wilaya" << endl
               << "3: Sales in a City" << endl
               << "4: Sales in an Area" << endl
               << "5: Sales in a Land" << endl
               << "0: Return to the main menu" << endl;
            promptAndValidate(input, "Enter your query: ", 0, 5);
            Wilaya* wil; City* cit; Area* ar; Land* lnd;
            switch(input) {
              default:
                displayMenu = true;
                return;
              case 1:
                cout << dye::red_on_white("WARNING: ") << "This will print the entire database, resulting in " << dye::green("MILLIONS") << " of lines. Depending on your hardware, " << dye::black_on_white("the 3ND 0F TH3 UN1V3RS3") << " may come before its done printing. Are you sure you want to proceed? (1 for yes, 0 for no)" << endl;
                promptAndValidate(input, "Proceed?", 0, 1);
                if(input) {
                  cout << dye::blue("What sales would you like to list?") << endl
                       << "1: Sales in a specific month" << endl
                       << "2: Sales for a specific year" << endl
                       << "3: Sales for a period"
                       << "0: Return to the main menu" << endl;
                       promptAndValidate(input, "Enter your query: ", 0, 3);
                       switch(input) {
                        default:
                          displayMenu = true;
                          return;
                       case 1:
                         promptAndValidate(year, "Enter the year you want: ");
                         promptAndValidate(month, "Enter the month you want: ", 1, 12);
                         List_monthly_farmer_sales_in_country(year, month);
                         displayMenu = true;
                         return;
                       case 2:
                         promptAndValidate(year, "Enter the year you want: ");
                         List_yearly_farmer_sales_in_country(year);
                         displayMenu = true;
                         return;
                       case 3:
                         promptAndValidate(year, "Enter the year you want to start with: ");
                         promptAndValidate(month, "Enter the month you want to start with: ");
                         promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                         promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                         print_period_country_sales(year, month, yearEnd, monthEnd);
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
                     << "3: All Sales" << endl
                     << "4: Sales for a period" << endl
                     << "0: Return to the main menu" << endl;

                  promptAndValidate(input, "Enter your query: ", 0, 4);
                  switch(input) {
                    default:
                      displayMenu = true;
                      return;
                    case 1:
                      promptAndValidate(input, "Enter the ID of the wilaya you want: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      promptAndValidate(month, "Enter the month you want: ", 1, 12);
                      List_monthly_farmer_sales_in_wilaya(input, year, month);
                      displayMenu = true;
                      return;
                    case 2:
                      promptAndValidate(input, "Enter the ID of the wilaya you want: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      List_yearly_farmer_sales_in_wilaya(input, year);
                      wil = wilayas.getById(input);
                      if(wil) {
                        promptAndValidate(input2, "Would you like to generate a Plot table for this data? (yes=1, no=0)");
                        if(input2) generatePlot(wil, year);
                      }
                      displayMenu = true;
                      return;
                    case 3:
                      promptAndValidate(input, "Enter the ID of the wilaya you want: ");
                      List_yearly_farmer_sales_in_wilaya(input, -1);
                      wil = wilayas.getById(input);
                      if (wil)
                      {
                        promptAndValidate(input2, "Would you like to generate a Plot table for this data? (yes=1, no=0)");
                        if (input2) generatePlot(wil);
                      }
                      displayMenu = true;
                      return;
                    case 4:
                      print_period_city_sales(input2, year, month, yearEnd, monthEnd);
                      promptAndValidate(year, "Enter the year you want to start with: ");
                      promptAndValidate(month, "Enter the month you want to start with: ");
                      promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                      promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                      print_period_wilaya_sales(input2, year, month, yearEnd, monthEnd);
                      displayMenu = true;
                      return;
                  }
              case 3:
                cout << dye::blue("What sales would you like to list?") << endl
                     << "1: Sales in a specific month" << endl
                     << "2: Sales for a specific year" << endl
                     << "3: All Sales" << endl
                     << "4: Sales for a period" << endl
                     << "0: Return to the main menu" << endl;

                  promptAndValidate(input, "Enter your query: ", 0, 4);
                  switch(input) {
                                  default:
                displayMenu = true;
                return;
                    case 1:
                      promptAndValidate(input, "Enter the ID of the City: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      promptAndValidate(month, "Enter the month you want: ", 1, 12);
                      List_monthly_farmer_sales_in_city(input, year, month);
                      displayMenu = true;
                      return;
                    case 2:
                      promptAndValidate(input, "Enter the ID of the City");
                      promptAndValidate(year, "Enter the year you want: ");
                      List_yearly_farmer_sales_in_city(input, year);
                      cit = cities.getById(input);
                      if(cit) {
                        promptAndValidate(input2, "Would you like to generate a Plot table for this data? (yes=1, no=0)");
                        if(input2) generatePlot(cit, year);
                      }
                      displayMenu = true;
                      return;
                    case 3:
                      promptAndValidate(input, "Enter the ID of the City: ");
                      List_yearly_farmer_sales_in_city(input, -1);
                      cit = cities.getById(input);
                      if (cit)
                      {
                        promptAndValidate(input2, "Would you like to generate a Plot table for this data? (yes=1, no=0)");
                        if (input2) generatePlot(cit);
                      }
                      displayMenu = true;
                      return;
                    case 4:
                      promptAndValidate(input2, "Enter the ID of the City: ");
                      promptAndValidate(year, "Enter the year you want to start with: ");
                      promptAndValidate(month, "Enter the month you want to start with: ");
                      promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                      promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                      print_period_city_sales(input2, year, month, yearEnd, monthEnd);
                      displayMenu = true;
                      return;
                  }
              case 4:
                cout << dye::blue("What sales would you like to list?") << endl
                     << "1: Sales in a specific month" << endl
                     << "2: Sales for a specific year" << endl
                     << "3: All Sales" << endl
                     << "4: Sales  for a period" << endl
                     << "0: Return to the main menu" << endl;

                  promptAndValidate(input, "Enter your query: ", 0, 4);
                  switch(input) {
                    default:
                      displayMenu = true;
                      return;
                    case 1:
                      promptAndValidate(input, "Enter the ID of the Area you want: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      promptAndValidate(month, "Enter the month you want: ", 1, 12);
                      List_monthly_farmer_sales_in_area(input, year, month);
                      displayMenu = true;
                      return;
                    case 2:
                      promptAndValidate(input, "Enter the ID of the Area you want: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      List_yearly_farmer_sales_in_area(input, year);
                      displayMenu = true;
                      ar = areas.getById(input);
                      if(ar) {
                        promptAndValidate(input2, "Would you like to generate a Plot table for this data? (yes=1, no=0)");
                        if(input2) generatePlot(ar, year);
                      }
                      return;
                    case 3:
                      promptAndValidate(input, "Enter the ID of the Area you want: ");
                      List_yearly_farmer_sales_in_area(input, -1);
                      displayMenu = true;
                      ar = areas.getById(input);
                      if (ar)
                      {
                        promptAndValidate(input2, "Would you like to generate a Plot table for this data? (yes=1, no=0)");
                        if (input2) generatePlot(ar);
                      }
                      return;
                    case 4:
                      promptAndValidate(input2, "Enter the ID of the Area: ");
                      promptAndValidate(year, "Enter the year you want to start with: ");
                      promptAndValidate(month, "Enter the month you want to start with: ");
                      promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                      promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                      print_period_area_sales(input2, year, month, yearEnd, monthEnd);
                      displayMenu = true;
                      return;
                  }
              case 5:
                cout << dye::blue("What sales would you like to list?") << endl
                     << "1: Sales in a specific month" << endl
                     << "2: Sales for a specific year" << endl
                     << "3: All Sales" << endl
                     << "4: Sales for a period" << endl
                     << "0: Return to the main menu" << endl;

                  promptAndValidate(input, "Enter your query: ", 0, 4);
                  switch(input) {
                    default:
                      displayMenu = true;
                      return;
                    case 1:
                      promptAndValidate(input, "Enter the ID of the Land: ");
                      promptAndValidate(year, "Enter the year you want: ");
                      promptAndValidate(month, "Enter the month you want: ", 1, 12);
                      List_monthly_farmer_sales(input, year, month);
                      displayMenu = true;
                      return;
                    case 2:
                      promptAndValidate(input, "Enter the ID of the Land");
                      promptAndValidate(year, "Enter the year you want: ");
                      List_yearly_farmer_sales(input, year);
                      lnd = lands.getById(input);
                      if (lnd)
                      {
                        promptAndValidate(input2, "Would you like to generate a Plot table for this data? (yes=1, no=0)");
                        if(input2)
                          generatePlot(lnd, year);
                      }
                      displayMenu = true;
                      return;
                    case 3:
                      promptAndValidate(input, "Enter the ID of the Land: ");
                      List_yearly_farmer_sales(input, -1);
                      lnd = lands.getById(input);
                      if (lnd)
                      {
                        promptAndValidate(input2, "Would you like to generate a Plot table for this data? (yes=1, no=0)");
                        if (input2)
                          generatePlot(lnd);
                      }
                      displayMenu = true;
                      return;
                    case 4:
                      promptAndValidate(input2, "Enter the ID of the Land: ");
                      promptAndValidate(year, "Enter the year you want to start with: ");
                      promptAndValidate(month, "Enter the month you want to start with: ");
                      promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                      promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                      print_period_land_sales(input2, year, month, yearEnd, monthEnd);
                      displayMenu = true;
                      return;
                  }
            }
        case 3:
          cout << dye::blue("What Penalties would you like to access") << endl
               << "1: Penalties in the Whole Country" << endl
               << "2: Penalties in a Wilaya" << endl
               << "3: Penalties in a City" << endl
               << "4: Penalties in an Area" << endl
               << "5: Penalties in a Land" << endl
               << "0: Return to the main menu" << endl;
            promptAndValidate(input, "Enter your query: ", 0, 5);
            switch(input) {
              default:
                displayMenu = true;
                return;
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
                         << "3: Show Penalties for a period" << endl
                         << "0: Return to the main menu" << endl;
                    do
                    {
                      promptAndValidate(input, "Enter your query: ", 0, 3);
                      switch (input)
                      {
                      default:
                        displayMenu = true;
                        return;
                      case 1:
                        promptAndValidate(year, "Enter the year you want: ");
                        promptAndValidate(month, "Enter the month you want: ", 1, 12);
                        cout << dye::blue("In what category should the Penalties be for?") << endl;
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
                        promptAndValidate(year, "Enter the year you want: ");
                        cout << dye::blue("In what category should the Penalties be for?") << endl;
                        for (int i = 0; i < categories.size(); ++i)
                          cout << i + 1 << ": " << categories[i] << endl;
                        cout << categories.size() << ": show all categories" << endl;
                        cout << "0: Return to the main menu" << endl;
                        promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                        if (input == categories.size())
                          for (const string &cat : categories)
                            List_country_monthly_farmers_penalties(year, month, cat);
                        else
                          List_country_monthly_farmers_penalties(year, month, categories[input - 1]);
                        displayMenu = true;
                        return;
                      case 3:
                        promptAndValidate(year, "Enter the year you want to start with: ");
                        promptAndValidate(month, "Enter the month you want to start with: ");
                        promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                        promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                        cout << dye::blue("In what category should the Penalties be for?") << endl;
                        for (int i = 0; i < categories.size(); ++i)
                          cout << i + 1 << ": " << categories[i] << endl;
                        cout << categories.size() << ": show all categories" << endl;
                        cout << "0: Return to the main menu" << endl;
                        promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                        if (input == categories.size())
                          for (const string &cat : categories)
                            List_period_country_monthly_farmers_penalties(year, month, yearEnd, monthEnd, cat);
                        else
                          List_period_country_monthly_farmers_penalties(year, month, yearEnd, monthEnd, categories[input - 1]);
                        displayMenu = true;
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
                     << "3: Show Penaltiers for a period" << endl
                     << "0: Return to the main menu" << endl;
                  promptAndValidate(input, "Enter your query: ", 0, 3);
                  switch (input)
                  {
                  default:
                    displayMenu = true;
                    return;
                  case 1:
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(month, "Enter the month you want: ", 1, 12);
                    cout << dye::blue("In what category should the Penalties be for?") << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i + 1 << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_wilaya_monthly_farmers_penalties(input2, year, month, cat);
                    else
                      List_wilaya_monthly_farmers_penalties(input2, year, month, categories[input - 1]);
                    displayMenu = true;
                    return;
                  case 2:
                    promptAndValidate(year, "Enter the year you want: ");
                    cout << dye::blue("In what category should the Penalties be for?") << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i + 1 << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_wilaya_monthly_farmers_penalties(input2, year, month, cat);
                    else
                      List_wilaya_monthly_farmers_penalties(input2, year, month, categories[input - 1]);
                    displayMenu = true;
                    return;
                  case 3:
                    promptAndValidate(year, "Enter the year you want to start with: ");
                    promptAndValidate(month, "Enter the month you want to start with: ");
                    promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                    promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                    cout << dye::blue("In what category should the Penalties be for?") << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i + 1 << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_period_wilaya_monthly_farmers_penalties(input2, year, month, yearEnd, monthEnd, cat);
                    else
                      List_period_wilaya_monthly_farmers_penalties(input2, year, month, yearEnd, monthEnd, categories[input - 1]);
                    displayMenu = true;
                    return;
                  }
              case 3:
                promptAndValidate(input2, "Enter the ID of the city: ");
                cout << dye::blue("How would you like to access the Penalties?") << endl
                     << "1: Show Penalties in a specific month" << endl
                     << "2: Show Penalties in a specific year" << endl
                     << "3: Show Penalties for a period" << endl
                     << "0: Return to the main menu" << endl;
                  promptAndValidate(input, "Enter your query: ", 0, 3);
                  switch (input)
                  {
                  case 1:
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(month, "Enter the month you want: ", 1, 12);
                    cout << dye::blue("In what category should the Penalties be for?") << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i + 1 << ": " << categories[i] << endl;
                     cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_city_monthly_farmers_penalties(input2, year, month, cat);
                    else
                      List_city_monthly_farmers_penalties(input2, year, month, categories[input - 1]);
                    displayMenu = true;
                    return;
                  case 2:
                    promptAndValidate(year, "Enter the year you want: ");
                    cout << dye::blue("In what category should the Penalties be for?") << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i + 1 << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_city_monthly_farmers_penalties(input2, year, month, cat);
                    else
                      List_city_monthly_farmers_penalties(input2, year, month, categories[input - 1]);
                    displayMenu = true;
                    return;
                  case 3:
                    promptAndValidate(year, "Enter the year you want to start with: ");
                    promptAndValidate(month, "Enter the month you want to start with: ");
                    promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                    promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                    cout << dye::blue("In what category should the Penalties be for?") << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i + 1 << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_period_city_monthly_farmers_penalties(input2, year, month, yearEnd, monthEnd, cat);
                    else
                      List_period_city_monthly_farmers_penalties(input2, year, month, yearEnd, monthEnd, categories[input - 1]);
                    displayMenu = true;
                    return;
                  }
              case 4:
                promptAndValidate(input2, "Enter the ID of the area: ");
                cout << dye::blue("How would you like to access the Penalties?") << endl
                     << "1: Show Penalties in a specific month" << endl
                     << "2: Show Penalties in a specific year" << endl
                     << "3: Show Penalties for a period" << endl
                     << "0: Return to the main menu" << endl;

                  promptAndValidate(input, "Enter your query: ", 0, 3);
                  switch (input)
                  {
                  default:
                    displayMenu = true;
                    return;
                  case 1:
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(month, "Enter the month you want: ", 1, 12);
                    cout << dye::blue("In what category should the Penalties be for?") << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i + 1 << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_area_monthly_farmers_penalties(input2, year, month, cat);
                    else
                      List_area_monthly_farmers_penalties(input2, year, month, categories[input - 1]);
                    displayMenu = true;
                    return;
                  case 2:
                    promptAndValidate(year, "Enter the year you want: ");
                    cout << dye::blue("In what category should the Penalties be for?") << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i + 1 << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_area_monthly_farmers_penalties(input2, year, month, cat);
                    else
                      List_area_monthly_farmers_penalties(input2, year, month, categories[input - 1]);
                    displayMenu = true;
                    return;
                  case 3:
                    promptAndValidate(year, "Enter the year you want to start with: ");
                    promptAndValidate(month, "Enter the month you want to start with: ");
                    promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                    promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                    cout << dye::blue("In what category should the Penalties be for?") << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i + 1 << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_period_area_monthly_farmers_penalties(input2, year, month, yearEnd, monthEnd, cat);
                    else
                      List_period_area_monthly_farmers_penalties(input2, year, month, yearEnd, monthEnd, categories[input - 1]);
                    displayMenu = true;
                    return;
                  }
              case 5:
                promptAndValidate(input2, "Enter the ID of the land: ");
                cout << dye::blue("How would you like to access the Penalties?") << endl
                     << "1: Show Penalties in a specific month" << endl
                     << "2: Show Penalties in a specific year" << endl
                     << "3: Show Penalties for a period" << endl
                     << "0: Return to the main menu" << endl;

                  promptAndValidate(input, "Enter your query: ", 0, 3);
                  switch (input)
                  {
                  default:
                    displayMenu = true;
                    return;
                  case 1:
                    promptAndValidate(year, "Enter the year you want: ");
                    promptAndValidate(month, "Enter the month you want: ", 1, 12);
                    cout << dye::blue("In what category should the Penalties be for?") << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i + 1 << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_monthly_farmer_penalty(input2, year, month, cat);
                    else
                      List_monthly_farmer_penalty(input2, year, month, categories[input - 1]);
                    return;
                  case 2:
                    promptAndValidate(year, "Enter the year you want: ");
                    cout << dye::blue("In what category should the Penalties be for?") << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i + 1 << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_monthly_farmer_penalty(input2, year, month, cat);
                    else
                      List_monthly_farmer_penalty(input2, year, month, categories[input - 1]);
                    return;
                    displayMenu = true;
                    return;
                  case 3:
                    promptAndValidate(year, "Enter the year you want to start with: ");
                    promptAndValidate(month, "Enter the month you want to start with: ");
                    promptAndValidate(yearEnd, "Enter the year you want to end with: ");
                    promptAndValidate(monthEnd, "Enter the month you want to end with: ");
                    cout << dye::blue("In what category should the Penalties be for?") << endl;
                    for (int i = 0; i < categories.size(); ++i)
                      cout << i + 1 << ": " << categories[i] << endl;
                    cout << categories.size() << ": show all categories" << endl;
                    cout << "0: Return to the main menu" << endl;
                    promptAndValidate(input, "Enter your query: ", 0, categories.size() - 1);
                    if (input == categories.size())
                      for (const string &cat : categories)
                        List_period_farmer_penalty(input2, year, month, yearEnd, monthEnd, cat);
                    else
                      List_period_farmer_penalty(input2, year, month, yearEnd, monthEnd, categories[input - 1]);
                    displayMenu = true;
                    return;
                  }
              }
        case 4:
          cout << dye::blue("Which category you want to list the winners of?") << endl;
          for(int i = 1; i <= categories.size(); i++) 
            cout << i + 1 << ": " << categories[i] << endl;
          cout << categories.size() << ": Show for all categories" << endl;
          promptAndValidate(input, "Enter your query: ");
          promptAndValidate(year, "Enter the year you want: ");
          promptAndValidate(month,"Enter the month you want: ", 1, 12);
          if(input == categories.size())
            for(const string& cat: categories) 
              getWinner(year, month, cat);
          else 
            getWinner(year, month, categories[input - 1]);
        }
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
  // void getLandsPrompt()
  // {
  //   int input = -1, year = 0, month = 0;
  //   while (input)
  //   {
  //     cout << "How would you like to access the lands? " << endl
  //          << "1: List all lands" << endl
  //          << "2: List lands in a Wilaya" << endl
  //          << "3: List lands in a City" << endl
  //          << "4: List lands in a Area" << endl
  //          << "5: Access a specific land" << endl
  //          << "Enter your query number: ";
  //     cin >> input;
  //     switch (input)
  //     {
  //     case 1:
  //       cout << setfill('=') << setw(40) << "" << endl;
  //       wilayas.iterate([](Wilaya *wil) -> bool
  //                       {
  //           cout << *wil << endl;
  //           return true; });
  //       input = 0;
  //       break;

  //     default:
  //       break;
  //     }
  //   }
  // }
  // void getwilayas()
  // {
  //   int input = -1;
  //   while (input)
  //   {
  //     cout << "How would you like to access the wilayas? " << endl
  //          << "1: List all wilayas" << endl
  //          << "2: Access a specific wilaya" << endl
  //          << "Enter your query number: ";
  //     cin >> input;
  //     switch (input)
  //     {
  //     case 1:
  //       cout << setfill('=') << setw(40) << "" << endl;
  //       wilayas.iterate([](Wilaya *wil) -> bool
  //                       {
  //           cout << *wil << endl;
  //           return true; });
  //       input = 0;
  //       break;
  //     case 2:
  //       cout << "Enter the wilaya id: ";
  //       cin >> input;
  //       cout << *wilayas.getById(input) << endl;
  //       input = 0;
  //       break;
  //     default:
  //       break;
  //     }
  //   }
  // }

  // void getcities()
  // {
  //   int input = -1;
  //   while (input)
  //   {
  //     cout << "How would you like to access the cities? " << endl
  //          << "1: List all cities" << endl
  //          << "2: Access a specific city" << endl
  //          << "Enter your query number: ";
  //     cin >> input;
  //     switch (input)
  //     {
  //     case 1:
  //       cout << setfill('=') << setw(40) << "" << endl;
  //       cities.iterate([](City *city) -> bool
  //                      {
  //           cout << *city << endl;
  //           return true; });
  //       input = 0;
  //       break;
  //     case 2:
  //       cout << "Enter the city id: ";
  //       cin >> input;
  //       cout << *cities.getById(input) << endl;
  //       input = 0;
  //       break;
  //     default:
  //       break;
  //     }
  //   }
  // }

  // void getAreas()
  // {
  //   int input = -1;
  //   while (input)
  //   {
  //     cout << "How would you like to access the areas? " << endl
  //          << "1: List all areas" << endl
  //          << "2: Access a specific area" << endl
  //          << "Enter your query number: ";
  //     cin >> input;
  //     switch (input)
  //     {
  //     case 1:
  //       cout << setfill('=') << setw(40) << "" << endl;
  //       areas.iterate([](Area *area) -> bool
  //                     {
  //           cout << *area << endl;
  //           return true; });
  //       input = 0;
  //       break;
  //     case 2:
  //       cout << "Enter the area id: ";
  //       cin >> input;
  //       cout << *areas.getById(input) << endl;
  //       input = 0;
  //       break;
  //     default:
  //       break;
  //     }
  //   }
  // }
  // print land detailed info by  month
  void print_monthly_land_info(int landId, int year, int month)
  {
    Land *land = lands.getById(landId);
    //cheking if the land exists
    if (land != nullptr)
    {  
      cout << "Land ID: " << landId<< endl;
       cout << "Farmer: " << land->getFarmer()->getName() << endl;
      land->printMonthlyReport(year, month);
    }
    else
    {
      cout << "the land with ID " << landId << " doesn't exist" << endl;
    }
  }
 // print land detailed info in a period
  void print_period_land_info(int landId, int year1, int month1,int year2,int month2)
  {
    Land *land = lands.getById(landId);
   //iterating over the years from specific month and calling  print_monthly_land_info
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)  
      {
        for(int j=month1;j<=12;j++)
        {
          print_monthly_land_info(landId,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          print_monthly_land_info(landId,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          print_monthly_land_info(landId,i,j);
        }
      }
    }
  }

  // print land detailed info by  year
  void print_yearly_land_info(int landId, int year,int choice)
  {
    Land *land = lands.getById(landId);
    //cheking if the land exists
    if (land != nullptr)
    {
      if (year == -1)
      {
        for (int i = start_year; i < 2024; i++)
          land->print_yearly_farmer_sales(i);
      }
      else
        land->print_yearly_farmer_sales(year);
      // land->printAnnualReport(year,choice);
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
    if (result != 0){
      cout << "the total sales of the land " << landid << " in the month " << month << " of the year " << year << " is :" << result <<(result > 1000000 ? result / 1000000 : result > 1000 ? result / 1000 : result); 
  cout<<(result > 1000000 ? "MDA" : result > 1000 ? "KDA" : "DA")<<endl;
  }
    else
      cout << "  the land  " << landid << " has no sales in this month " << endl;
    }
  }
  //print land summary info in a period
  void print_period_land_sales(int landid, int year1, int month1,int year2,int month2)
  {
    Land *land =lands.getById(landid);
    //iterating over the years from specific month and calling  print_monthly_land_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          print_monthly_land_sales(landid,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          print_monthly_land_sales(landid,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          print_monthly_land_sales(landid,i,j);
        }
      }
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
      if (result != 0){
        cout << "the total sales of the land " << landid << " in the year " << year << " is :" << result <<(result > 1000000 ? result / 1000000 : result > 1000 ? result / 1000 : result); 
  cout<<(result > 1000000 ? "MDA" : result > 1000 ? "KDA" : "DA")<<endl;
  }
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
        for(int i = start_year; i < 2024; i++)
          for(int j = 1; j <= 12; j++)
            area->print_area_monthly_farmer_sales(i, j);
      }
      // cout << "Area ID: " << areaId<< endl;
      // cout << "Area: " << area->getName() << endl;
      // area->Print_Area_By_month(year, month);
    }
    else
    {
      cout << "the area with ID " << areaId << " doesn't exist" << endl;
    }
  }

  //print area detailed info in a period
  void print_period_area_info(int areaId, int year1, int month1,int year2,int month2)
  {
    Area *area = areas.getById(areaId);
    //iterating over the years from specific month and calling  print_monthly_area_info
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          print_monthly_area_info(areaId,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          print_monthly_area_info(areaId,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          print_monthly_area_info(areaId,i,j);
        }
      }
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
    if (result != 0){
      cout << "the total sales of the area " << area->getName() << "with ID : " << areaid << " in the month " << month << " of the year " << year << " is :" << result <<(result > 1000000 ? result / 1000000 : result > 1000 ? result / 1000 : result); 
  cout<<(result > 1000000 ? "MDA" : result > 1000 ? "KDA" : "DA")<<endl;
  }
    else
      cout << "  the area  " << area->getName() << "with ID : " << areaid << " has no sales in this month " << endl;
  }
  }
//print area summary info in a period
  void print_period_area_sales(int areaid, int year1, int month1,int year2,int month2)
  {
    Area *area = areas.getById(areaid);
    //iterating over the years from specific month and calling  print_monthly_area_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          print_monthly_area_sales(areaid,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          print_monthly_area_sales(areaid,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          print_monthly_area_sales(areaid,i,j);
        }
      }
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
    if (result != 0){
      cout << "the total sales of the area " << area->getName() << "with ID : " << areaid << " of the year " << year << " is :" << result <<(result > 1000000 ? result / 1000000 : result > 1000 ? result / 1000 : result); 
  cout<<(result > 1000000 ? "MDA" : result > 1000 ? "KDA" : "DA")<<endl;
  }
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
      if (year == -1)
      {
        for (int i = start_year; i < 2024; i++)
          for(int j = 1; j <= 12; j++)
            city->print_city_monthly_farmer_sales(i, j);
      }
      else
        city->print_city_monthly_farmer_sales(year, month);
      //  cout<<" city name :"<<city->getName()<<endl;
      // cout<< " city id : "<< city->getId()<<endl;
      // city->print_city_by_month(year, month);
    }
    else
    {
      cout << "the city with ID " << cityId << " doesn't exist" << endl;
    }
  }
  //print city detailed info in a period
  void print_period_city_info(int cityId, int year1, int month1,int year2,int month2)
  {
    City *city = cities.getById(cityId);
    //iterating over the years from specific month and calling  print_monthly_city_info
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          print_monthly_city_info(cityId,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          print_monthly_city_info(cityId,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          print_monthly_city_info(cityId,i,j);
        }
      }
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
    if (result != 0){
      cout << "the total sales of the city " << city->getName() << "with ID : " << cityid << " in the month " << month << " of the year " << year << " is :" << result <<(result > 1000000 ? result / 1000000 : result > 1000 ? result / 1000 : result); 
  cout<<(result > 1000000 ? "MDA" : result > 1000 ? "KDA" : "DA")<<endl;
  }
    else
      cout << "  the city  " << city->getName() << "with ID : " << cityid << " has no sales in this month " << endl;
  }
  }
  //print city summary info in a period
  void print_period_city_sales(int cityid, int year1, int month1,int year2,int month2)
  {
    City *city = cities.getById(cityid);
    //iterating over the years from specific month and calling  print_monthly_city_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          print_monthly_city_sales(cityid,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          print_monthly_city_sales(cityid,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          print_monthly_city_sales(cityid,i,j);
        }
      }
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
    if (result != 0){
      cout << "the total sales of the city " << city->getName() << "with ID : " << cityid << " in the year " << year << " is :" << result <<(result > 1000000 ? result / 1000000 : result > 1000 ? result / 1000 : result); 
  cout<<(result > 1000000 ? "MDA" : result > 1000 ? "KDA" : "DA")<<endl;
  }
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
      if (year == -1)
      {
        for (int i = start_year; i < 2024; i++)
          for (int j = 1; j <= 12; j++)
            wilaya->print_wilaya_monthly_farmer_sales(i, j);
      }
      else
        wilaya->print_wilaya_monthly_farmer_sales(year, month);
    }
    else
    {
      cout << "the wilaya with ID " << wilayaId << " doesn't exist" << endl;
    }
  }
  //print wilaya detailed info in a period
  void print_period_wilaya_info(int wilayaId, int year1, int month1,int year2,int month2)
  {
    Wilaya *wilaya = wilayas.getById(wilayaId);
    //iterating over the years from specific month and calling  print_monthly_wilaya_info
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          print_monthly_wilaya_info(wilayaId,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          print_monthly_wilaya_info(wilayaId,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          print_monthly_wilaya_info(wilayaId,i,j);
        }
      }
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
    if (result != 0){
      cout << "the total sales of the wilaya " << wilaya->getName() << "with ID : " << wilayaid << " in the month " << month << " of the year " << year << " is :" << result <<(result > 1000000 ? result / 1000000 : result > 1000 ? result / 1000 : result); 
  cout<<(result > 1000000 ? "MDA" : result > 1000 ? "KDA" : "DA")<<endl;
  }
    else
      cout << "  the wilaya  " << wilaya->getName() << "with ID : " << wilayaid << " has no sales in this month " << endl;
  }
  }
  //print wilaya summary info in a period
  void print_period_wilaya_sales(int wilayaid, int year1, int month1,int year2,int month2)
  {
    Wilaya *wilaya = wilayas.getById(wilayaid);
    //iterating over the years from specific month and calling  print_monthly_wilaya_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          print_monthly_wilaya_sales(wilayaid,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          print_monthly_wilaya_sales(wilayaid,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          print_monthly_wilaya_sales(wilayaid,i,j);
        }
      }
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
    if (result != 0){
      cout << "the total sales of the wilaya " << wilaya->getName() << "with ID : " << wilayaid << " in the year " << year << " is :" << result <<(result > 1000000 ? result / 1000000 : result > 1000 ? result / 1000 : result); 
  cout<<(result > 1000000 ? "MDA" : result > 1000 ? "KDA" : "DA")<<endl;
  }
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
      cout<<"the total sales of the country in the month "<<month<<" of the year "<<year<<" is :"<<sum1 <<(sum1 > 1000000 ? sum1 / 1000000 : sum1 > 1000 ? sum1 / 1000 : sum1); 
  cout<<(sum1 > 1000000 ? "MDA" : sum1 > 1000 ? "KDA" : "DA")<<endl;
      cout<<"the total water consumption of the country in the month "<<month<<" of the year "<<year<<" is :"<<  sum2<<(sum2 > 1000000 ? sum2 / 1000000 :  sum2);
  cout<<(sum2 > 1000000 ? "dam^3" : "m^3")<<endl;
      cout<<"the total electricity consumption of the country in the month "<<month<<" of the year "<<year<<" is :"<<  sum3<<(sum3 > 1000000 ? sum3 / 1000 : sum3);
  cout<<(sum3 > 1000000 ? "Mwh" :  "kwh")<<endl;
  }
  //print country detailed info in a period
  void print_period_country_info(int year1, int month1,int year2,int month2)
  {
    // iterating over all the wilayas
    int sum2=0;
      int sum1=0;
      int sum3=0;
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          wilayas.iterate([i, j,&sum1,&sum2,&sum3](Wilaya *wilaya) -> bool
       {
      wilaya->print_wilaya_by_month(i, j);
      sum1+=wilaya->get_wilaya_total_sales_per_month(i, j);
      sum2+=wilaya->get_wilaya_monthly_water_consumption(i, j);
      sum3+=wilaya->get_wilaya_monthly_electricity_consumption(i, j);
      return true; });
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          wilayas.iterate([i, j,&sum1,&sum2,&sum3](Wilaya *wilaya) -> bool
       {
      wilaya->print_wilaya_by_month(i, j);
      sum1+=wilaya->get_wilaya_total_sales_per_month(i, j);
      sum2+=wilaya->get_wilaya_monthly_water_consumption(i, j);
      sum3+=wilaya->get_wilaya_monthly_electricity_consumption(i, j);
      return true; });
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          wilayas.iterate([i, j,&sum1,&sum2,&sum3](Wilaya *wilaya) -> bool
       {
      wilaya->print_wilaya_by_month(i, j);
      sum1+=wilaya->get_wilaya_total_sales_per_month(i, j);
      sum2+=wilaya->get_wilaya_monthly_water_consumption(i, j);
      sum3+=wilaya->get_wilaya_monthly_electricity_consumption(i, j);
      return true; });
        }
      }
    }
    //printing the sums
      cout<<"the total sales of the country in the period from "<<month1<<"/"<<year1<<" to "<<month2<<"/"<<year2<<" is :"<<  sum1 <<(sum1 > 1000000 ? sum1 / 1000000 : sum1 > 1000 ? sum1 / 1000 : sum1); 
  cout<<(sum1 > 1000000 ? "MDA" : sum1 > 1000 ? "KDA" : "DA")<<endl;
      cout<<"the total water consumption of the country in the period from "<<month1<<"/"<<year1<<" to "<<month2<<"/"<<year2<<" is :"<< sum2<<(sum2 > 1000000 ? sum2 / 1000000 :  sum2);
  cout<<(sum2 > 1000000 ? "dam^3" : "m^3")<<endl;
      cout<<"the total electricity consumption of the country in the period from "<<month1<<"/"<<year1<<" to "<<month2<<"/"<<year2<<" is :"<<  sum3<<(sum3 > 1000000 ? sum3 / 1000 : sum3);
  cout<<(sum3 > 1000000 ? "Mwh" :  "kwh")<<endl;
  }
   
  // print country detailed info by  year
  void print_yearly_country_info(int year,int choice)
  {
     int sum2=0;
      int sum1=0;
      int sum3=0;
    // iterating over all the wilayas
    int sy = start_year;
    wilayas.iterate([year,choice,&sum1,&sum2,&sum3, sy](Wilaya *wilaya) -> bool
     {
      for(int i = sy; i < 2024; i++) {
        wilaya->print_wilaya_by_year(year, choice);
        sum1 += wilaya->get_wilaya_total_sales_per_year(year);
        sum2 += wilaya->get_wilaya_yearly_water_consumption(year);
        sum3 += wilaya->get_wilaya_yearly_electricity_consumption(year);
      }


      return true;
      });
      //printing the sums
      cout<<"the total sales of the country in the year "<<year<<" is :"<<  sum1 <<(sum1 > 1000000 ? sum1 / 1000000 : sum1 > 1000 ? sum1 / 1000 : sum1); 
  cout<<(sum1 > 1000000 ? "MDA" : sum1 > 1000 ? "KDA" : "DA")<<endl;
      cout<<"the total water consumption of the country in the year "<<year<<" is :"<< sum2<<(sum2 > 1000000 ? sum2 / 1000000 :  sum2);
  cout<<(sum2 > 1000000 ? "dam^3" : "m^3")<<endl;
      cout<<"the total electricity consumption of the country in the year "<<year<<" is :"<<  sum3<<(sum3 > 1000000 ? sum3 / 1000 : sum3);
  cout<<(sum3 > 1000000 ? "Mwh" :  "kwh")<<endl;
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
  //print country summary info in a period
  void print_period_country_sales(int year1, int month1,int year2,int month2)
  {
    int result = 0;
    // iterating over all the wilayas
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          wilayas.iterate([i, j, &result](Wilaya *wilaya) -> bool
                    {
      result+=wilaya->get_wilaya_total_sales_per_month(i,j);
      return true; });
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          wilayas.iterate([i, j, &result](Wilaya *wilaya) -> bool
                    {
      result+=wilaya->get_wilaya_total_sales_per_month(i,j);
      return true; });
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          wilayas.iterate([i, j, &result](Wilaya *wilaya) -> bool
                    {
      result+=wilaya->get_wilaya_total_sales_per_month(i,j);
      return true; });
        }
      }
    }
    if (result != 0)
      cout << "the total sales of the country in the period from "<<month1<<"/"<<year1<<" to "<<month2<<"/"<<year2<<" is :" <<   result <<(result > 1000000 ? result / 1000000 : result > 1000 ? result / 1000 : result); 
  cout<<(result > 1000000 ? "MDA" : result > 1000 ? "KDA" : "DA")<<endl;
    else
      cout << "  the country has no sales in this period " << endl;
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
      cout << "the total sales of the country in the year " << year << " is :" <<  result <<(result > 1000000 ? result / 1000000 : result > 1000 ? result / 1000 : result); 
  cout<<(result > 1000000 ? "MDA" : result > 1000 ? "KDA" : "DA")<<endl;
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
// Listing all the sales of a farmer in a period
  void List_period_farmer_sales(int LandID, int year1, int month1,int year2,int month2)
  {
    Land *land = lands.getById(LandID);
    //iterating over the years from specific month and calling  print_monthly_farmer_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          List_monthly_farmer_sales(LandID,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          List_monthly_farmer_sales(LandID,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          List_monthly_farmer_sales(LandID,i,j);
        }
      }
    }
  }


  // Listing all the sales of a farmer in a land in a year
  void List_yearly_farmer_sales(int LandID, int year)
  {
    Land *land = lands.getById(LandID);
    //cheking if the land exists
    if (land != nullptr)
    {
      if (year == -1)
      {
        for (int i = start_year; i < 2024; i++)
          for (int j = 1; j <= 12; j++)
            land->print_yearly_farmer_sales(i);
      }
      else
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
  // Listing all the sales of a farmer in a area in a period
  void List_period_farmer_sales_in_area(int areaID, int year1, int month1,int year2,int month2)
  {
    Area *area = areas.getById(areaID);
    //iterating over the years from specific month and calling  print_monthly_farmer_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          List_monthly_farmer_sales_in_area(areaID,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          List_monthly_farmer_sales_in_area(areaID,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          List_monthly_farmer_sales_in_area(areaID,i,j);
        }
      }
    }
  }


  // Listing all the sales of a farmer in a area in a year
  void List_yearly_farmer_sales_in_area(int areaID, int year)
  {
    Area *area = areas.getById(areaID);
    //cheking if the area exists
    if (area != nullptr)
    {
      if (year == -1)
      {
        for (int i = start_year; i < 2024; i++)
          area->print_area_yearly_farmer_sales(i);
      }
      else area->print_area_yearly_farmer_sales(year);
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
  // Listing all the sales of a farmer in a city in a period
  void List_period_farmer_sales_in_city(int cityID, int year1, int month1,int year2,int month2)
  {
    City *city = cities.getById(cityID);
    //iterating over the years from specific month and calling  print_monthly_farmer_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          List_monthly_farmer_sales_in_city(cityID,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          List_monthly_farmer_sales_in_city(cityID,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          List_monthly_farmer_sales_in_city(cityID,i,j);
        }
      }
    }
  }



  // Listing all the sales of a farmer in a city in a year
  void List_yearly_farmer_sales_in_city(int cityID, int year)
  {
    City *city = cities.getById(cityID);
    //cheking if the city exists
    if (city != nullptr)
    {
      if (year == -1)
      {
        for (int i = start_year; i < 2024; i++)
          city->print_city_yearly_farmer_sales(i);
      }
      else
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
  // Listing all the sales of a farmer in a wilaya in a period
  void List_period_farmer_sales_in_wilaya(int wilayaID, int year1, int month1,int year2,int month2)
  {
    Wilaya *wilaya = wilayas.getById(wilayaID);
    //iterating over the years from specific month and calling  print_monthly_farmer_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          List_monthly_farmer_sales_in_wilaya(wilayaID,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          List_monthly_farmer_sales_in_wilaya(wilayaID,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          List_monthly_farmer_sales_in_wilaya(wilayaID,i,j);
        }
      }
    }
  }



  // Listing all the sales of a farmer in a wilaya in a year
  void List_yearly_farmer_sales_in_wilaya(int wilayaID, int year)
  {
    Wilaya *wilaya = wilayas.getById(wilayaID);
    //cheking if the wilaya exists
    if (wilaya != nullptr)
    {
      if (year == -1)
      {
        for (int i = start_year; i < 2024; i++)
          wilaya->print_wilaya_yearly_farmer_sales(i);
      }
      else
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
// Listing all the sales of all farmers in the country in a period
  void List_period_farmer_sales_in_country(int year1, int month1,int year2,int month2)
  {
    // iterating over all the wilayas
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          wilayas.iterate([i, j](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_monthly_farmer_sales(i,j);
      return true; });
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          wilayas.iterate([i, j](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_monthly_farmer_sales(i,j);
      return true; });
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          wilayas.iterate([i, j](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_monthly_farmer_sales(i,j);
      return true; });
        }
      }
    }
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
      bool isProcessed = false;
      if(is_integer) {
          while(!isProcessed) {
          input = 0;
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
              continue;
            }
            else if (input > max || input < min)
            {
              cout << dye::red("ERR: input is outside of range, please type again") << endl;
              continue;
            }
          } else {
            cout << dye::red("ERR: wrong input type. Please type again") << endl;
            continue;
          }
          isProcessed = true;

        }
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
  //listing the penalties of a farmer  in a period in a specific category
  void List_period_farmer_penalty(int landID, int year1, int month1,int year2,int month2, string category)
  {
    Land *land = lands.getById(landID);
    //iterating over the years from specific month and calling  print_monthly_farmer_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          List_monthly_farmer_penalty(landID,i,j,category);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          List_monthly_farmer_penalty(landID,i,j,category);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          List_monthly_farmer_penalty(landID,i,j,category);
        }
      }
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
 //listing the penalties of a farmer  in a period in a specific category
  void List_period_area_monthly_farmers_penalties(int areaID, int year1, int month1,int year2,int month2, string category)
  {
    Area *area = areas.getById(areaID);
    //iterating over the years from specific month and calling  print_monthly_farmer_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          List_area_monthly_farmers_penalties(areaID,i,j,category);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          List_area_monthly_farmers_penalties(areaID,i,j,category);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          List_area_monthly_farmers_penalties(areaID,i,j,category);
        }
      }
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
  //listing the penalties of a farmers in city  in a period in a specific category
  void List_period_city_monthly_farmers_penalties(int cityID, int year1, int month1,int year2,int month2, string category)
  {
    City *city = cities.getById(cityID);
    //iterating over the years from specific month and calling  print_monthly_farmer_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          List_city_monthly_farmers_penalties(cityID,i,j,category);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          List_city_monthly_farmers_penalties(cityID,i,j,category);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          List_city_monthly_farmers_penalties(cityID,i,j,category);
        }
      }
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
  //listing the penalties of a farmers in wilaya  in a period in a specific category
  void List_period_wilaya_monthly_farmers_penalties(int wilayaID, int year1, int month1,int year2,int month2, string category)
  {
    Wilaya *wilaya = wilayas.getById(wilayaID);
    //iterating over the years from specific month and calling  print_monthly_farmer_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          List_wilaya_monthly_farmers_penalties(wilayaID,i,j,category);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          List_wilaya_monthly_farmers_penalties(wilayaID,i,j,category);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          List_wilaya_monthly_farmers_penalties(wilayaID,i,j,category);
        }
      }
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
 //listing the penalties of a farmers in wilaya  in a period in a specific category
  void List_period_country_monthly_farmers_penalties(int year1, int month1,int year2,int month2, string category)
  {
    // iterating over all the wilayas
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          wilayas.iterate([i, j, category](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_monthly_penalty(i, j, category);
      return true; });
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          wilayas.iterate([i, j, category](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_monthly_penalty(i, j, category);
      return true; });
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          wilayas.iterate([i, j, category](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_monthly_penalty(i, j, category);
      return true; });
        }
      }
    }
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
 //functions to print the summarized reports in a period
  void print_period_land_summarized(int landID, int year1, int month1,int year2,int month2)
  {
    Land *land = lands.getById(landID);
    //iterating over the years from specific month and calling  print_monthly_farmer_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          print_monthly_land_summarized(landID,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          print_monthly_land_summarized(landID,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          print_monthly_land_summarized(landID,i,j);
        }
      }
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
  //functions to print the summarized reports in a period
  void print_period_area_summarized(int areaID, int year1, int month1,int year2,int month2)
  {
    Area *area = areas.getById(areaID);
    //iterating over the years from specific month and calling  print_monthly_farmer_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          print_monthly_area_summarized(areaID,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          print_monthly_area_summarized(areaID,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          print_monthly_area_summarized(areaID,i,j);
        }
      }
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

  //functions to print the summarized reports in a period
  void print_period_city_summarized(int cityID, int year1, int month1,int year2,int month2)
  {
    City *city = cities.getById(cityID);
    //iterating over the years from specific month and calling  print_monthly_farmer_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          print_monthly_city_summarized(cityID,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          print_monthly_city_summarized(cityID,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          print_monthly_city_summarized(cityID,i,j);
        }
      }
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

  //functions to print the summarized reports in a period

  void print_period_wilaya_summarized(int wilayaID, int year1, int month1,int year2,int month2)
  {
    Wilaya *wilaya = wilayas.getById(wilayaID);
    //iterating over the years from specific month and calling  print_monthly_farmer_sales
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          print_monthly_wilaya_summarized(wilayaID,i,j);
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          print_monthly_wilaya_summarized(wilayaID,i,j);
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          print_monthly_wilaya_summarized(wilayaID,i,j);
        }
      }
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

  //functions to print the summarized reports in a period
  void print_period_country_summarized(int year1, int month1,int year2,int month2)
  {
    // iterating over all the wilayas
    for(int i=year1;i<=year2;i++)
    {
      if(i==year1)
      {
        for(int j=month1;j<=12;j++)
        {
          wilayas.iterate([i, j](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_summarized_by_month(i,j);
      return true; });
        }
      }
      else if(i==year2)
      {
        for(int j=1;j<=month2;j++)
        {
          wilayas.iterate([i, j](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_summarized_by_month(i,j);
      return true; });
        }
      }
      else
      {
        for(int j=1;j<=12;j++)
        {
          wilayas.iterate([i, j](Wilaya *wilaya) -> bool
                    {
      wilaya->print_wilaya_summarized_by_month(i,j);
      return true; });
        }
      }
    }
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
      y.push_back(land->get_land_total_sales_per_month(year, i + 1));
    }

    ScatterPlotSeries* series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    string narrowString = "Sales per month from " + land->getFarmer()->getName() + "'s Land over the year of " + std::to_string(year);
    std::wstring wideString(narrowString.begin(), narrowString.end());
    settings->title = toVector(wideString.c_str());
    settings->xLabel = toVector(L"Months");
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
      cout << dye::green("Plot Generated! opening...") << endl;
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
    string narrowString = "Sales per year from " + land->getFarmer()->getName() + "'s Land since it was founded";
    std::wstring wideString(narrowString.begin(), narrowString.end());
    settings->title = toVector(wideString.c_str());
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
      cout << dye::green("Plot Generated! opening...") << endl;
      system(file_name.str().c_str());
    }
  }
  void generatePlot(Area *area, int year)
  {
    vector<double> x, y;
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    for (int i = 0; i < 12; i++)
    {
      x.push_back(i + 1);
      y.push_back(area->get_area_total_sales_per_month(year, i + 1));
    }

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    string narrowString = "Sales per month from Areaa of " + area->getName() + " over the year of " + std::to_string(year);
    std::wstring wideString(narrowString.begin(), narrowString.end());
    settings->title = toVector(wideString.c_str());
    settings->xLabel = toVector(L"Months");
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
    string narrowString = "Sales per year from Area of" + area->getName() + " since it was founded";
    std::wstring wideString(narrowString.begin(), narrowString.end());
    settings->title = toVector(wideString.c_str());
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
    for (int i = 0; i < 12; i++)
    {
      x.push_back(i + 1);
      y.push_back(city->get_city_total_sales_per_month(year, i + 1));
    }

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    string narrowString = "Sales per month from the City of " + city->getName() + " over the year of " + std::to_string(year);
    std::wstring wideString(narrowString.begin(), narrowString.end());
    settings->title = toVector(wideString.c_str());
    settings->xLabel = toVector(L"Months");
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
    for (int i = start_year; i < end_year; i++)
    {
      x.push_back(i);
      y.push_back(city->get_city_total_sales_per_year(i + 1));
    }

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    string narrowString = "Sales per year from the City of " + city->getName() + " since it was founded";
    std::wstring wideString(narrowString.begin(), narrowString.end());
    settings->title = toVector(wideString.c_str());
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
    for (int i = 1; i <= 12; i++)
    {
      x.push_back(i);
      y.push_back(wilaya->get_wilaya_total_sales_per_month(year, i + 1));
    }

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    string narrowString = "Sales per month from " + wilaya->getName() + " over the year of " + std::to_string(year);
    std::wstring wideString(narrowString.begin(), narrowString.end());
    settings->title = toVector(wideString.c_str());
    settings->xLabel = toVector(L"Months");
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
    for (int i = start_year; i < end_year; i++)
    {
      x.push_back(i);
      y.push_back(wilaya->get_wilaya_total_sales_per_year(i + 1));
    }

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->lineThickness = 2;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->height = 1024;
    settings->width = 1024;
    stringstream str;
    string narrowString = "Sales per year from " + wilaya->getName() + " since it was founded";
    std::wstring wideString(narrowString.begin(), narrowString.end());
    settings->title = toVector(wideString.c_str());
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