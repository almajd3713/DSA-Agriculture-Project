
#include "land_data.hpp"

LandData::LandData() {
  waterConsumption = 0;
  electricityConsumption = 0;
  categories = vector<category*>();
}

LandData::LandData(int wc, int ec, const vector<category*>&initcategory)
: waterConsumption{wc}, electricityConsumption{ec}, categories{initcategory} {}

LandData::LandData(const LandData& rhs)
: waterConsumption{rhs.waterConsumption}, electricityConsumption{rhs.electricityConsumption}, categories{rhs.categories} {}

LandData::LandData(LandData&& rhs)
: waterConsumption{rhs.waterConsumption}, electricityConsumption{rhs.electricityConsumption}, categories{move(rhs.categories)} {}

LandData::~LandData() {
  categories.clear();
}

int LandData::getWaterConsumption() const {
  return waterConsumption;
}
void LandData::setWaterConsumption(int new_waterConsumption) {
  waterConsumption = new_waterConsumption;
}

int LandData::getElectricityConsumption() const {
  return electricityConsumption;
}
void LandData::setElectricityConsumption(int new_electricityConsumption) {
  electricityConsumption = new_electricityConsumption;
}

vector<category*> LandData::getcategories() const {
  return categories;
}
void LandData::setcategories(vector<category*> new_category) {
  categories = new_category;
}
ostream& operator<<(ostream& os, const LandData& land) {
  os << "Water Consumption: " << land.waterConsumption << endl;
  os << "Electricity Consumption: " << land.electricityConsumption << endl;
  os << "Categories: " << endl;
  for (auto category : land.categories) {
    os << *category << endl;
  }
  return os;
}