
#ifndef JSONREADERDSA
#define JSONREADERDSA

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "./../../lib/json.hpp"
using json = nlohmann::json;
using namespace std;

#include "exceptions.hpp"


class DBMS {
  string filePath;
  ifstream fileReader;
  ofstream fileWriter;
  json fileData;
  bool isModified;

  bool fileExists() {
    return filesystem::exists(filePath);
  }

  public:
    DBMS(string fpath = "") : filePath{fpath}, isModified{false} {}
    DBMS(const DBMS& f) : filePath{f.filePath}, fileData{f.fileData}, isModified{false} {}
    DBMS(DBMS&& f) : filePath{move(f.filePath)}, fileReader{move(f.fileReader)}, fileWriter{move(f.fileWriter)}, fileData{move(f.fileData)}, isModified{f.isModified} {}

    friend ostream& operator<< (ostream&, const DBMS&);

    void read() {
      if(!fileExists()) throw fileDoesNotExistException();
      fileReader.open(filePath);
      if(!(fileReader.is_open())) {
        throw fileCouldNotBeOpenedException();
      }
      fileData = json::parse(fileReader);
      fileReader.close();
    }
    void write() {
      fileWriter.open(filePath);
      if(!fileWriter.is_open())
        throw fileCouldNotBeOpenedException();
      fileWriter << fileData.dump();
      fileWriter.close();
    }
    
    json& operator[](const string& accessor) {
      if(!fileExists()) throw fileDoesNotExistException();
      return fileData[accessor];
    }
    json& operator[](int accessor) {
      if(!fileExists()) throw fileDoesNotExistException();
      return fileData.at(accessor);
    }

    // DEBUG
    struct debug {
      static string type(const json& obj);
    };

    ~DBMS() {
      if(fileExists()) {
        fileReader.close();
        fileWriter.close();
      }
    }

    void erase(const string& item) {
      if(!fileExists()) throw fileDoesNotExistException();
      fileData.erase(item);
    }
    void erase(const int& item) {
      if(!fileExists()) throw fileDoesNotExistException();
      fileData.erase(item);
    }

};

string DBMS::debug::type(const json& obj)  {
  return
    obj.is_binary() ? "Binary" :
    obj.is_string() ? "String" :
    obj.is_array() ? "Array" :
    obj.is_boolean() ? "Boolean" :
    obj.is_number() ? "Number" :
    obj.is_object() ? "Object" :
    obj.is_null() ? "Null" :
    "Couldn't identify the type";
}


ostream& operator<<(ostream& os, const DBMS& dbms) {
  os << dbms.fileData << endl; 
  return os;
}





#endif