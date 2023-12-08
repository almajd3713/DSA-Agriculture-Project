
#ifndef PRODUCTDSA
#define PRODUCTDSA
#include <string>
#include "enums.hpp"

using namespace std;

class Product {
  string name;
  double basePrice;
  double production;
  PesticideSeverity pestSeverity;

  public:
  Product();
  Product(string n, double bp, double pr, PesticideSeverity ps);
  Product(const Product&);
  Product(Product&&);

  double getPureSales() const;
  double getPenalty() const;
  double getSales() const;
  double getRatio(const double&) const;

  string getName() const;
  void setName(string);
  double getBasePrice() const;
  void setBasePrice(double);
  double getProduction() const;
  void setProduction(double);
  PesticideSeverity getPestSeverity() const;
  void setPestSeverity(PesticideSeverity);

  Product& operator=(const Product&);
  
};





#endif