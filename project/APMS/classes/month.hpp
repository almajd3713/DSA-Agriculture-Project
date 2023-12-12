#ifndef MONTHDSA
#define MONTHDSA
#include "land_data.hpp"

class MonthlyReport {
  friend ostream& operator<<(ostream&, const MonthlyReport&);
  int month;
  LandData* data;

  public:
    MonthlyReport();
    MonthlyReport(int, LandData*);
    MonthlyReport(const MonthlyReport&);
    MonthlyReport(MonthlyReport&&);
    ~MonthlyReport();

    int getMonth() const;
    void setMonth(int);
    LandData* getLandData() const;
    void setLandData(LandData*);
    
};



#endif