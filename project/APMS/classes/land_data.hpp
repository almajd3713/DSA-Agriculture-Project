
#ifndef LANDDATADSA
#define LANDDATADSA
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "product.hpp"
using namespace std;

class LandData {
  friend ostream& operator<<(ostream&, const LandData&);
  int waterConsumption;
  int electricityConsumption;
  vector<category*> categories;

  public:
    LandData();
    LandData(int, int, const vector<category*>&);
    LandData(const LandData&);
    LandData(LandData&&);
    ~LandData();
    
    int getWaterConsumption() const;
    void setWaterConsumption(int);
    int getElectricityConsumption() const;
    void setElectricityConsumption(int);
    vector<category*> getcategories() const;
    void setcategories(vector<category*>);
    
    void addcategory(const string&, double, double, PesticideSeverity);
    void addcategory(const category&);

    LandData& operator=(const LandData& rhs) {
      electricityConsumption = rhs.electricityConsumption;
      waterConsumption = rhs.waterConsumption;
      categories= rhs.categories;
      return *this;
    }

};










#endif