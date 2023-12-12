
#include "product.hpp"

category::category() {
  name = "";
  basePrice = 0;
  production = 0;
  pestSeverity = PesticideSeverity::light;
}

category::category(string n, double bp, double pr, PesticideSeverity ps)
: name{n}, basePrice{bp}, production{pr}, pestSeverity{ps} {};

category::category(const category& rhs)
: name{rhs.name}, basePrice{rhs.basePrice}, production{rhs.production}, pestSeverity{rhs.pestSeverity} {}

category::category(category&& rhs)
: name{move(rhs.name)}, basePrice{rhs.basePrice}, production{rhs.production}, pestSeverity{move(rhs.pestSeverity)} {}

string category::getName() const {
  return name;
}
void category::setName(string new_name) {
  name = new_name;
}

double category::getProduction() const {
  return production;
}
void category::setProduction(double new_production) {
  production = new_production;
}

double category::getBasePrice() const {
  return basePrice;
}
void category::setBasePrice(double new_basePrice) {
  basePrice = new_basePrice;
}

PesticideSeverity category::getPestSeverity() const {
  return pestSeverity;
}
void category::setPestSeverity(PesticideSeverity new_pestSeverity) {
  pestSeverity = new_pestSeverity;
}

double category::getPureSales() const {
  return getGrossSales() - getPenalty();
}

double category::getGrossSales() const {
  return production * basePrice;
}

double category::getRatio(const double& wConsumption) const {
  return getPureSales() / wConsumption;
}

double category::getPenalty() const {
  return getGrossSales() * ( (10* pestSeverity) / 100);
}

category& category::operator=(const category& rhs) {
  name = rhs.name;
  basePrice = rhs.basePrice;
  production = rhs.production;
  pestSeverity = rhs.pestSeverity;
  return *this;
}

ostream& operator<<(ostream& out, const category& rhs) {
  out << "Name: " << rhs.name << endl;
  out << "Production: " << rhs.production << endl;
  out << "Base Price: " << rhs.basePrice << endl;
  out << "gross sales" << rhs.getGrossSales() << endl;

  out << "Pesticide Severity: " << rhs.pestSeverity << endl;
  out<< "Penalty: " << rhs.getPenalty() << endl;

  out << " Pure Sales(after penalty) : " << rhs.getPureSales() << endl;

  return out;
}