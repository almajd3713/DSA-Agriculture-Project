
#include "product_category.hpp"

ProductCategory::ProductCategory() {
  name = "";
  basePrice = 0;
  production = 0;
  pestSeverity = PesticideSeverity::light;
}

ProductCategory::ProductCategory(string n, double bp, double pr, PesticideSeverity ps)
: name{n}, basePrice{bp}, production{pr}, pestSeverity{ps} {};

ProductCategory::ProductCategory(const ProductCategory& rhs)
: name{rhs.name}, basePrice{rhs.basePrice}, production{rhs.production}, pestSeverity{rhs.pestSeverity} {}

ProductCategory::ProductCategory(ProductCategory&& rhs)
: name{move(rhs.name)}, basePrice{rhs.basePrice}, production{rhs.production}, pestSeverity{move(rhs.pestSeverity)} {}

string ProductCategory::getName() const {
  return name;
}
void ProductCategory::setName(string new_name) {
  name = new_name;
}

double ProductCategory::getProduction() const {
  return production;
}
void ProductCategory::setProduction(double new_production) {
  production = new_production;
}

double ProductCategory::getBasePrice() const {
  return basePrice;
}
void ProductCategory::setBasePrice(double new_basePrice) {
  basePrice = new_basePrice;
}

PesticideSeverity ProductCategory::getPestSeverity() const {
  return pestSeverity;
}
void ProductCategory::setPestSeverity(PesticideSeverity new_pestSeverity) {
  pestSeverity = new_pestSeverity;
}

double ProductCategory::getPureSales() const {
  return getGrossSales() - getPenalty();
}

double ProductCategory::getGrossSales() const {
  return production * basePrice;
}

double ProductCategory::getRatio(const double& wConsumption) const {
  return getPureSales() / wConsumption;
}

double ProductCategory::getPenalty() const {
  return getGrossSales() * (pestSeverity / 10);
}

ProductCategory& ProductCategory::operator=(const ProductCategory& rhs) {
  name = rhs.name;
  basePrice = rhs.basePrice;
  production = rhs.production;
  pestSeverity = rhs.pestSeverity;
  return *this;
}

void to_json(json& j, const ProductCategory& cat) {
  j = json {
    {"name", cat.getName()},
    {"basePrice", cat.getBasePrice()},
    {"production", cat.getProduction()},
    {"pesticideSeverity", cat.getPestSeverity()}
  };
}