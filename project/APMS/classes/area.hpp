#include <iostream>
#include <string>
#include <vector>
#include "Land.hpp"
class Area {

public:
    Area();
    Area(const std::string& , const int& ,const std::vector<Land>&);
    ~Area();
    //setters and  getters
    std::string getAreaName()const;
    std::vector<Land> getLands() const;
    int getAreaID()const;
    void setAreaID(const int&);
    void setAreaName(const std::string&);
    void setLands(const std::vector<Land>&);

    //add or remove a land to/from the Area
    void addLand(const Land&);
    void removeLand(const Land&);
    void removeLand(const std::string&);

    //overloading < operator
    bool operator<(const Area&)const; 


    private:
    std::string name;
    int ID;
    std::vector<Land> lands;

};
