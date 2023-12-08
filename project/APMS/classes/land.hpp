
#ifndef LANDDSA
#define LANDDSA
#include "worker.hpp"
#include "year.hpp"



class Land {
  int id;
  AnnualReport** report;

  public:
    Land();
    Land(int, AnnualReport**);
    Land(const Land&);
    Land(Land&&);
    ~Land();

    int getId() const;
    void setId(int);
    AnnualReport** getReport() const;
    void setReport(AnnualReport**);

    void addYear(const AnnualReport&);
    void removeYear(const AnnualReport&);
    void removeYear(int);
};



#endif