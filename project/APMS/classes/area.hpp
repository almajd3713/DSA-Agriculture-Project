#include <iostream>
#include <string>
#include <vector>
#include "Land.hpp"
class Area {

public:
    Area();
    Area(const std::string& , const std::vector<Land>&);

    // Copy constructor
    Area(const Area& rhs)
    //setters and  getters
    std::string getName()const;
    std::vector<Land> getLands()const;
    void setName(const std::string&);
    void setLands(const std::vector<Land>&);
    void addLand(const Land&);
    void removeLand(const Land&);
    void removeLand(const std::string&);

    private:
    std::string name;
    std::vector<Land> lands;

};
