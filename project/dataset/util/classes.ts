import type * as Interfaces from "./types"

export class Wilaya implements Interfaces.Wilaya {
  name: string
  cities: City[];
  constructor(name: string, cities: City[]) {
    this.cities = cities
    this.name = name
  }
}

export class City implements Interfaces.City {
  name: string
  areas: Area[];
  constructor(name: string, areas: Area[]) {
    this.areas = areas
    this.name = name
  }
}

export class Area implements Interfaces.Area {
  name: string
  lands: Land[];
  constructor(name: string, lands: Land[]) {
    this.lands = lands
    this.name = name
  }
}

export class Land implements Interfaces.Land {
  id: number;
  farmer: Farmer;
  workers: HumanWorker[];
  report: Interfaces.AnnualReport[];
  constructor(id: number, farmer: Farmer, workers: HumanWorker[], report: AnnualReport[]) {
    this.id = id;
    this.farmer = farmer
    this.workers = workers
    this.report = report;
  }
}

export class HumanWorker implements Interfaces.HumanWorker {
  id: number
  gender: Interfaces.Gender;
  constructor(id: number, gender: Interfaces.Gender) {
    this.id = id
    this.gender = gender
  }
}

export class Farmer extends HumanWorker implements Interfaces.Farmer {
  constructor(id: number, gender: Interfaces.Gender) {
    super(id, gender)
  }
}

export class AnnualReport implements Interfaces.AnnualReport {
  year: number;
  months: MonthlyReport[];
  constructor(year: number, months: MonthlyReport[]) {
    this.year = year
    this.months = months
  }
}

export class MonthlyReport implements Interfaces.MonthlyReport {
  month: number;
  data: Interfaces.LandData
  constructor(month: number, data: Interfaces.LandData) {
    this.month = month
    this.data = data
  }
}
export class LandData implements Interfaces.LandData {
  products: Interfaces.Product[];
  pesticideSeverity: Interfaces.PestSeverity;
  waterConsumption: number;
  electricityConsumption: number;
  constructor(products: Product[] = [], pestSev = 0, waterCon: number, electCon: number) {
    this.products = products
    this.pesticideSeverity = pestSev 
    this.waterConsumption = waterCon
    this.electricityConsumption = electCon
  }
}


export class Product implements Interfaces.Product {
  name: string  
  basePrice: number
  production: number;
  constructor(name: string, basePrice: number, production: number) {
    this.name = name
    this.basePrice = basePrice
    this.production = production
  }
}

export class SalesReport {
  products: SalesReport
  constructor(products: SalesReport) {
    this.products = products
  }
}