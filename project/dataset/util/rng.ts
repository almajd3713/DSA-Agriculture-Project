
import type * as Types from "./types"

export const rndNum = (min: number, max: number) => min + Math.floor(Math.random() * (max - min + 1))
const rndFromArr = <T>(arr: T[]) => {
  console.log(arr)
  return arr[Math.floor(Math.random() * arr.length)]
}

interface countryTemplateInterface {
  [wilaya: string]: {
    [city: string] : string[]
  }
}

const countryTemplate: countryTemplateInterface = {
  tissemsilt: {
    khemisti: ["badr", "el_darb"],
    aion: ["baraka", "centre"]
  }, 
  chlef: {
    chlef: ["shetia", "salam"],
    blad: ["shara", "lanex"]
  }
}
export const WILAYAS = Object.keys(countryTemplate)
const RNGSTR = "123456789"
const idGen = () => {
  let str = ""
  for(let i = 0; i < 16; i++) str = `${str}${rndFromArr<string>(RNGSTR.split(''))}`
  return str
}
export const getWilaya = (name: string) => {
  return countryTemplate[name]
}
export const getCity = (wil: Types.Wilaya) => {
  return wil.cities
}
export const getArea = (city: Types.City) => city.areas

