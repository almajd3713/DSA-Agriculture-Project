#include "land.hpp"

Land::Land() {
  id = 0;
  report = vector<AnnualReport*>();
}

Land::Land(int id, vector<AnnualReport*> report, const Farmer& farmer, const vector<Worker*>& workers)
: id{id}, report{report}, farmer{farmer}, workers{workers} {}

Land::Land(const Land& rhs)
: id{rhs.id}, report{rhs.report}, farmer{rhs.farmer}, workers{rhs.workers} {}

Land::Land(Land&& rhs)
: id{rhs.id}, report{move(rhs.report)}, farmer{move(rhs.farmer)}, workers{move(rhs.workers)} {}

Land::~Land() {
  report.clear();
}

int Land::getId() const {
  return id;
}
void Land::setId(int new_id) {
  id = new_id;
}

vector<AnnualReport*> Land::getReport() const {
  return report;
}
void Land::setReport(vector<AnnualReport*> new_report) {
  report = new_report;
}

Farmer Land::getFarmer() const {
  return farmer;
}
void Land::setFarmer(const Farmer& new_farmer) {
  farmer = new_farmer;
}

vector<Worker*> Land::getWorkers() const {
  return workers;
}
void Land::setWorkers(const vector<Worker*>& new_workers) {
  workers = new_workers;
}

void Land::addWorker(Worker* wkr) {
  workers.push_back(wkr);
}

//TODO This stuff aaaaahhhhhhhhhh
void Land::removeWorker(Worker* wkr) {

}



void Land::addYear(AnnualReport* rep) {
  report.push_back(rep);
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
  report = rhs.report;
  return *this;
}