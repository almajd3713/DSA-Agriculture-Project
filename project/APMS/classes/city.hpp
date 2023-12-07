
#include <iostream>
#include <vector> 
#include <string> 
#include "Area.hpp" 

using namespace std;   

class City {

public:
    City();
    //parameterized constructor
    City(const std::string&,const int&, const std::vector<Area>&);
    ~City();
    //getter and setter

    string getName()const;
    int getCityID()const;
    std::vector<Area> getArea()const;
    void setName(const string &name);
    void setArea(const vector<Area>& areas);
    void setCityID(const int& );

    //add area to the city
    void addArea(const Area&);
    //remove area from the city
    void removeArea(const Area&);
    void removeArea(const string&);

    //overloading < operator
    bool operator<(const City&)const; 


private:
    string name;
    int ID;
    std::vector<Area> areas; 
};

