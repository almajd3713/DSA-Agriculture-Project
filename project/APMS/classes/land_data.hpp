
#ifndef LANDDATADSA
#define LANDDATADSA
#include <string>
#include <unordered_map>
#include "product.hpp"
using namespace std;

class LandData {
  int waterConsumption;
  int eletricityConsumption;
  unordered_map<string, Product> products;

  public:
    LandData(int wc, int ec, const unordered_map<string, Product>& initProducts = {})
    : waterConsumption{wc}, eletricityConsumption{ec}, products{initProducts} {}

    int getWaterConsumption() const;
    void setWaterConsumption(int);
    int getElectricityConsumption() const;
    void setElectricityConsumption(int);
    unordered_map<string, Product> getProducts() const;
    void setProducts(unordered_map<string, Product>);
    
    

};










#endif