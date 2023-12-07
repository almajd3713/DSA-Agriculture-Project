
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
    Worker(int i, int a, string n, Gender g)
      : id{i}, age{a}, name{n}, gender{g} {};
  
    int getId() const;
    void setId(int);
    string getName() const;
    void setName(string);
    Gender getGender() const;
    void setGender(Gender);
};

class Farmer : public Worker {
  public:
    Farmer(int i, int a, string n, Gender g): Worker(i, a, n, g) {}
};






#endif