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

int Wilaya::getId() const {
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
    os << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    os << "Wilaya ID: " << wil.getId() << endl;
    os << "Wilaya: " << wil.getName() << endl;
    os << "Cities: " << endl;
    for (City *cit : wil.getCity())
    {
        os << *cit;
    }
    os << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;

    return os;
}
// detailed print
void Wilaya::print_wilaya_by_month(const int year, const int &month)
{
    cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout << "Wilaya ID: " << getId() << endl;
    cout << "Wilaya: " << getName() << endl;
    cout << "Cities: " << endl;
    for (City *cit : getCity())
    {
        cout << "\t" << *cit;
        cit->print_city_by_month(year, month);
    }

    double sales=0;
         sales = get_wilaya_total_sales_per_month(year,month);
         double water=0;
         water= get_wilaya_monthly_water_consumption(year,month);
         double electricity =0;
         electricity=get_wilaya_monthly_electricity_consumption(year,month);
      cout<<" area total sales :"<<sales<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
      //water and electricity consumption
        cout<<" area total water consumption :"<<water<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
        cout<<" area total electricity consumption :"<<electricity<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
    cout << setfill('=') << setw(40) << "" << endl;
    cout<< "the total_sales : " <<get_wilaya_total_sales_per_month(year,month)<<" DA "<<endl;
    //water and electricity consumption
    cout<<" total water consumption :"<<get_wilaya_monthly_water_consumption(year,month)<<" m^3 "<<endl;
    cout<<" total electricity consumption :"<<get_wilaya_monthly_electricity_consumption(year,month)<<" KWh "<<endl;
  cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
}

void Wilaya::print_wilaya_by_year(const int &year,int choice)
{
    cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout << "Wilaya ID: " << getId() << endl;
    cout << "Wilaya: " << getName() << endl;
    cout << "Cities: " << endl;
    for (City *cit : getCity())
    {
        cout << "\t" << *cit;
        cit->print_city_by_year(year,choice);
    }

    double sales=0;
         sales =get_wilaya_total_sales_per_year(year);
         double water=0;
         water= get_wilaya_yearly_water_consumption(year);
         double electricity =0;
         electricity=get_wilaya_yearly_electricity_consumption(year);
      cout<<" area total sales :"<<sales<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
      //water and electricity consumption
        cout<<" area total water consumption :"<<water<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
        cout<<" area total electricity consumption :"<<electricity<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
    cout << setfill('=') << setw(40) << "" << endl;
    cout<< "the total_sales : " <<get_wilaya_total_sales_per_year(year)<<" DA "<<endl;
    //water and electricity consumption
    cout<<" total water consumption :"<<get_wilaya_yearly_water_consumption(year)<<" m^3 "<<endl;
    cout<<" total electricity consumption :"<<get_wilaya_yearly_electricity_consumption(year)<<" KWh "<<endl;
  cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
}
double Wilaya::get_wilaya_total_sales_per_year(int year)
{
    double total = 0;
    for (City *cit : getCity())
    {
        total += cit->get_city_total_sales_per_year(year);
    }
    return total;
}
double Wilaya::get_wilaya_total_sales_per_month(int year, int month)
{
    double total = 0;
    for (City *cit : getCity())
    {
        total += cit->get_city_total_sales_per_month(year, month);
    }
    return total;
}

void Wilaya::print_wilaya_monthly_farmer_sales(int year, int month)
{
    cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout << "Wilaya ID: " << getId() << endl;
    cout << "Wilaya: " << getName() << endl;
    for (City *cit : getCity())
    {
        cit->print_city_monthly_farmer_sales(year, month);
    }
  cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    
}
void Wilaya::print_wilaya_yearly_farmer_sales(int year) {
  cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout << "Wilaya ID: " << getId() << endl;
    cout << "Wilaya: " << getName() << endl;
    
    for(City* cit: getCity()) {
        cit->print_city_yearly_farmer_sales(year);
    }
  cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
}

