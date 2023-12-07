#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include"land.hpp"
#include "Area.hpp"

Area::Area() {
    name = "";
    ID = 0;
    lands = std::vector<Land>();
}
Area::~Area()
{
     lands.clear();    
}

Area::Area(const std::string& name, const int& id, const std::vector<Land>& lands) : name(name), ID(id), lands(lands) {}

std::string Area::getAreaName() const {
    return name;
}

std::vector<Land> Area::getLands() const {
    return lands;
}

int Area::getAreaID() const {
    return ID;
}

void Area::setAreaID(const int& id) {
    this->ID = id;
}

void Area::setAreaName(const std::string& name) {
    this->name = name;
}

void Area::setLands(const std::vector<Land>& lands) {
    this->lands = lands;
}

void Area::addLand(const Land& land) {
    lands.push_back(land);
}

void Area::removeLand(const Land& land) {
    lands.erase(std::remove(lands.begin(), lands.end(), land), lands.end());
}

void Area::removeLand(const std::string& landName) {
    lands.erase(std::remove_if(lands.begin(), lands.end(), [&landName](const Land& land) {
        return land.getName() == landName;
    }), lands.end());
}

bool Area::operator<(const Area& rhs) const {
    return ID < rhs.ID;
}