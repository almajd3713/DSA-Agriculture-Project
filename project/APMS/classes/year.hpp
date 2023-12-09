
#ifndef YEARDSA
#define YEARDSA
#include "month.hpp"

class AnnualReport {
  int year;
  vector<MonthlyReport*> months;

  public:
    AnnualReport();
    AnnualReport(int, vector<MonthlyReport*>);
    AnnualReport(const AnnualReport&);
    AnnualReport(AnnualReport&&);
    ~AnnualReport();

    int getYear() const;
    void setYear(int);
    vector<MonthlyReport*> getMonthlyReport() const;
    void setMonthlyReport(vector<MonthlyReport*>);
    
    void addMonth(MonthlyReport*);
    // Why would you remove a month? Lord knows
    // void removeMonth(MonthlyReport*);
    // void removeMonth(int);
};







#endif