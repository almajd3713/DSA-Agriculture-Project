#pragma once
#ifndef LANDDSA
#define LANDDSA
#include "worker.hpp"
#include "year.hpp"



class Land {
  int id;
  vector<AnnualReport*> report;
  Farmer farmer;
  vector<Worker*> workers;

  public:
    Land();
    Land(int, vector<AnnualReport*>, const Farmer&, const vector<Worker*>&);
    Land(const Land&);
    Land(Land&&);
    ~Land();

    int getId() const;
    void setId(int);
    vector<AnnualReport*> getReport() const;
    void setReport(vector<AnnualReport*>);
    Farmer getFarmer() const;
    void setFarmer(const Farmer&);
    vector<Worker*> getWorkers() const;
    void setWorkers(const vector<Worker*>&);
    
    void addYear(AnnualReport*);
    void removeYear(AnnualReport*);
    void removeYear(int);
    void addWorker(Worker*);
    void removeWorker(Worker*);
    void removeWorker(string);
    void removeWorker(int);

    bool operator<(const Land&);
    bool operator==(const Land&);
    Land& operator=(const Land&);
};



#endif