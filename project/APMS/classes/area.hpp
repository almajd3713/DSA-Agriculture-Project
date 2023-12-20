#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "land.hpp"
class Area {
    string name;
    int id;
    vector<Land*> lands;

public:
    Area();
    Area(const string& , const int& ,const vector<Land*>&);
    Area(const Area&);
    Area(Area&&);
    ~Area();
    //setters and  getters
    string getName() const;
    vector<Land*> getLands() const;
    int getId()const;
    void setId(const int&);
    void setName(const std::string&);
    void setLands(const std::vector<Land*>&);

    //add or remove a land to/from the Area
    void addLand(Land*);
    void removeLand(Land*);
    // void removeLand(const int&);

    //overloading < operator
    bool operator<(const Area&) const; 
    bool operator==(const Area&);
    Area& operator=(const Area&);
    //print  the data  of area by year 
    void Print_Area_By_Year(int year,int choice);
    void Print_Area_By_month(int year,int month);
    //resumed print 
    int get_area_total_sales_per_year(int year);
    int get_area_total_sales_per_month(int year,int month);


    friend ostream& operator<<(ostream&, const Area&);

   //query two of the document project
    void print_area_monthly_farmer_sales(int year,int month);
    void print_area_yearly_farmer_sales(int year);
   
    // functions to print the monthly and yearly penalty of the area (query 3)
    void print_Area_monthly_penalty(int year,int month,string category_name);
    void print_Area_yearly_penalty(int year,string category_name);
    //functions to get the water and electricity consumption of the area
    int get_area_yearly_water_consumption(int year);
    int get_area_yearly_electricity_consumption(int year);
    //functions to get the water and electricity consumption of the area in a month
    int get_area_monthly_water_consumption(int year,int month);
    int get_area_monthly_electricity_consumption(int year,int month);
    

};
