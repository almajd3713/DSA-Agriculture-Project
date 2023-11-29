
#include "classes/DBMS.hpp"
using namespace std;


int main() {
  DBMS file("./../dataset/data.json");
  file.read();
  file.erase("submods");
  cout << setw(2) << file << endl;

  return 0;
}