#pragma once
#ifndef WILAYADSA
#define WILAYADSA
#include "city.hpp"

class Wilaya {
	string name;
	int id;
	vector<City*> cities; // array of cities

public:
	Wilaya();
	//parameterized constructor
	Wilaya(int, const string&, const vector<City*>&);
	Wilaya(const Wilaya&);
	Wilaya(Wilaya&&);
	~Wilaya();
	//getter and setter
	int getWilayaId()const;
	void setId(const int&);
	string getName()const;
	void setName(const string&);
	vector<City*> getCity()const;
	void setCity(const vector<City*>&);

	//add city to the wilaya
	void addCity(City*);
	//remove city from the wilaya
	void removeCity(City*);
	// void removeCity(const string&);

	//overloading < operator
	bool operator<(const Wilaya&) const;
	bool operator==(const Wilaya&);

	friend ostream &operator<<(ostream&, const Wilaya&);
	
	void print_wilaya_by_month(const int year,const int& month);
	void print_wilaya_by_year(const int& year,int choice);
	double get_wilaya_total_sales_per_year(int year);
	double get_wilaya_total_sales_per_month(int year,int month);


	void print_wilaya_monthly_farmer_sales(int year,int month);
	void print_wilaya_yearly_farmer_sales(int year);


	// functions to print the monthly and yearly penalty of the wilaya (query 3)
	void print_wilaya_monthly_penalty(int year,int month,string category_name);
	void print_wilaya_yearly_penalty(int year,string category_name);
	//functions to get the water and electricity consumption of the wilaya
	double get_wilaya_yearly_water_consumption(int year);
	double get_wilaya_yearly_electricity_consumption(int year);
	//functions to get the water and electricity consumption of the wilaya in a month
	double get_wilaya_monthly_water_consumption(int year,int month);
	double get_wilaya_monthly_electricity_consumption(int year,int month);

	//functions to print the the summarized report of the wilaya
	void print_wilaya_summarized_by_year(int year);
	void print_wilaya_summarized_by_month(int year,int month);
};




#endif