// functions to print the monthly and yearly penalty of the wilaya (query 3)
void Wilaya::print_wilaya_monthly_penalty(int year, int month, string category_name)
{
    cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout << "Wilaya ID: " << getId() << endl;
    cout << "Wilaya: " << getName() << endl;
    for (City *cit : getCity())
    {
        cit->print_city_monthly_penalty(year, month, category_name);
    }
    cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
}
void Wilaya::print_wilaya_yearly_penalty(int year, string category_name)
{
    cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
    cout << "Wilaya ID: " << getId() << endl;
    cout << "Wilaya: " << getName() << endl;
    for (City *cit : getCity())
    {
        cit->print_city_yearly_penalty(year, category_name);
    }
    cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
}
//functions to get the water and electricity consumption of the wilaya
double Wilaya::get_wilaya_yearly_water_consumption(int year)
{
    double total = 0;
    for (City *cit : getCity())
    {
        total += cit->get_city_yearly_water_consumption(year);
    }
    return total;
}
double Wilaya::get_wilaya_yearly_electricity_consumption(int year)
{
    double total = 0;
    for (City *cit : getCity())
    {
        total += cit->get_city_yearly_electricity_consumption(year);
    }
    return total;
}
//functions to get the water and electricity consumption of the wilaya in a month
double Wilaya::get_wilaya_monthly_water_consumption(int year, int month)
{
    double total = 0;
    for (City *cit : getCity())
    {
        total += cit->get_city_monthly_water_consumption(year, month);
    }
    return total;
}
double Wilaya::get_wilaya_monthly_electricity_consumption(int year, int month)
{
    double total = 0;
    for (City *cit : getCity())
    {
        total += cit->get_city_monthly_electricity_consumption(year, month);
    }
    return total;
}

//functions to print the the summarized report of the wilaya
void Wilaya::print_wilaya_summarized_by_year(int year)
{
    cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;

    cout << "Wilaya ID: " << getId() << endl;
    cout << "Wilaya: " << getName() << endl;
    cout << "Cities: " << endl;
    double sales = get_wilaya_total_sales_per_year(year);
    double water = get_wilaya_yearly_water_consumption(year);
    double electricity = get_wilaya_yearly_electricity_consumption(year);
  cout<<"the wilaya total sales is : "<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
  cout<<"the wilaya total water consumption is : "<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
  cout<<"the wilaya total electricity consumption is : "<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
  for (City *cit : getCity())
  {
      cout << "\t" << *cit;
      cit->print_city_summarized_by_year(year);
  }
    cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;

}

   void Wilaya::print_wilaya_summarized_by_month(int year,int month)
   {
    cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;

       cout << "Wilaya ID: " << getId() << endl;
       cout << "Wilaya: " << getName() << endl;
       cout << "Cities: " << endl;

       double sales = get_wilaya_total_sales_per_month(year,month);
       double water = get_wilaya_monthly_water_consumption(year,month);
       double electricity = get_wilaya_monthly_electricity_consumption(year,month);
       cout<<"the wilaya total_sales : "<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales);
       cout << (sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA") << endl;
       cout<<" the wilaya total water consumption :"<<(water > 1000000 ? water / 1000000 : water > 1000 ? water / 1000 : water);
       cout << (water > 1000000 ? " M^3" : water > 1000 ? " K^3" : " ^3") << endl;
       cout<<" the wilaya total electricity consumption :"<<(electricity > 1000000 ? electricity / 1000000 : electricity > 1000 ? electricity / 1000 : electricity);
       cout << (electricity > 1000000 ? " MKWh" : electricity > 1000 ? " KKWh" : " KWh") << endl;
       for (City *cit : getCity())
       {
           //    cout << "\t" << *cit;
           cit->print_city_summarized_by_month(year, month);
       }
       cout << dye::yellow(stringRepeat("=", getConsoleWidth() / 2)) << endl;
   } 


void to_json(json& j, const Wilaya& wil) {
  j = json{
    {"name", wil.getName()},
    {"id", wil.getId()},
  };
  for(City* cit: wil.getCity()) {
    j["cities"].push_back(*cit);
  }
}

double Wilaya::get_monthly_wilaya_penalty(int year, int month, const string &category_name)
{
    double sum = 0;
    for (City *land : getCity())
        sum += land->get_monthly_city_penalty(year, month, category_name);
    return sum;
}
double Wilaya::get_yearly_wilaya_penalty(int year, const string &category_name)
{
    double sum = 0;
    for (City *land : getCity())
        sum += land->get_yearly_city_penalty(year, category_name);
    return sum;
}