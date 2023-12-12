#include<algorithm>
#include "area.hpp"
using std::move;

Area::Area() {
    name = "";
    id = 0;
    lands = std::vector<Land*>();
}
Area::~Area() {
     lands.clear();    
}

Area::Area(const std::string& name, const int& id, const std::vector<Land*>& lands) : name{name}, id{id}, lands{lands} {}

Area::Area(const Area& rhs)
    : name{rhs.name}, id{rhs.id}, lands{rhs.lands} {}

Area::Area(Area&& rhs)
    : name{move(rhs.name)}, id{rhs.id}, lands{move(rhs.lands)} {}



string Area::getName() const {
    return name;
}

std::vector<Land*> Area::getLands() const {
    return lands;
}

int Area::getId() const {
    return id;
}

void Area::setId(const int& id) {
    this->id = id;
}

void Area::setName(const string& name) {
    this->name = name;
}

void Area::setLands(const std::vector<Land*>& lands) {
    this->lands = lands;
}

void Area::addLand(Land* land) {
    lands.push_back(land);
}

void Area::removeLand(Land* land) {
    lands.erase(std::remove(lands.begin(), lands.end(), land), lands.end());
}

// void Area::removeLand(/*const std::string& landName*/ const int& landId) {
//     lands.erase(std::remove_if(lands.begin(), lands.end(), [&landId](const Land& land) {
//         return land.getId() == landId;
//     }), lands.end());
// }

bool Area::operator<(const Area& rhs) const {
    return id < rhs.id;
}

Area& Area::operator=(const Area& rhs) {
    name = rhs.name;
    id = rhs.id;
    lands = rhs.lands;
    return *this;
}

bool Area::operator==(const Area& rhs) {
    return id == rhs.id;
}
//print function
void Area::Print_Area_By_Year(int year)
{
    cout<< "Year :"<<year<<endl;
    for(auto land : lands)
    {
        cout<<*land->getFarmer()<<endl;
        land->printAnualReport(year);
     }
}