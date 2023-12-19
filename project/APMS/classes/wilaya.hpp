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
	int getId()const;
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
	void print_wilaya_by_year(const int& year);
	int get_wilaya_total_sales_per_year(int year);
	int get_wilaya_total_sales_per_month(int year,int month);


	void print_wilaya_monthly_farmer_sales(int year,int month);
	void print_wilaya_yearly_farmer_sales(int year);
	string printWilaya(int);

	friend void to_json(json&, const Wilaya&);
};




#endif