
import * as Classes from "./util/classes"
import countryTemplate from "./util/countryTemplate"
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
const args = process.argv.slice(2)
const BASE_YEAR = Number(args[0]), CURRENT_YEAR = Number(args[1]), WIL_COUNT = Number([args[2]])

function workerGen(): Types.HumanWorker {
  let {name, gender} = RNG.getName()
  return new Classes.HumanWorker(name, RNG.rndNum(500000, 600000), RNG.rndNum(18, 40),  gender)
}
function farmerGen(): Types.Farmer {
  let { name, gender } = RNG.getName()
  return new Classes.Farmer(name, RNG.rndNum(500000, 600000), RNG.rndNum(18, 65), gender)
}

function landDataGen(): Types.LandData {
  let products = getProductSubset().map(prod => new Classes.Product(prod,RNG.rndNum(30, 200), RNG.rndNum(100, 5000), RNG.rndNum(0, 1)))
  let land = new Classes.LandData(products, (1000 * products.length) + RNG.rndNum(100 * products.length, 1000 * products.length), RNG.rndNum(1000 * products.length, 7000 * products.length))
  return land
}
function monthlyRepGen(month: number): Types.MonthlyReport {
  return new Classes.MonthlyReport(month + 1, landDataGen())
}
function yearlyRepGen(year: number, startingMonth: number, prevWorkers?: Classes.HumanWorker[]): Types.AnnualReport {
  let workers = (prevWorkers ? prevWorkers : new Array(RNG.rndNum(0, 20)).fill(1)).map((_, i) => {
    if(prevWorkers) {
      prevWorkers[i].age++
      return prevWorkers[i]
    }
    else return workerGen()
  })
  let months = new Array(12 - startingMonth).fill(1).map((_, i) => monthlyRepGen(i + startingMonth))
  return new Classes.AnnualReport(year, months, workers)
}
function landGen(id: number): Types.Land {
  id = (id * 100) + RNG.rndNum(1, 99)
  let landFormYear = RNG.rndNum(BASE_YEAR, CURRENT_YEAR)
  let rep = new Array(CURRENT_YEAR - landFormYear + 1).fill(1)
  rep.forEach((_, i, arr) => {
    if(i) arr[i] = yearlyRepGen(landFormYear + i, 0, arr[i - 1].workers)
    else arr[i] = yearlyRepGen(landFormYear + i, RNG.rndNum(1, 11))
  })
  return new Classes.Land(id, farmerGen(), rep)
}
function areaGen(id: number, area: string): Types.Area {
  id = (id * 100) + RNG.rndNum(1, 99)
  let lands = new Array(3).fill(1).map(_ => landGen(id))
  return new Classes.Area(id, area, lands)
}
function cityGen(id: number, city: [string, string[]]): Types.City {
  id = (id * 100) + RNG.rndNum(1, 99)
  let areas = city[1].map(area => areaGen(id, area))
  return new Classes.City(id, city[0], areas)
}
function wilayaGen(name: string): Types.Wilaya {
  let wil = RNG.getWilaya(name)
  let id = wil.id
  let cities = Object.entries(wil.cities).map(entry => cityGen(id, entry))

  let wilaya = new Classes.Wilaya(name, id, cities)
  return wilaya
}

function jsonGen(count: number) {
  console.log(count)
  return RNG.shuffle(Object.keys(countryTemplate)).slice(0, count).map(wil => {
    return wilayaGen(wil)
  });
}


console.log("Generating and writing started UwU")
let database = jsonGen(WIL_COUNT)
// console.log(database)
writeFileSync("data.json", JSON.stringify(database))
console.log("Done!")