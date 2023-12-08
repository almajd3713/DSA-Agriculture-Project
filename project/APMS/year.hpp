
#ifndef YEARDSA
#define YEARDSA
#include "month.hpp"

class AnnualReport {
  int year;
  MonthlyReport* months;

  public:
    AnnualReport();
    AnnualReport(int, MonthlyReport*);
    AnnualReport(const AnnualReport&);
    AnnualReport(AnnualReport&&);
    ~AnnualReport();

    int getYear() const;
    void setYear(int);
    MonthlyReport* getMonthlyReport() const;
    void setMonthlyReport(MonthlyReport*);
    
    void addMonth(const MonthlyReport&);
    void removeMonth(const MonthlyReport&);
    void removeMonth(int);
};







#endif