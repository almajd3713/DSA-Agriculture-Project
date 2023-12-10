
#ifndef YEARDSA
#define YEARDSA
#include "month.hpp"
#include "worker.hpp"

class AnnualReport {
  int year;
  vector<MonthlyReport*> months;
  vector<Worker*> workers;



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
    vector<Worker*> getWorkers() const;
    void setWorkers(const vector<Worker*>&);
    
    
    void addWorker(Worker*);
    void removeWorker(Worker*);
    void addMonth(MonthlyReport*);
    // Why would you remove a month? Lord knows
    // void removeMonth(MonthlyReport*);
    // void removeMonth(int);
};







#endif