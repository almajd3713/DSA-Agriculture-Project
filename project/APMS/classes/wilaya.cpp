#include "wilaya.hpp"

// Wilaya::Wilaya() {
//     name = "";
//     id = 0;
//     cities = vector<City>();
// }

// Wilaya::Wilaya(const std::string& name, const int& id, const std::vector<City>& cities) : name(name), id(id), cities(cities) {}

// Wilaya::Wilaya(const Wilaya& rhs)
// : name{rhs.name}, id{rhs.id}, cities{rhs.cities} {}

// Wilaya::Wilaya(Wilaya&& rhs)
// : name{move(rhs.name)}, id{rhs.id}, cities{move(rhs.cities)} {}

// Wilaya::~Wilaya()
// {
//     cities.clear();
// }
Wilaya::Wilaya()
{
    id = 0;
    name = "";
    cities = vector<City *>();
}

Wilaya::Wilaya(int id, const string &name, const vector<City *> &cities)
    : id{id}, name{name}, cities{cities} {}

Wilaya::Wilaya(const Wilaya &rhs)
    : id{rhs.id}, name{rhs.name}, cities{rhs.cities} {}

Wilaya::Wilaya(Wilaya &&rhs)
    : id{move(rhs.id)}, name{move(rhs.name)}, cities{move(rhs.cities)} {}

Wilaya::~Wilaya()
{
    cout << "deopcvfk" << endl;
    cities.clear();
}

int Wilaya::getWilayaId() const
{
    return id;
}

std::string Wilaya::getName() const
{
    return name;
}

std::vector<City *> Wilaya::getCity() const
{
    return cities;
}

void Wilaya::setName(const std::string &name)
{
    this->name = name;
}

void Wilaya::setCity(const std::vector<City *> &cities)
{
    this->cities = cities;
}

void Wilaya::setId(const int &id)
{
    this->id = id;
}

void Wilaya::addCity(City *city)
{
    cities.push_back(city);
}

void Wilaya::removeCity(City *city)
{
    cities.erase(remove(cities.begin(), cities.end(), city), cities.end());
}

// void Wilaya::removeCity(const string& cityName) {
//     cities.erase(remove_if(cities.begin(), cities.end(), [&cityName](const City& city) {
//         return city.getName() == cityName;
//     }), cities.end());
// }

bool Wilaya::operator<(const Wilaya &rhs) const
{
    return id < rhs.id;
}

bool Wilaya::operator==(const Wilaya &rhs)
{
    return id == rhs.id;
}

ostream &operator<<(ostream &os, const Wilaya &wil)
{
    // os << "Land ID: " << land.id << endl;
    // os << "Farmer: " << land.farmer->getName() << endl;
    // os << "Annual Reports: " << endl;
    // for (auto year : land.reports)
    // {
    //   os << *year << endl;
    // }
    os << "Wilaya ID: " << wil.getWilayaId() << endl;
    os << "Wilaya: " << wil.getName() << endl;
    os << "Cities: " << endl;
    cout << setfill('=') << setw(40) << "" << endl;
    for (City *cit : wil.getCity())
    {
        os << "\t" << *cit;
    }
    cout << setfill('=') << setw(40) << "" << endl;

    return os;
}
// detailed print
void Wilaya::print_wilaya_by_month(const int year, const int &month)
{
    cout << "Wilaya ID: " << getWilayaId() << endl;
    cout << "Wilaya: " << getName() << endl;
    cout << "Cities: " << endl;
    cout << setfill('=') << setw(40) << "" << endl;
    for (City *cit : getCity())
    {
        cout << "\t" << *cit;
        cit->print_city_by_month(year, month);
    }
    cout << setfill('=') << setw(40) << "" << endl;
}

void Wilaya::print_wilaya_by_year(const int &year)
{
    cout << "Wilaya ID: " << getWilayaId() << endl;
    cout << "Wilaya: " << getName() << endl;
    cout << "Cities: " << endl;
    cout << setfill('=') << setw(40) << "" << endl;
    for (City *cit : getCity())
    {
        cout << "\t" << *cit;
        cit->print_city_by_year(year);
    }
    cout << setfill('=') << setw(40) << "" << endl;
}
int Wilaya::get_wilaya_total_sales_per_year(int year)
{
    int total = 0;
    for (City *cit : getCity())
    {
        total += cit->get_city_total_sales_per_year(year);
    }
    return total;
}
int Wilaya::get_wilaya_total_sales_per_month(int year, int month)
{
    int total = 0;
    for (City *cit : getCity())
    {
        total += cit->get_city_total_sales_per_month(year, month);
    }
    return total;
}

void Wilaya::print_wilaya_monthly_farmer_sales(int year, int month)
{
    cout << "Wilaya ID: " << getWilayaId() << endl;
    cout << "Wilaya: " << getName() << endl;
    cout << setfill('=') << setw(40) << "" << endl;
    for (City *cit : getCity())
    {
        cit->print_city_monthly_farmer_sales(year, month);
    }
    cout << setfill('=') << setw(40) << "" << endl;
}
void Wilaya::print_wilaya_yearly_farmer_sales(int year)
{
    cout << "Wilaya ID: " << getWilayaId() << endl;
    cout << "Wilaya: " << getName() << endl;
    cout << setfill('=') << setw(40) << "" << endl;
    for (City *cit : getCity())
    {
        cit->print_city_yearly_farmer_sales(year);
    }
    cout << setfill('=') << setw(40) << "" << endl;
}

// functions to print the monthly and yearly penalty of the wilaya (query 3)
void Wilaya::print_wilaya_monthly_penalty(int year, int month, string category_name)
{
    cout << "Wilaya ID: " << getWilayaId() << endl;
    cout << "Wilaya: " << getName() << endl;
    cout << setfill('=') << setw(40) << "" << endl;
    for (City *cit : getCity())
    {
        cit->print_city_monthly_penalty(year, month, category_name);
    }
    cout << setfill('=') << setw(40) << "" << endl;
}
void Wilaya::print_wilaya_yearly_penalty(int year, string category_name)
{
    cout << "Wilaya ID: " << getWilayaId() << endl;
    cout << "Wilaya: " << getName() << endl;
    cout << setfill('=') << setw(40) << "" << endl;
    for (City *cit : getCity())
    {
        cit->print_city_yearly_penalty(year, category_name);
    }
    cout << setfill('=') << setw(40) << "" << endl;
}
