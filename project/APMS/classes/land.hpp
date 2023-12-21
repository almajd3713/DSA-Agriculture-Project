#pragma once
#ifndef LANDDSA
#define LANDDSA
#include "worker.hpp"
#include "year.hpp"



class Land {
friend ostream& operator<<(ostream&, const Land&);

  int id;
  vector<AnnualReport*> reports;// hash table to access directly to the year
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
    
    vector<Worker*> getWorkers() const;
    void setWorkers(const vector<Worker*>&);
  
    AnnualReport* getAnnualReport(int year);
    void printAnnualReport(int year,int choice);
    void printMonthlyReport(int year, int month);
    void addYear(AnnualReport*);
    void removeYear(AnnualReport*);
    void removeYear(int);
    void removeWorker(string);
    void removeWorker(int);

    bool operator<(const Land&);
    bool operator==(const Land&);
    Land& operator=(const Land&);

   // these function are for resumed print that return  all the sales in specific year
   double get_land_total_sales_per_year(int year);
   double get_land_total_sales_per_month(int year,int month);
   //query two of the document project 
   void print_monthly_farmer_sales(int year,int month);
   void print_yearly_farmer_sales(int year);

// functions to print the monthly and yearly penalty of the land (query 3)
void print_Land_monthly_penalty(int year,int month,string category_name); 
void print_Land_yearly_penalty(int year,string category_name);

//functions to get the water and electricity consumption of the land
double get_yearly_water_consumption(int year);
double get_yearly_electricity_consumption(int year);
//functions to get the water and electricity consumption of the land in a month
double get_monthly_water_consumption(int year,int month);
double get_monthly_electricity_consumption(int year,int month);

  
   
};



#endif