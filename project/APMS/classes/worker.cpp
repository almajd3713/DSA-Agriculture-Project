
#include "worker.hpp"

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

Farmer::Farmer() : Worker() {};
Farmer::Farmer(int id, int age, string name, Gender gender): Worker(id, age, name, gender) {};
Farmer::Farmer(const Farmer& rhs): Worker(rhs) {};
Farmer::Farmer(Farmer&& rhs): Worker(rhs) {};
Farmer::~Farmer() {}