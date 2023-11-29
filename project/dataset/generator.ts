
import * as Classes from "./util/classes"
import * as RNG from "./util/rng"
import * as Types from "./util/types"
import { writeFileSync } from "fs"
/**
 * Running the compiled generator.js file will generate a new set of data for the APMS to use.
 * You can modify the results later from the generated file or by the APMS terminal.
 * 
 * Requires node to be installed. Just run `node generator.js`
 */

// Pre-defined products
const pdProducts = ["Cereal", "Fruit", "Vegetable", "Date", "Olive"]
const getProductSubset = () => {
  const size = RNG.rndNum(1, pdProducts.length - 1)
  let shuffled = pdProducts.slice(0), i = pdProducts.length, min = i - size, temp, index;
  while (i-- > min) {
    index = Math.floor((i + 1) * Math.random());
    temp = shuffled[index];
    shuffled[index] = shuffled[i];
    shuffled[i] = temp;
  }
  return shuffled.slice(min);
}
const BASE_YEAR = 2000, CURRENT_YEAR = 2023

function workerGen(): Types.HumanWorker {
  let {name, gender} = RNG.getName()
  return new Classes.HumanWorker(name, RNG.rndNum(500000, 600000), gender)
}
function farmerGen(): Types.Farmer {
  let { name, gender } = RNG.getName()
  return new Classes.Farmer(name, RNG.rndNum(500000, 600000), gender)
}

function landDataGen(): Types.LandData {
  let products = getProductSubset().map(prod => new Classes.Product(prod,RNG.rndNum(30, 200), RNG.rndNum(100, 5000)))
  let land = new Classes.LandData(products, RNG.rndNum(0, 2), RNG.rndNum(0, 10000), RNG.rndNum(0, 10000))
  return land
}
function monthlyRepGen(month: number): Types.MonthlyReport {
  return new Classes.MonthlyReport(month + 1, landDataGen())
}
function yearlyRepGen(year: number): Types.AnnualReport {
  let months = new Array(12).fill(1).map((_, i) => monthlyRepGen(i))
  return new Classes.AnnualReport(year, months)
}
function landGen(): Types.Land {
  let workers = new Array(RNG.rndNum(0, 20)).fill(1).map(_ => workerGen())
  let landFormYear = RNG.rndNum(BASE_YEAR, CURRENT_YEAR)
  let rep = new Array(CURRENT_YEAR - landFormYear + 1).fill(1).map((_, i) => yearlyRepGen(landFormYear + i))
  return new Classes.Land(RNG.rndNum(200000, 300000), farmerGen(), workers, rep)
}
function areaGen(area: string): Types.Area {
  let lands = new Array(3).fill(1).map(_ => landGen())
  return new Classes.Area(area, lands)
}
function cityGen(city: [string, string[]]): Types.City {
  let areas = city[1].map(area => areaGen(area))
  return new Classes.City(city[0], areas)
}
function wilayaGen(name: string): Types.Wilaya {
  let wilCities = RNG.getWilaya(name)
  let cities = Object.entries(wilCities).map(entry => cityGen(entry))

  let wilaya = new Classes.Wilaya(name, cities)
  return wilaya
}

function jsonGen() {
  return Object.keys(RNG.countryTemplate).map(wil => wilayaGen(wil));
}


console.log("Generating and writing started")
let database = jsonGen()
writeFileSync("data.json", JSON.stringify(database))
console.log("Done!")