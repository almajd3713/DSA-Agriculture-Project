#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"Area.hpp"
#include "City.hpp"
using namespace std;


City::City() {
    name = "";
    ID = 0;
    areas = std::vector<Area>();

}

City::City(const std::string& name, const int& id, const std::vector<Area>& areas) : name(name), ID(id), areas(areas) {}

City::~City() {
    areas.clear();
}

std::string City::getName() const {
    return name;
}

int City::getCityID() const {
    return ID;
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

void City::setCityID(const int &id) {
    this->ID = id;
}

void City::addArea(const Area& area) {
    areas.push_back(area);
}

void City::removeArea(const Area& area) {
    areas.erase(std::remove(areas.begin(), areas.end(), area), areas.end());
}

void City::removeArea(const std::string& areaName) {
    areas.erase(std::remove_if(areas.begin(), areas.end(), [&areaName](const Area& area) {
        return area.getAreaName() == areaName;
    }), areas.end());
}

bool City::operator<(const City& rhs) const {
    return ID < rhs.ID;
}
