#include<algorithm>
#include "City.hpp"
using namespace std;


City::City() {
    name = "";
    id = 0;
    areas = std::vector<Area>();

}

City::City(const std::string& name, const int& id, const std::vector<Area>& areas) : name(name), id(id), areas(areas) {}

City::~City() {
    areas.clear();
}

std::string City::getName() const {
    return name;
}

int City::getCityId() const {
    return id;
}

std::vector<Area> City::getArea() const {
    return areas;
}

void City::setName(const std::string &name) {
    this->name = name;
}

void City::setArea(const std::vector<Area> &areas) {
    this->areas = areas;
}

void City::setCityId(const int &id) {
    this->id = id;
}

void City::addArea(const Area& area) {
    areas.push_back(area);
}

void City::removeArea(const Area& area) {
    areas.erase(remove(areas.begin(), areas.end(), area), areas.end());
}

void City::removeArea(const std::string& areaName) {
    areas.erase(remove_if(areas.begin(), areas.end(), [&areaName](const Area& area) {
        return area.getName() == areaName;
    }), areas.end());
}

bool City::operator<(const City& rhs) const {
    return id < rhs.id;
}
