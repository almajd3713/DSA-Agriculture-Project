"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const Classes = __importStar(require("./util/classes"));
const RNG = __importStar(require("./util/rng"));
const fs_1 = __importDefault(require("fs"));
/**
 * Running the compiled generator.js file will generate a new set of data for the APMS to use.
 * You can modify the results later from the generated file or by the APMS terminal.
 *
 * Requires node to be installed. Just run `node generator.js`
 */
// Pre-defined products
const pdProducts = ["Cereal", "Fruit", "Vegetable", "Date", "Olive"];
const getProductSubset = () => {
    const size = RNG.rndNum(1, pdProducts.length - 1);
    let shuffled = pdProducts.slice(0), i = pdProducts.length, min = i - size, temp, index;
    while (i-- > min) {
        index = Math.floor((i + 1) * Math.random());
        temp = shuffled[index];
        shuffled[index] = shuffled[i];
        shuffled[i] = temp;
    }
    return shuffled.slice(min);
};
const BASE_YEAR = 2000, CURRENT_YEAR = 2023;
function workerGen() {
    let { name, gender } = RNG.getName();
    return new Classes.HumanWorker(name, RNG.rndNum(500000, 600000), gender);
}
function farmerGen() {
    let { name, gender } = RNG.getName();
    return new Classes.Farmer(name, RNG.rndNum(500000, 600000), gender);
}
function landDataGen() {
    let products = getProductSubset().map(prod => new Classes.Product(prod, RNG.rndNum(30, 200), RNG.rndNum(100, 5000)));
    let land = new Classes.LandData(products, RNG.rndNum(0, 2), RNG.rndNum(0, 10000), RNG.rndNum(0, 10000));
    return land;
}
function monthlyRepGen(month) {
    return new Classes.MonthlyReport(month + 1, landDataGen());
}
function yearlyRepGen(year) {
    let months = new Array(12).fill(1).map((_, i) => monthlyRepGen(i));
    return new Classes.AnnualReport(year, months);
}
function landGen() {
    let workers = new Array(RNG.rndNum(0, 20)).fill(1).map(_ => workerGen());
    let landFormYear = RNG.rndNum(BASE_YEAR, CURRENT_YEAR);
    let rep = new Array(CURRENT_YEAR - landFormYear + 1).fill(1).map((_, i) => yearlyRepGen(landFormYear + i));
    return new Classes.Land(RNG.rndNum(200000, 300000), farmerGen(), workers, rep);
}
function areaGen(area) {
    let lands = new Array(3).fill(1).map(_ => landGen());
    return new Classes.Area(area, lands);
}
function cityGen(city) {
    let areas = city[1].map(area => areaGen(area));
    return new Classes.City(city[0], areas);
}
function wilayaGen(name) {
    let wilCities = RNG.getWilaya(name);
    let cities = Object.entries(wilCities).map(entry => cityGen(entry));
    let wilaya = new Classes.Wilaya(name, cities);
    return wilaya;
}
function jsonGen() {
    let tissemsilt = wilayaGen(RNG.WILAYAS[0]);
    return tissemsilt;
}
console.log("Generating and writing started");
fs_1.default.writeFileSync("data.json", JSON.stringify(jsonGen()));
console.log("Done!");
