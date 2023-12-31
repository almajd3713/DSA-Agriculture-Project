
#include "worker.hpp"
#ifndef COLOR_HPP
#include "../../lib/color.hpp"
#endif
#ifndef INCLUDESDSA
#include "../misc/includes.hpp"
#endif

Worker::Worker()
  : id{0}, name{""}, age{0}, gender{Gender::male} {}

Worker::Worker(int id, int age, const string& name, const Gender& gender)
  : id{id}, age{age}, name{name}, gender{gender} {}

Worker::Worker(const Worker& rhs)
  : id{rhs.id}, age{rhs.age}, name{rhs.name}, gender{gender} {}

Worker::Worker(Worker&& rhs)
  : id{rhs.id}, age{rhs.age}, name{move(rhs.name)}, gender{move(rhs.gender)} {}

Worker::~Worker() {
  
}

int Worker::getId() const {
  return id;
}
void Worker::setId(int new_id) {
  id = new_id;
}

int Worker::getAge() const {
  return age;
}
void Worker::setAge(int new_age) {
  age = new_age;
}


string Worker::getName() const {
  return name;
}
void Worker::setName(string new_name) {
  name = new_name;
}

Gender Worker::getGender() const {
  return gender;
}
void Worker::setGender(Gender new_gender) {
  gender = new_gender;
}

Worker& Worker::operator=(const Worker& rhs) {
  id = rhs.id;
  name = rhs.name;
  age = rhs.age;
  gender = rhs.gender;
  return *this;
}

bool Worker::operator==(const Worker& rhs) {
  return id == rhs.id;
}
bool Worker::operator<(const Worker& rhs) {
  return id < rhs.id;
}

Farmer::Farmer() : Worker() {};
Farmer::Farmer(int id, int age, string name, Gender gender, Land* land): Worker(id, age, name, gender), land{land} {};
Farmer::Farmer(const Farmer& rhs): Worker(rhs), land{land} {};
Farmer::Farmer(Farmer&& rhs): Worker(rhs), land{move(land)} {};
Farmer::~Farmer() {}

Farmer& Farmer::operator=(const Farmer& rhs) {
  id = rhs.id;
  name = rhs.name;
  age = rhs.age;
  gender = rhs.gender;
  land = rhs.land;
  return *this;
}

bool Farmer::operator==(const Farmer& rhs) {
  return id == rhs.id;
}

ostream& operator<<(ostream& out, const Worker& rhs)
{
  out << dye::light_purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
  out << "Worker Name: " << rhs.getName() << endl;
  out << "Worker ID: " << rhs.getId()  << endl;
  out<< "Age: " << rhs.getAge() << endl;
  out<<"Gender: " << (rhs.getGender() ? "Female" : "Male") << endl;
  out << dye::light_purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;

  return out;
}
ostream& operator<<(ostream & out,const Farmer& rhs)
{
  out << dye::light_purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
  out << "Worker Name: " << rhs.getName() << endl;
  out << "Worker ID: " << rhs.getId()  << endl;
  out<< "Age: " << rhs.getAge() << endl;
  out<< "Gender: " << (rhs.getGender() ? "Female" : "Male") << endl;
  out << dye::light_purple(stringRepeat("=", getConsoleWidth() / 2)) << endl;
  return out;
}

bool Farmer::operator<(const Farmer& rhs) {
  return id < rhs.id;
}

Land* Farmer::getLand() const {
  return land;
}
void Farmer::setLand(Land* new_land) {
  land = new_land;
}

void to_json(json& j, const Worker& worker) {
  j = {
    {"name", worker.getName()},
    {"id", worker.getId()},
    {"age", worker.getAge()},
    {"gender", worker.getGender()}
  };
}

void to_json(json& j, const Farmer& farmer) {
  j = {
    {"name", farmer.getName()},
    {"id", farmer.getId()},
    {"age", farmer.getAge()},
    {"gender", farmer.getGender()}
  };
}