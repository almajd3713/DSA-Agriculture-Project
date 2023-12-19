
#ifndef JSONREADERDSA
#define JSONREADERDSA

#include "includes.hpp"
#include "./../../lib/json.hpp"
#include "exceptions.hpp"


class DBMS {
  string filePath;
  ifstream fileReader;
  ofstream fileWriter;
  json fileData;
  bool isModified;

  bool fileExists() {
    // cout <<  << endl;
    return exists(filePath);
  }

  public:
    DBMS(): filePath{"data.json"}, isModified{false} {}
    DBMS(string fpath) : filePath{fpath}, isModified{false} {}
    DBMS(const DBMS& f) : filePath{f.filePath}, fileData{f.fileData}, isModified{false} {}
    DBMS(DBMS&& f) : filePath{move(f.filePath)}, fileReader{move(f.fileReader)}, fileWriter{move(f.fileWriter)}, fileData{move(f.fileData)}, isModified{f.isModified} {}

    friend ostream& operator<< (ostream&, const DBMS&);

    json& getFileData() {
      return fileData;
    }

    void read() {
      cout << "Starting data read..." << endl;
      if(!fileExists()) throw fileDoesNotExistException();
      fileReader.open(filePath);
      if(!(fileReader.is_open())) {
        throw fileCouldNotBeOpenedException();
      }
      fileData = json::parse(fileReader);
      fileReader.close();
      cout << "Data has been read" << endl;
    }
    void write(json &j, string new_path)
    {
      fileWriter.open(new_path);
      if(!fileWriter.is_open())
        throw fileCouldNotBeOpenedException();
      fileData = j;
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
        cout << "Program Finished" << endl;
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

    DBMS& operator=(const DBMS&);

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

DBMS& DBMS::operator=(const DBMS& rhs) {
  fileData = rhs.fileData;
  filePath = rhs.fileData;
  isModified = rhs.isModified;
  return *this;
} 


ostream& operator<<(ostream& os, const DBMS& dbms) {
  os << dbms.fileData << endl; 
  return os;
}





#endif