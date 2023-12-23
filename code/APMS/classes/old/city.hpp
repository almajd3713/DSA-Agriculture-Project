
#ifndef CITYDSA
#define CITYDSA
#include "area.hpp"

class City {
  string name;
  vector<Area> areas;

  public:
    City(string n, vector<Area> a)
      : name{n}, areas{a} {}

    string getName() const;
    void setName(string);
    vector<Area> getAreas() const;
    void setAreas(vector<Area>);
    
      
};



#endif