
#include "month.hpp"


MonthlyReport::MonthlyReport() {
  month = 0;
  data = nullptr;
}

MonthlyReport::MonthlyReport(int month, LandData* data)
  : month{month}, data{data} {}

MonthlyReport::MonthlyReport(const MonthlyReport& rhs)
  : month{rhs.month}, data{rhs.data} {}

MonthlyReport::MonthlyReport(MonthlyReport&& rhs)
  : month{rhs.month}, data{move(rhs.data)} {}

MonthlyReport::~MonthlyReport() {}



int MonthlyReport::getMonth() const {
  return month;
}
void MonthlyReport::setMonth(int new_month) {
  month = new_month;
}

LandData* MonthlyReport::getLandData() const {
  return data;
}
void MonthlyReport::setLandData(LandData* new_data) {
  data = new_data;
}

ostream& operator<<(ostream& os, const MonthlyReport& report) {
  os << "Month: " << report.month << endl;
  os << "Land Data: " << endl;
  os << *(report.data) << endl;
  return os;
}