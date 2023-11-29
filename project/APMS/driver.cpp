
#include "classes/DBMS.hpp"
using namespace std;


int main() {
  // Accessing the DBMS System, using the given database file
  DBMS data("data.json");
  // Read the file and store its data in the DBMS database
  data.read();
  // Cout the second city in the first wilaya, with intendation of two spaces per layer
  cout << setw(2) << data[0]["cities"][1] << endl;

  // Modifying the name of the second wilaya
  data[1]["name"] = "HabibiLand";
  cout << data[1]["name"];

  // erasing the second wilaya
  data.erase(0);

  // saving the changes into the data file
  data.write();
  
  return 0;
}