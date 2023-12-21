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
    cout<< "Year :"<<year<<endl;
    for(auto land : lands)
    {  
        cout<<" farmer : " <<*land->getFarmer()<<endl;
        land->printAnnualReport(year,choice);//prints id land and the total sales of the year
       
     }
      cout<<" area total sales :"<<get_area_total_sales_per_year(year)<<" DA "<<endl;
      //water and electricity consumption
        cout<<" area total water consumption :"<<get_area_yearly_water_consumption(year)<<" m^3 "<<endl;
        cout<<" area total electricity consumption :"<<get_area_yearly_electricity_consumption(year)<<" KWh "<<endl;
      
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
    cout<< "Year :"<<year<<" Month :"<<month<<endl;
    for(auto land : lands)
    {
        cout<<" farmer : " <<*land->getFarmer()<<endl;
        cout<<" id : "<<land->getId()<<endl;
        land->printMonthlyReport(year,month);
     }
        cout<<" area total sales :"<<get_area_total_sales_per_month(year,month)<<" DA "<<endl;
        //water and electricity consumption
            cout<<" area total water consumption :"<<get_area_monthly_water_consumption(year,month)<<" m^3 "<<endl;
            cout<<" area total electricity consumption :"<<get_area_monthly_electricity_consumption(year,month)<<" KWh "<<endl;
}
// all the years in the area
ostream& operator<<(ostream& os, const Area& area) {
    os << "Area ID: " << area.id << endl;
    os << "Area Name: " << area.name << endl;
    os << "Lands: " << endl;
    for (auto land : area.lands) {
        os << *land << endl;
    }
    return os;
}

  void Area::print_area_monthly_farmer_sales(int year,int month)
  {       cout<<"Area: " << name << endl;
        cout<<"Year :"<<year<<" Month :"<<month<<endl;
        for(auto land : lands)
        {
            land->print_monthly_farmer_sales(year,month);
            cout<<"============================================"<<endl;
        }
  }
  void Area:: print_area_yearly_farmer_sales(int year)
  {     cout<<"Area: " << name << endl;
        cout<<"Year :"<<year<<endl;
        for(auto land : lands)
        {
            land->print_yearly_farmer_sales(year);
            cout<<"============================================"<<endl;
        }}

// functions to print the monthly  penalty of the area

 void Area::print_Area_monthly_penalty(int year,int month,string category_name)
 {
   //iterating over the years and then over the months
    cout<<"Area: " << name << endl;
    cout<<"Year :"<<year<<" Month :"<<month<<endl;
    for(auto land : lands)
    {
        land->print_Land_monthly_penalty(year,month,category_name);
        cout<<"============================================"<<endl;
    }



 }
  void Area::print_Area_yearly_penalty(int year,string category_name)
  {
    //iterating over the years and then over the months
    cout<<"Area: " << name << endl;
    cout<<"Year :"<<year<<endl;
    for(auto land : lands)
    {
        land->print_Land_yearly_penalty(year,category_name);
        cout<<"============================================"<<endl;
    }

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
    cout<<"Area: " << name << endl;
    cout<<"Year :"<<year<<" Month :"<<month<<endl;
    for(auto land : lands)
    {
        land->print_monthly_summarized_report(year,month);
        cout<<"============================================"<<endl;
    }
double sales = get_area_total_sales_per_month(year,month);
double water = get_area_monthly_water_consumption(year,month);
double electricity = get_area_monthly_electricity_consumption(year,month);
 cout<<"the area total sales is : "<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
  cout<<"the area total water consumption is : "<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
  cout<<"the area total electricity consumption is : "<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
}
void Area::print_area_summerized_by_year(int year)
{
    cout<<"Area: " << name << endl;
    cout<<"Year :"<<year<<endl;
    for(auto land : lands)
    {
        land->print_yearly_summarized_report(year);
        cout<<"============================================"<<endl;
    }
double sales = get_area_total_sales_per_year(year);
double water = get_area_yearly_water_consumption(year);
double electricity = get_area_yearly_electricity_consumption(year);
 cout<<"the area total sales is : "<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
  cout<<"the area total water consumption is : "<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
  cout<<"the area total electricity consumption is : "<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
}
