#pragma once
#ifndef APMSDSA
#define APMSDSA
#include <vector>
#include <type_traits>
#include "misc/AvlTree.hpp"
#include "misc/BinarySearchTree.h"
#include "misc/DBMS.hpp"
#include "wilaya.hpp"

// template<>
// class APMS<int> {
//   DBMS rawData;
//   BSTree<Wilaya>* data;

//   public:
//     APMS(string fpath);

//     void startup();
// };

// template<typename Comparable>
// class APMS {
//   // To force the use of Avl or BST
//   static_assert(
//     std::is_same<Comparable, AvlTree<Wilaya>>::value || std::is_same<Comparable, BSTree<Wilaya>>::value,
//     "Error: Cannot use any storage types other than BSTree or AvlTree"
//   );  

//   DBMS rawData;
//   Comparable wilayas;
//   Comparable cities;
//   Comparable areas;
//   Comparable lands;

//   public: 
//     APMS();
//     APMS(const string& fpath);
// };


class APMS {
  DBMS rawFile;
  BSTree<Wilaya> wilayas;
  // BSTree<City> cities;
  // BSTree<Area> areas;
  // BSTree<Land> lands;

public:
  // APMS() : rawFile{DBMS("")}, wilayas{BSTree<Wilaya>()}, cities{BSTree<City>()}, areas{BSTree<Area>()}, lands{BSTree<Land>()} {}
  APMS() {
    wilayas = BSTree<Wilaya>();
    // cities = BSTree<City>();
    // areas = BSTree<Area>();
    // lands = BSTree<Land>();
  }
  BSTree<Wilaya> getWilayas() const {
    return wilayas;
  }
   APMS(const string &fpath) : rawFile{DBMS{fpath}}, wilayas{BSTree<Wilaya>()}, cities{BSTree<City>()}, areas{BSTree<Area>()}, lands{BSTree<Land>()} {}
};






#endif