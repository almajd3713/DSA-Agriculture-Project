#include <iostream>
#include <string>
#include <vector>
#include "Land.hpp"
class Area {
    string name;
    int id;
    vector<Land> lands;

public:
    Area();
    Area(const string& , const int& ,const vector<Land>&);
    Area(const Area&);
    Area(Area&&);
    ~Area();
    //setters and  getters
    std::string getName()const;
    std::vector<Land> getLands() const;
    int getId()const;
    void setId(const int&);
    void setName(const std::string&);
    void setLands(const std::vector<Land>&);

    //add or remove a land to/from the Area
    void addLand(const Land&);
    void removeLand(const Land&);
    void removeLand(const int&);

    //overloading < operator
    bool operator<(const Area&)const; 


    private:


};
