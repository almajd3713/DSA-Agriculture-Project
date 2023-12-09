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
const countryTemplate_1 = __importDefault(require("./util/countryTemplate"));
const RNG = __importStar(require("./util/rng"));
const fs_1 = require("fs");
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
const args = process.argv.slice(2);
const BASE_YEAR = Number(args[0]), CURRENT_YEAR = Number(args[1]), WIL_COUNT = Number([args[2]]);
function workerGen() {
    let { name, gender } = RNG.getName();
    return new Classes.HumanWorker(name, RNG.rndNum(500000, 600000), RNG.rndNum(0, 1), gender);
}
function farmerGen() {
    let { name, gender } = RNG.getName();
    return new Classes.Farmer(name, RNG.rndNum(500000, 600000), RNG.rndNum(0, 1), gender);
}
function landDataGen() {
    let products = getProductSubset().map(prod => new Classes.Product(prod, RNG.rndNum(30, 200), RNG.rndNum(100, 5000), RNG.rndNum(0, 1)));
    let land = new Classes.LandData(products, RNG.rndNum(0, 2), RNG.rndNum(0, 10000), RNG.rndNum(0, 10000));
    return land;
}
function monthlyRepGen(month) {
    return new Classes.MonthlyReport(month + 1, landDataGen());
}
function yearlyRepGen(year, startingMonth = 0) {
    let workers = new Array(RNG.rndNum(0, 20)).fill(1).map(_ => workerGen());
    let months = new Array(12 - startingMonth).fill(1).map((_, i) => monthlyRepGen(i + startingMonth));
    return new Classes.AnnualReport(year, months, workers);
}
function landGen() {
    let landFormYear = RNG.rndNum(BASE_YEAR, CURRENT_YEAR);
    let rep = new Array(CURRENT_YEAR - landFormYear + 1).fill(1).map((_, i) => {
        if (i)
            return yearlyRepGen(landFormYear + i, 0);
        else
            return yearlyRepGen(landFormYear + i, RNG.rndNum(1, 12));
    });
    return new Classes.Land(RNG.rndNum(200000, 300000), farmerGen(), rep);
}
function areaGen(area) {
    let lands = new Array(3).fill(1).map(_ => landGen());
    return new Classes.Area(RNG.rndNum(3000000, 4000000), area, lands);
}
function cityGen(city) {
    let areas = city[1].map(area => areaGen(area));
    return new Classes.City(RNG.rndNum(2000000, 3000000), city[0], areas);
}
function wilayaGen(name) {
    let wil = RNG.getWilaya(name);
    let id = wil.id;
    let cities = Object.entries(wil.cities).map(entry => cityGen(entry));
    let wilaya = new Classes.Wilaya(name, id, cities);
    return wilaya;
}
function jsonGen(count) {
    console.log(count);
    return RNG.shuffle(Object.keys(countryTemplate_1.default)).slice(0, count).map(wil => {
        return wilayaGen(wil);
    });
}
console.log("Generating and writing started UwU");
let database = jsonGen(WIL_COUNT);
// console.log(database)
(0, fs_1.writeFileSync)("data.json", JSON.stringify(database));
console.log("Done!");
