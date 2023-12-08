
#include "land.hpp"

Land::Land() {
  id = 0;
  report = new AnnualReport*[12];
}

Land::Land(int id, AnnualReport** report)
: id{id}, report{report} {}

Land::Land(const Land& rhs)
: id{rhs.id}, report{rhs.report} {}

Land::Land(Land&& rhs)
: id{rhs.id}, report{move(rhs.report)} {}

Land::~Land() {
  delete report;
}

int Land::getId() const {
  return id;
}
void Land::setId(int new_id) {
  id = new_id;
}

AnnualReport** Land::getReport() const {
  return report;
}
void Land::setReport(AnnualReport** new_report) {
  report = new_report;
}

void Land::addYear(const AnnualReport& rep) {
  delete[] report;
}