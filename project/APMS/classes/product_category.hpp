#pragma once
#ifndef PRODUCTDSA
#define PRODUCTDSA
#include "enums.hpp"
#include "../misc/includes.hpp"


class ProductCategory {
  string name;
  double basePrice;
  double production;
  PesticideSeverity pestSeverity;

  public:
  ProductCategory();
  ProductCategory(string n, double bp, double pr, PesticideSeverity ps);
  ProductCategory(const ProductCategory&);
  ProductCategory(ProductCategory&&);

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

  ProductCategory& operator=(const ProductCategory&);
  
};





#endif