
#include "month.hpp"

string monthsStr[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

MonthlyReport::MonthlyReport() {
  month = 0;
  data = nullptr;
}

MonthlyReport::MonthlyReport(int month, Production* data)
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

Production* MonthlyReport::getProduction() const {
  return data;
}
void MonthlyReport::setProduction(Production* new_data) {
  data = new_data;
}

ostream& operator<<(ostream& os, const MonthlyReport& report) {
  os << dye::light_red(stringRepeat("=", getConsoleWidth() / 2)) << endl;
  os << "Month: " << monthsStr[report.month - 1] << endl;
  os << *report.data;
  os << dye::light_red(stringRepeat("=", getConsoleWidth() / 2)) << endl;
  return os;
}

void to_json(json& j, const MonthlyReport& report) {
  j = json {
    {"month", report.getMonth()},
    {"data", (json)*report.getProduction()}
  };
}