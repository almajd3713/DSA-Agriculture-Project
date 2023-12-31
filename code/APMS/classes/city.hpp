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
    int getId()const;
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
    double get_city_total_sales_per_year(int year);
    double get_city_total_sales_per_month(int year,int month);

    friend ostream& operator<<(ostream&, const City&);
    //query two of the document project
    void print_city_monthly_farmer_sales(int year,int month);
    void print_city_yearly_farmer_sales(int year);
    friend void to_json(json&, const City&);
    // functions to print the monthly and yearly  penalty of the city(query 3)
    void print_city_monthly_penalty(int year,int month,string category_name);
    void print_city_yearly_penalty(int year,string category_name);
    //functions to get the water and electricity consumption of the city
    double get_city_yearly_water_consumption(int year);
    double get_city_yearly_electricity_consumption(int year);
    //functions to get the water and electricity consumption of the city in a month
    double get_city_monthly_water_consumption(int year,int month);
    double get_city_monthly_electricity_consumption(int year,int month);

    // Penalties
    double get_monthly_city_penalty(int, int, const string&);
    double get_yearly_city_penalty(int, const string&);
    //functions to print the the summarized report of the city
    void print_city_summarized_by_year(int year);
    void print_city_summarized_by_month(int year,int month);
};

