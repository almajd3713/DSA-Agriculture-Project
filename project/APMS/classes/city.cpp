#include "city.hpp"


City::City() {
    name = "";
    id = 0;
    areas = std::vector<Area*>();

}

City::City(const std::string& name, const int& id, const std::vector<Area*>& areas) : name(name), id(id), areas(areas) {}

City::City(const City& rhs)
: name{rhs.name}, id{rhs.id}, areas{rhs.areas} {}

City::City(City&& rhs)
: name{move(rhs.name)}, id{rhs.id}, areas{move(rhs.areas)} {}

City::~City() {
    areas.clear();
}

std::string City::getName() const {
    return name;
}

int City::getId() const
{
    return id;
}

std::vector<Area*> City::getArea() const {
    return areas;
}

void City::setName(const std::string &name) {
    this->name = name;
}

void City::setArea(const std::vector<Area*> &areas) {
    this->areas = areas;
}

void City::setCityId(const int &id) {
    this->id = id;
}

void City::addArea(Area* area) {
    areas.push_back(area);
}

void City::removeArea(Area* area) {
    areas.erase(remove(areas.begin(), areas.end(), area), areas.end());
}

// void City::removeArea(const std::string& areaName) {
//     areas.erase(remove_if(areas.begin(), areas.end(), [&areaName](const Area& area) {
//         return area.getName() == areaName;
//     }), areas.end());
// }

bool City::operator<(const City& rhs) const {
    return id < rhs.id;
}

City& City::operator=(const City& rhs) {
    id = rhs.id;
    name = rhs.name;
    areas = rhs.areas;
    return *this;
}

bool City::operator==(const City& rhs) {
    return id == rhs.id;
}

