#ifndef MONTHDSA
#define MONTHDSA
#include "production.hpp"

class MonthlyReport {
  friend ostream& operator<<(ostream&, const MonthlyReport&);
  int month;
  Production* data;

  public:
    MonthlyReport();
    MonthlyReport(int, Production*);
    MonthlyReport(const MonthlyReport&);
    MonthlyReport(MonthlyReport&&);
    ~MonthlyReport();

    int getMonth() const;
    void setMonth(int);
    Production* getLandData() const;
    void setLandData(Production*);
    
};



#endif