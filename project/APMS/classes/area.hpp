#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "land.hpp"
class Area {
    string name;
    int id;
    vector<Land*> lands;

public:
    Area();
    Area(const string& , const int& ,const vector<Land*>&);
    Area(const Area&);
    Area(Area&&);
    ~Area();
    //setters and  getters
    string getName() const;
    vector<Land*> getLands() const;
    int getId()const;
    void setId(const int&);
    void setName(const std::string&);
    void setLands(const std::vector<Land*>&);

    //add or remove a land to/from the Area
    void addLand(Land*);
    void removeLand(Land*);
    // void removeLand(const int&);

    //overloading < operator
    bool operator<(const Area&) const; 
    bool operator==(const Area&);
    Area& operator=(const Area&);
    //print  the data  of area by year 
    void Print_Area_By_Year(int year);

    friend ostream& operator<<(ostream&, const Area&);
    friend void to_json(json&, const Area&);
};
