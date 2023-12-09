#ifndef MONTHDSA
#define MONTHDSA
#include "land_data.hpp"

class MonthlyReport {
  int month;
  LandData data;

  public:
    MonthlyReport();
    MonthlyReport(int, const LandData&);
    MonthlyReport(const MonthlyReport&);
    MonthlyReport(MonthlyReport&&);
    ~MonthlyReport();

    int getMonth() const;
    void setMonth(int);
    LandData getLandData() const;
    void setLandData(const LandData&);
    
};



#endif