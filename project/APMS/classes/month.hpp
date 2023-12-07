
#ifndef MONTHDSA
#define MONTHDSA
#include "land_data.hpp"

class MonthlyReport {
  int month;
  LandData data;

  public:
    MonthlyReport(int m, LandData ld)
      : month{m}, data{ld} {}

    int getMonth() const;
    void setMonth(int);
    LandData getLandData() const;
    void setLandData(LandData);
    
    
};



#endif