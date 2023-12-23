#include<algorithm>
#include "area.hpp"
using std::move;

Area::Area() {
    name = "";
    id = 0;
    lands = std::vector<Land*>();
}
Area::~Area() {
     lands.clear();    
}

Area::Area(const std::string& name, const int& id, const std::vector<Land*>& lands) : name{name}, id{id}, lands{lands} {}

Area::Area(const Area& rhs)
    : name{rhs.name}, id{rhs.id}, lands{rhs.lands} {}

Area::Area(Area&& rhs)
    : name{move(rhs.name)}, id{rhs.id}, lands{move(rhs.lands)} {}



string Area::getName() const {
    return name;
}

std::vector<Land*> Area::getLands() const {
    return lands;
}

int Area::getId() const {
    return id;
}

void Area::setId(const int& id) {
    this->id = id;
}

void Area::setName(const string& name) {
    this->name = name;
}

void Area::setLands(const std::vector<Land*>& lands) {
    this->lands = lands;
}

void Area::addLand(Land* land) {
    lands.push_back(land);
}

void Area::removeLand(Land* land) {
    lands.erase(std::remove(lands.begin(), lands.end(), land), lands.end());
}

// void Area::removeLand(/*const std::string& landName*/ const int& landId) {
//     lands.erase(std::remove_if(lands.begin(), lands.end(), [&landId](const Land& land) {
//         return land.getId() == landId;
//     }), lands.end());
// }

bool Area::operator<(const Area& rhs) const {
    return id < rhs.id;
}

Area& Area::operator=(const Area& rhs) {
    name = rhs.name;
    id = rhs.id;
    lands = rhs.lands;
    return *this;
}

bool Area::operator==(const Area& rhs) {
    return id == rhs.id;
}
//print function
void Area::Print_Area_By_Year(int year,int choice)
{
  cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout<< "Year :"<<year<<endl;
    for(auto land : lands)
    {  
        cout<<" farmer : " <<*land->getFarmer()<<endl;
        land->printAnnualReport(year,choice);//prints id land and the total sales of the year
       
     }
     double sales=0 ;
     sales = get_area_total_sales_per_year(year);
     double water=0;
     water = get_area_yearly_water_consumption(year);
     double electricity=0;
      electricity = get_area_yearly_electricity_consumption(year);
      cout<<" area total sales :"<<sales<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
      //water and electricity consumption
        cout<<" area total water consumption :"<<water<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
        cout<<" area total electricity consumption :"<<electricity<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
      
}
double Area::get_area_total_sales_per_year(int year){
double total_sales = 0;
    for(auto land : lands)
    {
        total_sales += land->get_land_total_sales_per_year(year);
    }
    return total_sales;
    
}
 double Area::get_area_total_sales_per_month(int year,int month)
 {
        double total_sales = 0;
        for(auto land : lands)
        {
            total_sales += land->get_land_total_sales_per_month(year,month);
        }
        return total_sales;

 }
void Area::Print_Area_By_month(int year,int month){
    cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout<< "Year :"<<year<<" Month :"<<month<<endl;
    for(auto land : lands)
    {
        cout<<" farmer : " <<*land->getFarmer()<<endl;
        cout<<" id : "<<land->getId()<<endl;
        land->printMonthlyReport(year,month);
     }
         double sales=0;
         sales = get_area_total_sales_per_month(year,month);
         double water=0;
         water= get_area_monthly_water_consumption(year,month);
         double electricity =0;
         electricity=get_area_monthly_electricity_consumption(year,month);
      cout<<" area total sales :"<<sales<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
      //water and electricity consumption
        cout<<" area total water consumption :"<<water<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
        cout<<" area total electricity consumption :"<<electricity<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
}
// all the years in the area
ostream& operator<<(ostream& os, const Area& area) {
  os << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    os << "Area ID: " << area.id << endl;
    os << "Area Name: " << area.name << endl;
    os << "Lands: " << endl;
    for (auto land : area.lands) {
        os << *land << endl;
    }
  os << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    return os;
}

