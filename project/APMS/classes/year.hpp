
#ifndef YEARDSA
#define YEARDSA
#include "month.hpp"
#include "worker.hpp"

class AnnualReport {
  friend ostream& operator<<(ostream&, const AnnualReport&);
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
    vector<MonthlyReport*> getMonths() const;
    void setMonths(vector<MonthlyReport*>);
    vector<Worker*> getWorkers() const;
    void setWorkers(const vector<Worker*>&);
    
    
    void addWorker(Worker*);
    void removeWorker(Worker*);
    void addMonth(MonthlyReport*);

    MonthlyReport* getMonthlyReport(int month);
    // Why would you remove a month? Lord knows
    // void removeMonth(MonthlyReport*);
    // void removeMonth(int);
};







#endif