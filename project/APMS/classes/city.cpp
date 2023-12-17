#include<algorithm>
#include "city.hpp"
using namespace std;


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

int City::getCityId() const {
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
    os << "City ID: " << cit.getCityId() << endl;
    os << "City: " << cit.getName() << endl;
    for(Area* area: cit.getArea()) {
        os << *area;
    }
    cout << setfill('-') << setw(40) << "" << endl;
    return os;
}