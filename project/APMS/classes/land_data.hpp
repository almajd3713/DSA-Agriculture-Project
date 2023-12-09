
#ifndef LANDDATADSA
#define LANDDATADSA
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "product.hpp"
using namespace std;

class LandData {
  int waterConsumption;
  int electricityConsumption;
  unordered_map<string, Product> products;

  public:
    LandData();
    LandData(int, int, const unordered_map<string, Product>&);
    LandData(const LandData&);
    LandData(LandData&&);
    ~LandData();
    
    int getWaterConsumption() const;
    void setWaterConsumption(int);
    int getElectricityConsumption() const;
    void setElectricityConsumption(int);
    unordered_map<string, Product> getProducts() const;
    void setProducts(unordered_map<string, Product>);
    
    void addProduct(const string&, double, double, PesticideSeverity);
    void addProduct(const Product&);

    LandData& operator=(const LandData& rhs) {
      electricityConsumption = rhs.electricityConsumption;
      waterConsumption = rhs.waterConsumption;
      products = rhs.products;
      return *this;
    }

};










#endif