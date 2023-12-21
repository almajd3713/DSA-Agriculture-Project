#include "land.hpp"

Land::Land()
{
  id = 0;
  reports = vector<AnnualReport *>();
}

Land::Land(int id, vector<AnnualReport *> reports, Farmer *farmer)
    : id{id}, reports{reports}, farmer{farmer} {}

Land::Land(const Land &rhs)
    : id{rhs.id}, reports{rhs.reports}, farmer{rhs.farmer} {}

Land::Land(Land &&rhs)
    : id{rhs.id}, reports{move(rhs.reports)}, farmer{move(rhs.farmer)} {}

Land::~Land()
{
  reports.clear();
}

int Land::getId() const
{
  return id;
}
void Land::setId(int new_id)
{
  id = new_id;
}

vector<AnnualReport *> Land::getReports() const
{
  return reports;
}
void Land::setReport(vector<AnnualReport *> new_report)
{
  reports = new_report;
}

Farmer *Land::getFarmer() const
{
  return farmer;
}
void Land::setFarmer(Farmer *new_farmer)
{
  farmer = new_farmer;
}

void Land::addYear(AnnualReport *rep)
{
  reports.push_back(rep);
  // TODO: Check if arr.length > 12
}

bool Land::operator<(const Land &rhs)
{
  return id < rhs.id;
}

bool Land::operator==(const Land &rhs)
{
  return id == rhs.id;
}

Land &Land::operator=(const Land &rhs)
{
  id = rhs.id;
  reports = rhs.reports;
  return *this;
}
// to be used in case we want to retrieve the report of a all years
ostream &operator<<(ostream &os, const Land &land)
{
  os << "Land ID: " << land.id << endl;
  os << "Farmer: " << land.farmer->getName() << endl;
  os << "Annual Reports: " << endl;
  for (auto year : land.reports)
  {
    os << *year << endl;
  }
  return os;
}

void Land:: printMonthlyReport(int year, int month)
{    
 
  AnnualReport* report = getAnnualReport(year);
  if(report != nullptr) {
    MonthlyReport* mReport = report->getMonthlyReport(month);
    if(mReport != nullptr) {
      cout << *mReport << endl;
      cout<< "the total_sales : " <<get_land_total_sales_per_month(year,month)<<" DA "<<endl;
      //water and electricity consumption
      cout<<"the total water consumption is : "<<get_monthly_water_consumption(year,month)<<" m3"<<endl;
      cout<<"the total electricity consumption is : "<<get_monthly_electricity_consumption(year,month)<<" Kwh"<<endl;  
    }
    else {
      cout << "No report for this month" << endl;
    }
  }
  else {
    cout << "No report for this year" << endl;
  }
}
double Land :: get_land_total_sales_per_year(int year){
  double Sum=0;
  AnnualReport * report =getAnnualReport(year);
  if(report == nullptr) 
   return 0;
  for( auto *month : report->getMonths()){
   Sum+= month->getProduction()->summrisedSales();
  }
  return Sum;

}

void Land::printAnnualReport(int year,int choice) {
  cout << "Land ID: " << id << endl;
 AnnualReport* report = getAnnualReport(year);
  if(report != nullptr) {
    cout << *report << endl;
    

  if(choice==1){
      cout << "Workers: " << endl;
    
  int number = 0;
  for (auto worker : report->getWorkers()) {
    cout << "Worker " << number << ": " << endl;
    cout << *worker << endl;
  }
  }
   cout<< "the total_sales : " <<get_land_total_sales_per_year(year) <<" DA "<<endl;
   //water and electricity consumption
    cout<<"the water consumption is : "<<get_yearly_water_consumption(year)<<" m3"<<endl;
    cout<<"the electricity consumption is : "<<get_yearly_electricity_consumption(year)<<" Kwh"<<endl;
  }
  else {
    cout << "No report for this year" << endl;
  }
 
}

AnnualReport* Land::getAnnualReport(int year) {
  for(AnnualReport* y: reports) {
    if(y->getYear() == year) return y;
  }
  return nullptr;
}

double Land::get_land_total_sales_per_month(int year,int month){
  double Sum=0;
  AnnualReport * report =getAnnualReport(year);
  if(report == nullptr) 
   return 0;
  MonthlyReport * mReport = report->getMonthlyReport(month);
  if(mReport == nullptr) 
   return 0;
  Sum= mReport->getProduction()->summrisedSales();
  return Sum;
}

  void Land::print_monthly_farmer_sales(int year,int month)
  {
     cout << "Farmer: " << farmer->getName() << endl;
    AnnualReport* report = getAnnualReport(year);
    if(report != nullptr) {
      MonthlyReport* mReport = report->getMonthlyReport(month);
      if(mReport != nullptr) {
        cout << "Monthly Sales: " << mReport->getProduction()->summrisedSales() << endl;
      }
      else {
        cout << "No report for this month" << endl;
      }
    }
    else {
      cout << "No report for this year" << endl;
    }
  }


    void Land::print_yearly_farmer_sales(int year)
    {
      cout << "Farmer: " << farmer->getName() << endl;
      AnnualReport* report = getAnnualReport(year);
      if(report != nullptr) {
     //iterrating over the months and print sales of each farmer
        double sum=0;
        for(auto month:report->getMonths()){
          sum+=month->getProduction()->summrisedSales();
        }
        cout << "Yearly Sales: " << sum <<" DA" <<endl;
      }
      else {
        cout << "No report for this year" << endl;
      }

    }

