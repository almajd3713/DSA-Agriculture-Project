#pragma once
#ifndef LANDDSA
#define LANDDSA
#include "worker.hpp"
#include "year.hpp"



class Land {
friend ostream& operator<<(ostream&, const Land&);

  int id;
  vector<AnnualReport*> reports;
  Farmer* farmer;

  public:
    Land();
    Land(int, vector<AnnualReport*>, Farmer*);
    Land(const Land&);
    Land(Land&&);
    ~Land();

    int getId() const;
    void setId(int);
    vector<AnnualReport*> getReports() const;
    void setReport(vector<AnnualReport*>);
    Farmer* getFarmer() const;
    void setFarmer(Farmer*);
    //wtf is this
    vector<Worker*> getWorkers() const;
    void setWorkers(const vector<Worker*>&);
    //
    void printAnualReport(int year);
    void addYear(AnnualReport*);
    void removeYear(AnnualReport*);
    void removeYear(int);
    void removeWorker(string);
    void removeWorker(int);

    bool operator<(const Land&);
    bool operator==(const Land&);
    Land& operator=(const Land&);
};



#endif