
#ifndef YEARDSA
#define YEARDSA
#include "month.hpp"

class AnnualReport {
  int year;
  MonthlyReport* months;

  public:
    AnnualReport(int y, MonthlyReport m[12])
      : year{y}, months{m} {}

    int getYear() const;
    void setYear(int);
    MonthlyReport* getMonthlyReport() const;
    void setMonthlyReport(MonthlyReport*);
    
};







#endif