// functions to print the monthly  penalty of the land
void Land::print_Land_monthly_penalty(int year,int month,string category_name)
{
   //iterating over the years and then over the months
    AnnualReport * report =getAnnualReport(year);
    if(report == nullptr)
    {
      cout<<"No report for this year"<<endl;
      return;
    }
    MonthlyReport * mReport = report->getMonthlyReport(month);
    if(mReport == nullptr)
    {
      cout<<"No report for this month"<<endl;
      return;
    }
    cout<<"Farmer: "<<farmer->getName()<<endl;
    cout<<"Monthly Penalty of the category  "<<category_name<<"is :"<<mReport->getProduction()->get_Category_Penalty(category_name)<<" DA"<<endl;

} 
// functions to print the yearly  penalty of the land
void Land::print_Land_yearly_penalty(int year,string category_name)
{
    //iterating over the years and then over the months
      AnnualReport * report =getAnnualReport(year);
      if(report == nullptr)
      {
        cout<<"No report for this year"<<endl;
        return;
      }
      cout<<"Farmer: "<<farmer->getName()<<endl;
      double sum=0;
      for(auto month:report->getMonths()){
        sum+=month->getProduction()->get_Category_Penalty(category_name);
      }
      cout<<"Yearly Penalty of the category : "<<category_name<<" is : "<<sum<<" DA"<<endl;

}
// functions to print the monthly  water and elctricity consumption of the land
double Land::get_monthly_water_consumption(int year,int month){
  AnnualReport * report =getAnnualReport(year);
  if(report == nullptr)
  {
    return 0;
  }
  MonthlyReport * mReport = report->getMonthlyReport(month);
  if(mReport == nullptr)
  {
    return 0;
  }
  return mReport->getProduction()->getWaterConsumption();
}
double Land::get_monthly_electricity_consumption(int year,int month){
  AnnualReport * report =getAnnualReport(year);
  if(report == nullptr)
  {
    return 0;
  }
  MonthlyReport * mReport = report->getMonthlyReport(month);
  if(mReport == nullptr)
  {
    return 0;
  }
  return mReport->getProduction()->getElectricityConsumption();
}
// functions to print the yearly  water and elctricity consumption of the land
double Land::get_yearly_water_consumption(int year){
  AnnualReport * report =getAnnualReport(year);
  if(report == nullptr)
  {
    return 0;
  }
  double sum=0;
  for(auto month:report->getMonths()){
    sum+=month->getProduction()->getWaterConsumption();
  }
  return sum;
}
double Land::get_yearly_electricity_consumption(int year){
  AnnualReport * report =getAnnualReport(year);
  if(report == nullptr)
  {
    return 0;
  }
  double sum=0;
  for(auto month:report->getMonths()){
    sum+=month->getProduction()->getElectricityConsumption();
  }
  return sum;
}

//functions to print the the summarized report of the land
void Land::print_monthly_summarized_report(int year,int month){
  AnnualReport * report =getAnnualReport(year);
  if(report == nullptr)
  {
    cout<<"No report for this year"<<endl;
    return;
  }
  MonthlyReport * mReport = report->getMonthlyReport(month);
  if(mReport == nullptr)
  {
    cout<<"No report for this month"<<endl;
    return;
  }
  double sales=0;
  double water=0;
  double electricity=0;
  cout<<"Farmer: "<<farmer->getName()<<endl;
  cout<<"Monthly Summarized Report : "<<endl;
  electricity=get_monthly_electricity_consumption(year,month);
  water=get_monthly_water_consumption(year,month);
  sales=mReport->getProduction()->summrisedSales();
  cout<<"the total sales is : "<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
  cout<<"the total water consumption is : "<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
  cout<<"the total electricity consumption is : "<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
 
}

 void Land::print_yearly_summarized_report(int year){
  AnnualReport * report =getAnnualReport(year);
  if(report == nullptr)
  {
    cout<<"No report for this year"<<endl;
    return;
  }
  cout<<"Farmer: "<<farmer->getName()<<endl;
  cout<<"Yearly Summarized Report : "<<endl;
  double sales=0;
  double water=0;
  double electricity=0;
  sales=get_land_total_sales_per_year(year);
  water=get_yearly_water_consumption(year);
  electricity=get_yearly_electricity_consumption(year);
  cout<<"the total sales is : "<<(sales > 1000000 ? sales / 1000000 : sales > 1000 ? sales / 1000 : sales); 
  cout<<(sales > 1000000 ? "MDA" : sales > 1000 ? "KDA" : "DA")<<endl;
  cout<<"the total water consumption is : "<<(water > 1000000 ? water / 1000000 :  water);
  cout<<(water > 1000000 ? "dam^3" : "m^3")<<endl;
  cout<<"the total electricity consumption is : "<<(electricity > 1000000 ? electricity / 1000 : electricity);
  cout<<(electricity > 1000000 ? "Mwh" :  "kwh")<<endl;
 }
