
#include "production.hpp"

Production::Production() {
  waterConsumption = 0;
  electricityConsumption = 0;
  categories = unordered_map<string, ProductCategory *>();
}

Production::Production(int wc, int ec, const unordered_map<string, ProductCategory*>&initcategories)
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

unordered_map<string, ProductCategory*> Production::getCategories() const {
  return categories;
}
void Production::setCategories(unordered_map<string, ProductCategory*> new_categories) {
  categories = new_categories;
}

void Production::addProduct(ProductCategory* category) {
  categories[category->getName()] = category;
}

void Production::addProduct(const string& name, double bp, double pr, PesticideSeverity ps) {
  categories[name] = new ProductCategory(name, bp, pr, ps);
}

ostream &operator<<(ostream& os, const Production& data) {
  os << "Water Consumption: " << data.getWaterConsumption() << endl
     << "Electricity Consumption: " << data.getElectricityConsumption() << endl
     << "Products: " << endl;
    int i = 1;
  for(auto& it: data.categories) {
    os << "Product " << i << ": " << it.first << endl
    << "Production: " << it.second->getProduction() << endl
    << "Price/unit: " << it.second->getBasePrice() << endl
    << "Total sales: " << it.second->getGrossSales() << endl
    << "Net sales: " << it.second->getPureSales() << endl
    << "==============================" << endl;
    i++;
  }
  return os;
};

ProductCategory* Production::getCategory(string cat) {
  if(categories.find(cat) != categories.end()) return categories[cat];
  else return nullptr;
}

void to_json(json& j, const Production& production) {
  j = json {
    {"waterConsumption", production.getWaterConsumption()},
    {"electricityConsumption", production.getElectricityConsumption()}
  };
  for(const auto&[key, val]: production.getCategories()) {
    j["products"].push_back(*val);
  }
}

int Production::summarizedSales() {
  for(const pair<const string, ProductCategory*>& entry: getCategories()) {
    // ProductCategory* cat = entry.second;
    
  }
  return 1;
}