#include "year.hpp"
#include <iostream>
AnnualReport::AnnualReport() {
  year = 0;
  months = vector<MonthlyReport*>();
}

AnnualReport::AnnualReport(int year, vector<MonthlyReport*> months)
: year{year}, months{months} {}

AnnualReport::AnnualReport(const AnnualReport& rhs)
: year{rhs.year}, months{rhs.months} {}

AnnualReport::AnnualReport(AnnualReport&& rhs)
: year{rhs.year}, months{move(rhs.months)} {}

AnnualReport::~AnnualReport() {
  months.clear();
}

int AnnualReport::getYear() const {
  return year;
}
void AnnualReport::setYear(int new_year) {
  year = new_year;
}
vector<MonthlyReport*> AnnualReport::getMonths() const {
  return months;
}
void AnnualReport::setMonths(vector<MonthlyReport*> new_months) {
  months = new_months;
}

vector<Worker*> AnnualReport::getWorkers() const {
  return workers;
}
void AnnualReport::setWorkers(const vector<Worker*>& new_workers) {
  workers = new_workers;
}

void AnnualReport::addWorker(Worker* wkr) {
  workers.push_back(wkr);
}
void AnnualReport::removeWorker(Worker* wkr) {
  
}


void AnnualReport::addMonth(MonthlyReport* rhs) {
  months.push_back(rhs);
};
// void AnnualReport::removeMonth(MonthlyReport* rhs) {
//   months.erase(remove(months.begin(), months.end(), rhs));
// };
// void AnnualReport::removeMonth(int) {
  
// };
ostream& operator<<(ostream& os, const AnnualReport& report) {
  os << "Year: " << report.year << endl;
  os << "Monthly Reports: " << endl;
  for (auto month : report.months) {
    os << *month << endl;
  }
  os << "Workers: " << endl;
  int number = 0;
  for (auto worker : report.workers) {
    os << "Worker " << number << ": " << endl;
    os << *worker << endl;
  }
  return os;
}

MonthlyReport* AnnualReport::getMonthlyReport(int month) {
  if(months.size() < 12) {
    if(months[0]->getMonth() > month) return nullptr;
    else return months[12 - month - 1];
  }
  else return months[month - 1];
}