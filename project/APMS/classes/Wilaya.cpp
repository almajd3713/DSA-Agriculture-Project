#include "Wilaya.hpp"
#include <algorithm>
#include "City.hpp"

using namespace std;


// Wilaya::Wilaya() {
//     name = "";
//     id = 0;
//     cities = vector<City>();
// }

// Wilaya::Wilaya(const std::string& name, const int& id, const std::vector<City>& cities) : name(name), id(id), cities(cities) {}

// Wilaya::Wilaya(const Wilaya& rhs)
// : name{rhs.name}, id{rhs.id}, cities{rhs.cities} {}

// Wilaya::Wilaya(Wilaya&& rhs)
// : name{move(rhs.name)}, id{rhs.id}, cities{move(rhs.cities)} {}

// Wilaya::~Wilaya() 
// {
//     cities.clear();
// }
Wilaya::Wilaya() {
  id = 0;
  name = "";
  cities = vector<City>();
}

Wilaya::Wilaya(int id, const string& name, const vector<City>& cities)
  : id{id}, name{name}, cities{cities} {}

Wilaya::Wilaya(const Wilaya& rhs)
  : id{rhs.id}, name{rhs.name}, cities{rhs.cities} {}

Wilaya::Wilaya(Wilaya&& rhs)
  : id{move(rhs.id)}, name{move(rhs.name)}, cities{move(rhs.cities)} {}

Wilaya::~Wilaya() {
    cities.clear();
}

int Wilaya::getWilayaId() const {
    return id;
}

std::string Wilaya::getName() const {
    return name;
}

std::vector<City> Wilaya::getCity() const {
    return cities;
}

void Wilaya::setName(const std::string& name) {
    this->name = name;
}

void Wilaya::setCity(const std::vector<City>& cities) {
    this->cities = cities;
}

void Wilaya::setId(const int& id) {
    this->id = id;
}

void Wilaya::addCity(const City& city) {
    cities.push_back(city);
}

void Wilaya::removeCity(const City& city) {
    cities.erase(remove(cities.begin(), cities.end(), city), cities.end());
}

void Wilaya::removeCity(const string& cityName) {
    cities.erase(remove_if(cities.begin(), cities.end(), [&cityName](const City& city) {
        return city.getName() == cityName;
    }), cities.end());
}

bool Wilaya::operator<(const Wilaya& rhs) const {
    return id < rhs.id;
}