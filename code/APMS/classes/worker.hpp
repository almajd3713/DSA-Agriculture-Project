#pragma once
#ifndef WORKERDSA
#define WORKERDSA
// #include <string>
#include "enums.hpp"
#include "../misc/includes.hpp"
// #include <iomanip>
// #include <iostream>


class Land;
class Worker {
  friend ostream& operator<<(ostream& out, const Worker&);
  protected:
    int id;
    int age;
    string name;
    Gender gender;

  public:
    Worker();
    Worker(int, int, const string&, const Gender&);
    Worker(const Worker&);
    Worker(Worker&&);
    ~Worker();

    int getId() const;
    void setId(int);
    int getAge() const;
    void setAge(int);

    
    string getName() const;
    void setName(string);
    Gender getGender() const;
    void setGender(Gender);

    Worker& operator=(const Worker&);
    bool operator==(const Worker&);
    bool operator<(const Worker&);

    friend void to_json(json&, const Worker&);
};

class Farmer : public Worker {
  friend ostream& operator<<(ostream&, const Farmer&);
    Land* land;


  public:
    Farmer();
    Farmer(int, int, string, Gender, Land*);
    Farmer(const Farmer &);
    Farmer(Farmer &&);
    ~Farmer();

    Farmer &operator=(const Farmer &);
    bool operator==(const Farmer &);
    bool operator<(const Farmer &);
    Land *getLand() const;
    void setLand(Land*);

    friend void to_json(json&, const Farmer&);

};


#endif