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
void Area::Print_Area_By_Year(int year)
{
  cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout<< "Year :"<<year<<endl;
    for(auto land : lands)
    {
        cout<<*land->getFarmer()<<endl;
        land->printAnnualReport(year);
     }
  cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
}
int Area::get_area_total_sales_per_year(int year){
    int total_sales = 0;
    for(auto land : lands)
    {
        total_sales += land->get_land_total_sales_per_year(year);
    }
    return total_sales;
    
}
 int Area::get_area_total_sales_per_month(int year,int month)
 {
        int total_sales = 0;
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
        cout<<*land->getFarmer()<<endl;
        land->printMonthlyReport(year,month);
     }
    cout << dye::purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
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
