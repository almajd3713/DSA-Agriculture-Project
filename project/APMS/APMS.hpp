
#ifndef APMSDSA
#define APMSDSA
#include <vector>
#include "misc/BST.hpp"
#include "misc/DBMS.hpp"
#include "../classes/wilaya.hpp"




class APMS {
  DBMS rawData;
  BSTree<Wilaya>* data;

  public:
    APMS(string fpath, string storeMode): rawData{fpath} {
      if(storeMode == "avl") 
        data = new AVLTree<Wilaya>();
      else
        data = new BSTree<Wilaya>();
    }

    void startup() {
      
    }
};










#endif