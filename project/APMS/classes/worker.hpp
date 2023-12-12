#pragma once
#ifndef WORKERDSA
#define WORKERDSA
#include <string>
#include "enums.hpp"
using namespace std;


class Worker {
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
};

class Farmer : public Worker {
  
  public:
    Farmer();
    Farmer(int, int, string, Gender);
    Farmer(const Farmer&);
    Farmer(Farmer&&);
    ~Farmer();

    

    Farmer& operator=(const Farmer&);
    bool operator==(const Farmer&);
    bool operator<(const Farmer&);
};


#endif