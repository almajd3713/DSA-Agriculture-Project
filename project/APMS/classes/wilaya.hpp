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
    string name;
    int id;
    vector<City> cities; // array of cities

public:
    Wilaya();
    //parameterized constructor
    Wilaya(int, const string&, const vector<City>&);
    Wilaya(const Wilaya&);
    Wilaya(Wilaya&&);
    ~Wilaya();
    //getter and setter
    int getWilayaId()const;
    void setId(const int&);
    string getName()const;
    void setName(const string&);
    vector<City> getCity()const;
    void setCity(const vector<City>&);

    //add city to the wilaya
    void addCity(const City&);
    //remove city from the wilaya
    void removeCity(const City&);
    void removeCity(const string&);

    //overloading < operator
    bool operator<(const Wilaya&)const;
};

#endif