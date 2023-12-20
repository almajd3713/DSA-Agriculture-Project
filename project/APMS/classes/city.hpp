#pragma once
#include "area.hpp" 

class City {
    string name;
    int id;
    std::vector<Area*> areas;

public: 
    City();
    //parameterized constructor
    City(const string&, const int&, const vector<Area*>&);
    City(const City&);
    City(City&&);
    ~City();
    //getter and setter

    string getName()const;
    int getCityId()const;
    std::vector<Area*> getArea()const;
    void setName(const string &name);
    void setArea(const vector<Area*>& areas);
    void setCityId(const int& );

    //add area to the city
    void addArea(Area*);
    //remove area from the city
    void removeArea(Area*);
    // void removeArea(const string&);

    //overloading < operator
    bool operator<(const City&) const;
    City &operator=(const City&);
    bool operator==(const City&);
    void print_city_by_month(const int year,const int& month);
    void print_city_by_year(const int& year,int choice);
    int get_city_total_sales_per_year(int year);
    int get_city_total_sales_per_month(int year,int month);

    friend ostream& operator<<(ostream&, const City&);
    //query two of the document project
    void print_city_monthly_farmer_sales(int year,int month);
    void print_city_yearly_farmer_sales(int year);
    // functions to print the monthly and yearly  penalty of the city(query 3)
    void print_city_monthly_penalty(int year,int month,string category_name);
    void print_city_yearly_penalty(int year,string category_name);
    //functions to get the water and electricity consumption of the city
    int get_city_yearly_water_consumption(int year);
    int get_city_yearly_electricity_consumption(int year);
    //functions to get the water and electricity consumption of the city in a month
    int get_city_monthly_water_consumption(int year,int month);
    int get_city_monthly_electricity_consumption(int year,int month);
};

