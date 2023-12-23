#include "default_config.hpp"


int main() {

  // 1 - Replace the value of dataPath with the ABSOLUTE path 
  // (starting with C:/..) with the path of data.json
  string dataPath = "data.json";

  // To launch the program, comment out testProgram
  // To test the speed of creation/deletion of BST/AVL
  // based APMS, uncomment testProgram and comment startProgram. 
  // Change the second parameter to your preferred iterations. 
  // Higher values mean more time, but more accurate results

  startProgram(dataPath);
  // testProgram(dataPath, 20);


  return 0;
}






