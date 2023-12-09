#include "year.hpp"


AnnualReport::AnnualReport() {
  year = 0;
  months = nullptr;
}

AnnualReport::AnnualReport(int year, MonthlyReport* months)
: year{year}, months{months} {}

AnnualReport::AnnualReport(const AnnualReport& rhs)
: year{rhs.year}, months{rhs.months} {}

AnnualReport::AnnualReport(AnnualReport&& rhs)
: year{rhs.year}, months{move(rhs.months)} {}

AnnualReport::~AnnualReport() {
  delete months;
}

int AnnualReport::getYear() const {
  return year;
}
void AnnualReport::setYear(int new_year) {
  year = new_year;
}
MonthlyReport* AnnualReport::getMonthlyReport() const {
  return months;
}
void AnnualReport::setMonthlyReport(MonthlyReport* new_months) {
  months = new_months;
}

