"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.SalesReport = exports.Product = exports.LandData = exports.MonthlyReport = exports.AnnualReport = exports.Farmer = exports.HumanWorker = exports.Land = exports.Area = exports.City = exports.Wilaya = void 0;
class Wilaya {
    name;
    cities;
    constructor(name, cities) {
        this.cities = cities;
        this.name = name;
    }
}
exports.Wilaya = Wilaya;
class City {
    name;
    areas;
    constructor(name, areas) {
        this.areas = areas;
        this.name = name;
    }
}
exports.City = City;
class Area {
    name;
    lands;
    constructor(name, lands) {
        this.lands = lands;
        this.name = name;
    }
}
exports.Area = Area;
class Land {
    id;
    farmer;
    workers;
    report;
    constructor(id, farmer, workers, report) {
        this.id = id;
        this.farmer = farmer;
        this.workers = workers;
        this.report = report;
    }
}
exports.Land = Land;
class HumanWorker {
    id;
    gender;
    constructor(id, gender) {
        this.id = id;
        this.gender = gender;
    }
}
exports.HumanWorker = HumanWorker;
class Farmer extends HumanWorker {
    constructor(id, gender) {
        super(id, gender);
    }
}
exports.Farmer = Farmer;
class AnnualReport {
    year;
    months;
    constructor(year, months) {
        this.year = year;
        this.months = months;
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
    constructor(name, basePrice, production) {
        this.name = name;
        this.basePrice = basePrice;
        this.production = production;
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
