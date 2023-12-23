
#ifndef AREADSA
#define AREADSA
#include "land.hpp"

class Area {
  string name;
  vector<Land> lands;

  public:
    Area(string n, vector<Land> l):
      name{n}, lands{l} {}

    string getName() const;
    void setName(string);
    vector<Land> getLands() const;
    void setLands(vector<Land>);
    
};






#endif
