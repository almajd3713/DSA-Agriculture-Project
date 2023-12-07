#include "Wilaya.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "City.hpp"

using namespace std;


Wilaya::Wilaya() {
    name = "";
    ID = 0;
    Cities = vector<City>();
}

Wilaya::Wilaya(const std::string& name, const int& id, const std::vector<City>& cities) : name(name), ID(id), Cities(cities) {}

Wilaya::~Wilaya() 
{
    Cities.clear();
}

int Wilaya::getWilayaID() const {
    return ID;
}

std::string Wilaya::getName() const {
    return name;
}

std::vector<City> Wilaya::getCity() const {
    return Cities;
}

void Wilaya::setName(const std::string& name) {
    this->name = name;
}

void Wilaya::setCity(const std::vector<City>& cities) {
    this->Cities = cities;
}

void Wilaya::setWilayaID(const int& id) {
    this->ID = id;
}

void Wilaya::addCity(const City& city) {
    Cities.push_back(city);
}

void Wilaya::removeCity(const City& city) {
    Cities.erase(std::remove(Cities.begin(), Cities.end(), city), Cities.end());
}

void Wilaya::removeCity(const std::string& cityName) {
    Cities.erase(std::remove_if(Cities.begin(), Cities.end(), [&cityName](const City& city) {
        return city.getName() == cityName;
    }), Cities.end());
}

bool Wilaya::operator<(const Wilaya& rhs) const {
    return ID < rhs.ID;
}