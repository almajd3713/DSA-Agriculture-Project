#pragma once

#ifndef APMSDSA
#define APMSDSA
#include <vector>
#include <type_traits>
#include "misc/AvlTree.hpp"
#include "misc/DBMS.hpp"
#include "classes/wilaya.hpp"




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
  AvlTree<Wilaya> wilayas;
  AvlTree<City> cities;
  AvlTree<Area> areas;
  AvlTree<Land> lands;

public:
  APMS() : rawFile{DBMS("")}, wilayas{AvlTree<Wilaya>()}, cities{AvlTree<City>()}, areas{AvlTree<Area>()}, lands{AvlTree<Land>()} {}
  APMS(const string &fpath) : rawFile{DBMS{fpath}}, wilayas{AvlTree<Wilaya>()}, cities{AvlTree<City>()}, areas{AvlTree<Area>()}, lands{AvlTree<Land>()} {}
};






#endif