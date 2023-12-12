
#include "production.hpp"

Production::Production() {
  waterConsumption = 0;
  electricityConsumption = 0;
  categories = unordered_map<string, ProductCategory>();
}

Production::Production(int wc, int ec, const unordered_map<string, ProductCategory>&initcategories)
: waterConsumption{wc}, electricityConsumption{ec}, categories{initcategories} {}

Production::Production(const Production& rhs)
: waterConsumption{rhs.waterConsumption}, electricityConsumption{rhs.electricityConsumption}, categories{rhs.categories} {}

Production::Production(Production&& rhs)
: waterConsumption{rhs.waterConsumption}, electricityConsumption{rhs.electricityConsumption}, categories{move(rhs.categories)} {}

Production::~Production() {
  categories.clear();
}

int Production::getWaterConsumption() const {
  return waterConsumption;
}
void Production::setWaterConsumption(int new_waterConsumption) {
  waterConsumption = new_waterConsumption;
}

int Production::getElectricityConsumption() const {
  return electricityConsumption;
}
void Production::setElectricityConsumption(int new_electricityConsumption) {
  electricityConsumption = new_electricityConsumption;
}

unordered_map<string, ProductCategory> Production::getcategories() const {
  return categories;
}
void Production::setcategories(unordered_map<string, ProductCategory> new_categories) {
  categories = new_categories;
}

void Production::addProduct(const ProductCategory& ProductCategory) {
  categories[ProductCategory.getName()] = ProductCategory;
}

void Production::addProduct(const string& name, double bp, double pr, PesticideSeverity ps) {
  categories[name] = ProductCategory(name, bp, pr, ps);
}