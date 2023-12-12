
#ifndef PRODUCTDSA
#define PRODUCTDSA
#include <string>
#include "enums.hpp"
#include <iostream>

using namespace std;

class category {
friend ostream& operator<<(ostream&, const category&);

  string name;
  double basePrice;
  double production;
  PesticideSeverity pestSeverity;

  public:
  category();
  category(string n, double bp, double pr, PesticideSeverity ps);
  category(const category&);
  category(category&&);

  double getGrossSales() const;
  double getPenalty() const;
  double getPureSales() const;
  double getRatio(const double&) const;

  string getName() const;
  void setName(string);
  double getBasePrice() const;
  void setBasePrice(double);
  double getProduction() const;
  void setProduction(double);
  PesticideSeverity getPestSeverity() const;
  void setPestSeverity(PesticideSeverity);

  category& operator=(const category&);
  
};





#endif