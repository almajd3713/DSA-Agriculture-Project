#ifndef WILAYADSA
#define WILAYADSA
#include <iostream>
#include <string>
#include "City.hpp"
#include <vector>
#include <algorithm>

using namespace std;
using std::vector;
template<typename City>
class Wilaya {

 public:
    Wilaya();
    //parameterized constructor
    Wilaya(const std::string&, const std::vector<City>&);
    ~Wilaya();
    Wilaya(const Wilaya& rhs);  //copy constructor
    //getter and setter
    string getName()const;
    City getCity(int)const;
    void setName(const string&);
    void setCity(const vector<City>&);

    //add city to the wilaya
    void addCity(const City&);
    //remove city from the wilaya
    void removeCity(const City&);
    void removeCity(const string&);
    
    


    private:
    string name;
    vector<City> Cities; // array of cities
};

#endif