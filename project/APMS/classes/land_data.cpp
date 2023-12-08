
#include "land_data.hpp"

LandData::LandData() {
  waterConsumption = 0;
  electricityConsumption = 0;
  products = unordered_map<string, Product>();
}

LandData::LandData(int wc, int ec, const unordered_map<string, Product>&initProducts)
: waterConsumption{wc}, electricityConsumption{ec}, products{initProducts} {}

LandData::LandData(const LandData& rhs)
: waterConsumption{rhs.waterConsumption}, electricityConsumption{rhs.electricityConsumption}, products{rhs.products} {}

LandData::LandData(LandData&& rhs)
: waterConsumption{rhs.waterConsumption}, electricityConsumption{rhs.electricityConsumption}, products{move(rhs.products)} {}

LandData::~LandData() {
  products.clear();
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

unordered_map<string, Product> LandData::getProducts() const {
  return products;
}
void LandData::setProducts(unordered_map<string, Product> new_products) {
  products = new_products;
}

void LandData::addProduct(const Product& product) {
  products[product.getName()] = product;
}

void LandData::addProduct(const string& name, double bp, double pr, PesticideSeverity ps) {
  products[name] = Product(name, bp, pr, ps);
}