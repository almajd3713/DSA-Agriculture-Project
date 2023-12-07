#ifndef WILAYADSA
#define WILAYADSA
#include <iostream>
#include <string>
#include "City.hpp"
#include <vector>
#include <algorithm>

using namespace std;
using std::vector;
class Wilaya {

 public:
    Wilaya();
    //parameterized constructor
    Wilaya(const std::string&,const int&, const std::vector<City>&);
    ~Wilaya();
    //getter and setter
    int getWilayaID()const;
    string getName()const;
    vector<City> getCity()const;
    void setName(const string&);
    void setCity(const vector<City>&);
    void setWilayaID(const int&);

    //add city to the wilaya
    void addCity(const City&);
    //remove city from the wilaya
    void removeCity(const City&);
    void removeCity(const string&);
    
    //overloading < operator
    bool operator<(const Wilaya&)const;
    


    private:
    string name;
    int ID;
    vector<City> Cities; // array of cities
};

#endif