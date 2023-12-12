
#ifndef LANDDATADSA
#define LANDDATADSA
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "product_category.hpp"
using namespace std;

class Production {
friend ostream& operator<<(ostream&, const Production&);//left for redwan to do it (unordered_map issues :( 
  int waterConsumption;
  int electricityConsumption;
  unordered_map<string, ProductCategory> categories;

  public:
    Production();
    Production(int, int, const unordered_map<string, ProductCategory>&);
    Production(const Production&);
    Production(Production&&);
    ~Production();
    
    int getWaterConsumption() const;
    void setWaterConsumption(int);
    int getElectricityConsumption() const;
    void setElectricityConsumption(int);
    unordered_map<string, ProductCategory> getcategories() const;
    void setcategories(unordered_map<string, ProductCategory>);
    
    void addProduct(const string&, double, double, PesticideSeverity);
    void addProduct(const ProductCategory&);

    Production& operator=(const Production& rhs) {
      electricityConsumption = rhs.electricityConsumption;
      waterConsumption = rhs.waterConsumption;
      categories = rhs.categories;
      return *this;
    }

};










#endif