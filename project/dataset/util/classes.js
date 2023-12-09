"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.SalesReport = exports.Product = exports.LandData = exports.MonthlyReport = exports.AnnualReport = exports.Farmer = exports.HumanWorker = exports.Land = exports.Area = exports.City = exports.Wilaya = void 0;
class Wilaya {
    name;
    id;
    cities;
    constructor(name, id, cities) {
        this.cities = cities;
        this.name = name;
        this.id = id;
    }
}
exports.Wilaya = Wilaya;
class City {
    id;
    name;
    areas;
    constructor(id, name, areas) {
        this.id = id;
        this.areas = areas;
        this.name = name;
    }
}
exports.City = City;
class Area {
    id;
    name;
    lands;
    constructor(id, name, lands) {
        this.id = id;
        this.lands = lands;
        this.name = name;
    }
}
exports.Area = Area;
class Land {
    id;
    farmer;
    report;
    constructor(id, farmer, report) {
        this.id = id;
        this.farmer = farmer;
        this.report = report;
    }
}
exports.Land = Land;
class HumanWorker {
    name;
    id;
    age;
    gender;
    constructor(name, id, age, gender) {
        this.name = name;
        this.id = id;
        this.gender = gender;
        this.age = age;
    }
}
exports.HumanWorker = HumanWorker;
class Farmer extends HumanWorker {
    constructor(name, id, age, gender) {
        super(name, id, age, gender);
    }
}
exports.Farmer = Farmer;
class AnnualReport {
    year;
    months;
    workers;
    constructor(year, months, workers) {
        this.year = year;
        this.months = months;
        this.workers = workers;
    }
}
exports.AnnualReport = AnnualReport;
class MonthlyReport {
    month;
    data;
    constructor(month, data) {
        this.month = month;
        this.data = data;
    }
}
exports.MonthlyReport = MonthlyReport;
class LandData {
    products;
    pesticideSeverity;
    waterConsumption;
    electricityConsumption;
    constructor(products = [], pestSev = 0, waterCon, electCon) {
        this.products = products;
        this.pesticideSeverity = pestSev;
        this.waterConsumption = waterCon;
        this.electricityConsumption = electCon;
    }
}
exports.LandData = LandData;
class Product {
    name;
    basePrice;
    production;
    pesticideSeverity;
    constructor(name, basePrice, production, pestSeverity) {
        this.name = name;
        this.basePrice = basePrice;
        this.production = production;
        this.pesticideSeverity = pestSeverity;
    }
}
exports.Product = Product;
class SalesReport {
    products;
    constructor(products) {
        this.products = products;
    }
}
exports.SalesReport = SalesReport;
