
#include "production.hpp"

Production::Production() {
  waterConsumption = 0;
  electricityConsumption = 0;
  categories = unordered_map<string, ProductCategory *>();
}

Production::Production(double wc, double ec, const unordered_map<string, ProductCategory*>&initcategories)
: waterConsumption{wc}, electricityConsumption{ec}, categories{initcategories} {}

Production::Production(const Production& rhs)
: waterConsumption{rhs.waterConsumption}, electricityConsumption{rhs.electricityConsumption}, categories{rhs.categories} {}

Production::Production(Production&& rhs)
: waterConsumption{rhs.waterConsumption}, electricityConsumption{rhs.electricityConsumption}, categories{move(rhs.categories)} {}

Production::~Production() {
  categories.clear();
}

double Production::getWaterConsumption() const {
  return waterConsumption;
}
void Production::setWaterConsumption(double new_waterConsumption) {
  waterConsumption = new_waterConsumption;
}

double Production::getElectricityConsumption() const {
  return electricityConsumption;
}
void Production::setElectricityConsumption(double new_electricityConsumption) {
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
  os << dye::aqua(stringRepeat("=", getConsoleWidth() / 2)) << endl;
  os << "Water Consumption: " << data.getWaterConsumption() <<" m³"<< endl
     << "Electricity Consumption: " << data.getElectricityConsumption() <<" kWh"<< endl;
  os << dye::light_yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;

  int i = 1;
  for(auto& it: data.categories) {
  os << dye::light_yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;

    os << "Product " << i << ": " << it.first << endl
    << "Production: " << it.second->getProduction() <<" KG"<< endl
    << "Price/unit: " << it.second->getBasePrice() <<" DA/KG"<< endl
    << "Total sales: " << it.second->getGrossSales() <<(it.second->getGrossSales() > 1000000 ? it.second->getGrossSales()/ 1000000 : it.second->getGrossSales() > 1000 ? it.second->getGrossSales() / 1000 : it.second->getGrossSales()) 
    <<(it.second->getGrossSales() > 1000000 ? "MDA" : it.second->getGrossSales() > 1000 ? "KDA" : "DA")<<endl
    << "Net sales: " << it.second->getPureSales() <<(it.second->getPureSales()  > 1000000 ? (it.second->getPureSales()  / 1000000) : it.second->getPureSales()  > 1000 ? (it.second->getPureSales()  / 1000): it.second->getPureSales() )
    <<(it.second->getPureSales()  > 1000000 ? "MDA" : it.second->getPureSales()  > 1000 ? "KDA" : "DA")<<endl;
    i ++;
    os << dye::light_yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
  }
  os << dye::aqua(stringRepeat("=", getConsoleWidth() / 2)) << endl;
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

double Production::summarizedSales() {
  double sum = 0;
  for(const pair<const string, ProductCategory*>& entry: getCategories()) {
    ProductCategory* cat = entry.second;
    sum += cat->getPureSales();
    
  }
  return sum;
}

double Production::get_Category_Penalty(const string& cat) {
  if(categories.find(cat) != categories.end()) {
    return categories[cat]->getPenalty();
  } else return 0;
}