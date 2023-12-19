#include<algorithm>
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
    cout << setfill('-') << setw(40) << "" << endl;
    os << "City ID: " << cit.getId() << endl;
    os << "City: " << cit.getName() << endl;
    for(Area* area: cit.getArea()) {
        os << *area;
    }
    cout << setfill('-') << setw(40) << "" << endl;
    return os;
}
//print resumed 
void City::print_city_by_month(const int year,const int& month)
{
    cout<< "Year :"<<year<<endl;
    cout<<"----------------------------------------"<<endl;
    for(auto area : areas)
    {
        area->Print_Area_By_month(year,month);
    }
}
void City::print_city_by_year(const int& year)
{
    cout<< "Year :"<<year<<endl;
    cout<<"----------------------------------------"<<endl;
    for(auto area : areas)
    {
        area->Print_Area_By_Year(year);
    }
}
int City::get_city_total_sales_per_year(int year)
{
    int total=0;
    for(auto area : areas)
    {
        total+=area->get_area_total_sales_per_year(year);
    }
    return total;
}
int City::get_city_total_sales_per_month(int year,int month)
{
    int total=0;
    for(auto area : areas)
    {
        total+=area->get_area_total_sales_per_month(year,month);
    }
    return total;
}

 void City::print_city_monthly_farmer_sales(int year,int month)
 {
        cout<<"City: " << name << endl;
        cout<<"Year :"<<year<<" Month :"<<month<<endl;
        for(auto area : areas)
        {
            area->print_area_monthly_farmer_sales(year,month);
            cout<<"============================================"<<endl;
        }
 }
    
void City::print_city_yearly_farmer_sales(int year)
{
        cout<<"City: " << name << endl;
        cout<<"Year :"<<year<<endl;
        for(auto area : areas)
        {
            area->print_area_yearly_farmer_sales(year);
            cout<<"============================================"<<endl;
        }
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
