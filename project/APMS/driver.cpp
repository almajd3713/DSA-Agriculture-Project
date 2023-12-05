
#include "misc/DBMS.hpp"
using namespace std;


int main() {
  // Accessing the DBMS System, using the given database file
  DBMS data("./data.json");
  // Read the file and store its data in the DBMS database
  data.read();
  cout << "AYE" << endl;
  // Cout the second city in the first wilaya, with intendation of two spaces per layer

  // Modifying the name of the second wilaya
  // for(auto& [key, val] : data.getFileData()[0].items()) {
  //   cout << key << endl;
  // }

  // erasing the second wilaya

  // saving the changes into the data file
  
  return 0;
}