export const enum PestSeverity { light, moderate, severe }
export const enum Gender { male, female }


export interface datasetStructure {
  wilayas: Wilaya[]
}

export interface Wilaya {
  name: string
  cities: City[]

}
export interface City {
  name: string
  areas: Area[]
}
export interface Area {
  name: string
  lands: Land[]
}
export interface Land {
  id: number
  farmer: Farmer
  workers: HumanWorker[]
  report: AnnualReport[]
  

}

export export interface HumanWorker {
  name: string
  id: number,
  gender: Gender
}

export interface Farmer extends HumanWorker { }

export interface AnnualReport {
  year: number
  months: MonthlyReport[]
}
export interface MonthlyReport {
  month: number
  data: LandData
}
export interface LandData {
  pesticideSeverity: PestSeverity
  products: Product[]
  waterConsumption: number
  electricityConsumption: number
}

export interface Product {
  name: string
  basePrice: number
  production: number
}

export interface SalesReport {
  [product: string]: number
}