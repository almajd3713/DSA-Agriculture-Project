
#include "production.hpp"

Production::Production() {
  waterConsumption = 0;
  electricityConsumption = 0;
  products = unordered_map<string, ProductCategory>();
}

Production::Production(int wc, int ec, const unordered_map<string, ProductCategory>&initProducts)
: waterConsumption{wc}, electricityConsumption{ec}, products{initProducts} {}

Production::Production(const Production& rhs)
: waterConsumption{rhs.waterConsumption}, electricityConsumption{rhs.electricityConsumption}, products{rhs.products} {}

Production::Production(Production&& rhs)
: waterConsumption{rhs.waterConsumption}, electricityConsumption{rhs.electricityConsumption}, products{move(rhs.products)} {}

Production::~Production() {
  products.clear();
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

unordered_map<string, ProductCategory> Production::getProducts() const {
  return products;
}
void Production::setProducts(unordered_map<string, ProductCategory> new_products) {
  products = new_products;
}

void Production::addProduct(const ProductCategory& ProductCategory) {
  products[ProductCategory.getName()] = ProductCategory;
}

void Production::addProduct(const string& name, double bp, double pr, PesticideSeverity ps) {
  products[name] = ProductCategory(name, bp, pr, ps);
}