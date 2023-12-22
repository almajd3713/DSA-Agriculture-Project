
#ifndef LANDDATADSA
#define LANDDATADSA
#include "product_category.hpp"

class Production {
friend ostream& operator<<(ostream&, const Production&);//left for redwan to do it (unordered_map issues :( 
  double waterConsumption;
  double electricityConsumption;
  unordered_map<string, ProductCategory*> categories;

  public:
    Production();
    Production(double, double, const unordered_map<string, ProductCategory*>&);
    Production(const Production&);
    Production(Production&&);
    ~Production();
    
    double getWaterConsumption() const;
    void setWaterConsumption(double);
    double getElectricityConsumption() const;
    void setElectricityConsumption(double);
    unordered_map<string, ProductCategory*> getCategories() const;
    void setCategories(unordered_map<string, ProductCategory*>);

    ProductCategory* getCategory(string cat);
    
    void addProduct(const string&, double, double, PesticideSeverity);
    void addProduct(ProductCategory*);

    Production& operator=(const Production& rhs) {
      electricityConsumption = rhs.electricityConsumption;
      waterConsumption = rhs.waterConsumption;
      categories = rhs.categories;
      return *this;
    }

    friend ostream& operator<<(ostream&, const Production&);

  // left foe redwan to deal with ordered map for summrised sales
  friend void to_json(json&, const Production&);

   //left foe redwan to deal with ordered map for summrised sales
  double summarizedSales();

  // left for redwan to deal with ordered map for summrised sales
  double get_Category_Penalty(const string& );
};










#endif