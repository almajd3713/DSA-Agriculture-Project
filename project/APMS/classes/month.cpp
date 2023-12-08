
#include "month.hpp"


MonthlyReport::MonthlyReport() {
  month = 0;
  data = LandData();
}

MonthlyReport::MonthlyReport(int month, const LandData& data)
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

LandData MonthlyReport::getLandData() const {
  return data;
}
void MonthlyReport::setLandData(const LandData& new_data) {
  data = new_data;
}
