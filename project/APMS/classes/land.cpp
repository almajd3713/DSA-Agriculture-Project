#include "land.hpp"

Land::Land() {
  id = 0;
  reports = vector<AnnualReport*>();
}

Land::Land(int id, vector<AnnualReport*> reports, Farmer* farmer)
: id{id}, reports{reports}, farmer{farmer} {}

Land::Land(const Land& rhs)
: id{rhs.id}, reports{rhs.reports}, farmer{rhs.farmer} {}

Land::Land(Land&& rhs)
: id{rhs.id}, reports{move(rhs.reports)}, farmer{move(rhs.farmer)} {}

Land::~Land() {
  reports.clear();
}

int Land::getId() const {
  return id;
}
void Land::setId(int new_id) {
  id = new_id;
}

vector<AnnualReport*> Land::getReports() const {
  return reports;
}
void Land::setReport(vector<AnnualReport*> new_report) {
  reports = new_report;
}

Farmer* Land::getFarmer() const {
  return farmer;
}
void Land::setFarmer(Farmer* new_farmer) {
  farmer = new_farmer;
}

// vector<Worker*> Land::getWorkers() const {
//   return workers;
// }
// void Land::setWorkers(const vector<Worker*>& new_workers) {
//   workers = new_workers;
// }

// void Land::addWorker(Worker* wkr) {
//   workers.push_back(wkr);
// }

// //TODO This stuff aaaaahhhhhhhhhh
// void Land::removeWorker(Worker* wkr) {

// }



void Land::addYear(AnnualReport* rep) {
  reports.push_back(rep);
  //TODO: Check if arr.length > 12
}

bool Land::operator<(const Land &rhs) {
  return id < rhs.id;
}

bool Land::operator==(const Land& rhs) {
  return id == rhs.id;
}

Land& Land::operator=(const Land& rhs) {
  id = rhs.id;
  reports = rhs.reports;
  return *this;
}

ostream& operator<<(ostream& os, const Land& land) {
  os << "Land ID: " << land.id << endl;
  os << "Farmer: " << land.farmer->getName() << endl;
  os << "Annual Reports: " << endl;
  for (auto year : land.reports) {
    os << *year << endl;
  }
  return os;
}

void Land::printAnualReport(int year) {
    cout << "Land ID: " << id << endl;
  for (auto report : reports) {
    if (report->getYear() == year) {
      
      cout << *report << endl;
    }
  }
}