ostream &operator<<(ostream &os, const City& cit)
{
    // os << "Land ID: " << land.id << endl;
    // os << "Farmer: " << land.farmer->getName() << endl;
    // os << "Annual Reports: " << endl;
    // for (auto year : land.reports)
    // {
    //     os << *year << endl;
    // }
    os << dye::green(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    os << "City ID: " << cit.getId() << endl;
    os << "City: " << cit.getName() << endl;
    for(Area* area: cit.getArea()) {
        os << *area;
    }
    os << dye::green(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    return os;
}
//print resumed 
void City::print_city_by_month(const int year,const int& month)
{
  cout << dye::green(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout<< "Year :"<<year<<endl;
    for(auto area : areas)
    {
        area->Print_Area_By_month(year,month);
    }
    cout<<" total sales :"<<get_city_total_sales_per_month(year,month)<<" DA "<<endl;
    //water and electricity consumption
    cout<<" total water consumption :"<<get_city_monthly_water_consumption(year,month)<<" m^3 "<<endl;
    cout<<" total electricity consumption :"<<get_city_monthly_electricity_consumption(year,month)<<" KWh "<<endl;
    cout << dye::green(stringRepeat("=", getConsoleWidth() / 2)) << endl;
}
void City::print_city_by_year(const int& year,int choice)
{
  cout << dye::green(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout<< "Year :"<<year<<endl;
    for(auto area : areas)
    {
        area->Print_Area_By_Year(year,choice);
    }
  cout << dye::green(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout<<" total sales :"<<get_city_total_sales_per_year(year)<<" DA "<<endl;
    //water and electricity consumption
    cout<<" total water consumption :"<<get_city_yearly_water_consumption(year)<<" m^3 "<<endl;
    cout<<" total electricity consumption :"<<get_city_yearly_electricity_consumption(year)<<" KWh "<<endl;
}

double City::get_city_total_sales_per_year(int year)
{
    double total=0;
    for(auto area : areas)
    {
        total+=area->get_area_total_sales_per_year(year);
    }
    return total;
}
double City::get_city_total_sales_per_month(int year,int month)
{
    double total=0;
    for(auto area : areas)
    {
        total+=area->get_area_total_sales_per_month(year,month);
    }
    return total;
}

 void City::print_city_monthly_farmer_sales(int year,int month)
 {
  cout << dye::green(stringRepeat("=", getConsoleWidth() / 2)) << endl;

    cout<<"City: " << name << endl;
    cout<<"Year :"<<year<<" Month :"<<month<<endl;
    for(auto area : areas)
    {
        area->print_area_monthly_farmer_sales(year,month);
    }
  cout << dye::green(stringRepeat("=", getConsoleWidth() / 2)) << endl;
 }
    
void City::print_city_yearly_farmer_sales(int year)
{ 
  cout << dye::green(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout<<"City: " << name << endl;
    cout<<"Year: "<<year<<endl;
    for(auto area : areas)
    {
        area->print_area_yearly_farmer_sales(year);
    }
  cout << dye::green(stringRepeat("=", getConsoleWidth() / 2)) << endl;
}

void to_json(json& j, const City& cit) {
    j = json{
        {"id", cit.getId()},
        {"name", cit.getName()},
        {"lands", "Bazingen"}};
    for(Area* area: cit.getArea()) {
        j["areas"].push_back(*area);
    } 
}

//query 3
void City::print_city_monthly_penalty(int year,int month,string category_name)
{
    cout<<"City: " << name << endl;
    cout<<"Year :"<<year<<" Month :"<<month<<endl;
    for(auto area : areas)
    {
        area->print_Area_monthly_penalty(year,month,category_name);
        cout<<"============================================"<<endl;
    }
}
//query 3
void City::print_city_yearly_penalty(int year,string category_name)
{
    cout<<"City: " << name << endl;
    cout<<"Year :"<<year<<endl;
    for(auto area : areas)
    {
        area->print_Area_yearly_penalty(year,category_name);
        cout<<"============================================"<<endl;
    }
}
//functions to get the water and electricity consumption of the city
double City::get_city_yearly_water_consumption(int year)
{
    double total=0;
    for(auto area : areas)
    {
        total+=area->get_area_yearly_water_consumption(year);
    }
    return total;
}
double City::get_city_yearly_electricity_consumption(int year)
{
    double total=0;
    for(auto area : areas)
    {
        total+=area->get_area_yearly_electricity_consumption(year);
    }
    return total;
}
//functions to get the water and electricity consumption of the city in a month
double City::get_city_monthly_water_consumption(int year,int month)
{
    double total=0;
    for(auto area : areas)
    {
        total+=area->get_area_monthly_water_consumption(year,month);
    }
    return total;
}
double City::get_city_monthly_electricity_consumption(int year,int month)
{
    double total=0;
    for(auto area : areas)
    {
        total+=area->get_area_monthly_electricity_consumption(year,month);
    }
    return total;
}
//functions to print the the summarized report of the city
void City::print_city_summarized_by_year(int year)
{
    cout<<"City: " << name << endl;
    cout<<"Year :"<<year<<endl;
    for(auto area : areas)
    {
        area->print_area_summerized_by_year(year);
        cout<<"============================================"<<endl;
    }
    double sales=get_city_total_sales_per_year(year);
    double water=get_city_yearly_water_consumption(year);
    double electricity=get_city_yearly_electricity_consumption(year);
    cout<<"the city total sales is : "<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
  cout<<"the city total water consumption is : "<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
  cout<<"the city total electricity consumption is : "<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
}
void City::print_city_summarized_by_month(int year,int month)
{
    cout<<"City: " << name << endl;
    cout<<"Year :"<<year<<" Month :"<<month<<endl;
    for(auto area : areas)
    {
        area->print_area_summerized_by_month(year,month);
        cout<<"============================================"<<endl;
    }
    double sales=get_city_total_sales_per_month(year,month);
    double water=get_city_monthly_water_consumption(year,month);
    double electricity=get_city_monthly_electricity_consumption(year,month);
    cout<<"the city total sales is : "<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
  cout<<"the city total water consumption is : "<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
  cout<<"the city total electricity consumption is : "<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
}

double City::get_monthly_city_penalty(int year, int month, const string &category_name)
{
    double sum = 0;
    for (Area *land : getArea())
        sum += land->get_monthly_area_penalty(year, month, category_name);
    return sum;
}
double City::get_yearly_city_penalty(int year, const string &category_name)
{
    double sum = 0;
    for (Area *land : getArea())
        sum += land->get_yearly_area_penalty(year, category_name);
    return sum;
}