void Area::print_area_monthly_farmer_sales(int year,int month)
{      
  cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;   
     cout<<"Area: " << name << endl;
    cout<<"Year :"<<year<<" Month :"<<month<<endl;
    for(auto land : lands)
    {
        land->print_monthly_farmer_sales(year,month);

    }
  cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
}
void Area:: print_area_yearly_farmer_sales(int year)
{
  cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout<<"Area: " << name << endl;
    cout<<"Year :"<<year<<endl;
    for(auto land : lands)
    {
        land->print_yearly_farmer_sales(year);
    }
  cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
}

// ostream& operator<<(ostream& os, const Area& area) {
//     cout << setfill('.') << setw(40) << "" << endl;
//     os << "Area ID: " << area.getId() << endl;
//     os << "Area: " << area.getName() << endl;
//     cout << setfill('.') << setw(40) << "" << endl;
//     return os;
// }

void to_json(json& j, const Area& area) {
  j = json{
    {"name", area.getName()},
    {"id", area.getId()},
  };
  for(Land* land: area.getLands()) {
    j["lands"].push_back(*land);
  }
}
double Area::get_monthly_area_penalty(int year, int month, const string& category_name) {
    double sum = 0;
    for(Land* land: getLands())
        sum += land->get_monthly_land_penalty(year, month, category_name);
    return sum;
}
double Area::get_yearly_area_penalty(int year, const string& category_name) {
    double sum = 0;
    for(Land* land: getLands())
        sum += land->get_yearly_land_penalty(year, category_name);
    return sum;
}
// functions to print the monthly  penalty of the area

 void Area::print_Area_monthly_penalty(int year,int month,string category_name)
 {
     cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
     // iterating over the years and then over the months
     cout << "Area: " << name << endl;
     cout << "Year :" << year << " Month :" << month << endl;
     for (auto land : lands)
     {
         land->print_Land_monthly_penalty(year, month, category_name);
    
    }
    cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
 }
  void Area::print_Area_yearly_penalty(int year,string category_name)
  {
      cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
      // iterating over the years and then over the months
      cout << "Area: " << name << endl;
      cout << "Year :" << year << endl;
      for (auto land : lands)
      {
          land->print_Land_yearly_penalty(year, category_name);
    
    }
    cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
  }
//functions to get the water and electricity consumption of the area
double Area::get_area_yearly_water_consumption(int year)
{
    double total=0;
    for(auto land : lands)
    {
        total+=land->get_yearly_water_consumption(year);
    }
    return total;
}
double Area::get_area_yearly_electricity_consumption(int year)
{
    double total=0;
    for(auto land : lands)
    {
        total+=land->get_yearly_electricity_consumption(year);
    }
    return total;
}
//functions to get the water and electricity consumption of the area in a month
double Area::get_area_monthly_water_consumption(int year,int month)
{
    double total=0;
    for(auto land : lands)
    {
        total+=land->get_monthly_water_consumption(year,month);
    }
    return total;
}
double Area::get_area_monthly_electricity_consumption(int year,int month)
{
    double total=0;
    for(auto land : lands)
    {
        total+=land->get_monthly_electricity_consumption(year,month);
    }
    return total;
}

//functions to print the the summarized report of the area
void Area::print_area_summerized_by_month(int year,int month)
{
    cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout<<"Area: " << name << endl;
    cout<<"Year :"<<year<<" Month :"<<month<<endl;

double sales = get_area_total_sales_per_month(year,month);
double water = get_area_monthly_water_consumption(year,month);
double electricity = get_area_monthly_electricity_consumption(year,month);
 cout<<"the area total sales is : "<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
  cout<<"the area total water consumption is : "<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
  cout<<"the area total electricity consumption is : "<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
  cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
  for (auto land : lands)
  {
      land->print_monthly_summarized_report(year, month);
  }
}
void Area::print_area_summerized_by_year(int year)
{
    cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout<<"Area: " << name << endl;
    cout<<"Year :"<<year<<endl;

double sales = get_area_total_sales_per_year(year);
double water = get_area_yearly_water_consumption(year);
double electricity = get_area_yearly_electricity_consumption(year);
 cout<<"the area total sales is : "<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
  cout<<"the area total water consumption is : "<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
  cout<<"the area total electricity consumption is : "<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
  cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
  for (auto land : lands)
  {
      land->print_yearly_summarized_report(year);
  }
}
