
#ifndef LANDDSA
#define LANDDSA
#include "worker.hpp"
#include "year.hpp"



class Land {
  int id;
  AnnualReport* report;

  public:
    Land(int i, AnnualReport r[12])
      : id{i}, report{r} {};

    int getId() const;
    void setId(int);
    AnnualReport* getReport() const;
    void setReport(AnnualReport*);
    
  
};



#endif