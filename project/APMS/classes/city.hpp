
#include <iostream>
#include <vector> 
#include <string> 
#include "Area.hpp" 

using namespace std;   

template<typename Area>
class City {

public:
    City();
    //parameterized constructor
    City(const std::string&, const std::vector<Area>&);
    ~City();
    City(const City& rhs);  //copy constructor
    //getter and setter
    string getName();
    Area getArea(int index);
    void setName(string name);
    void setArea(vector<Area> areas);

    //add area to the city
    void addArea(const Area&);
    //remove area from the city
    void removeArea(const Area&);
    void removeArea(const string&);



private:
    std::string name;
    std::vector<Area> areas; 
};

