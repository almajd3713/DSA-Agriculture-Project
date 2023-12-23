#ifndef WILAYADSA
#define WILAYADSA
#include "city.hpp"

class Wilaya {
  string name;
  vector<City> cities;

  public:
    Wilaya(string n, vector<City> c)
      : name{n}, cities{c} {}

    string getName() const;
    void setName(string);
    vector<City> getCities() const;
    void setCities(vector<City>);
    
      
};





#endif