"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.getArea = exports.getCity = exports.getWilaya = exports.WILAYAS = exports.rndNum = void 0;
const rndNum = (min, max) => min + Math.floor(Math.random() * (max - min + 1));
exports.rndNum = rndNum;
const rndFromArr = (arr) => {
    console.log(arr);
    return arr[Math.floor(Math.random() * arr.length)];
};
const countryTemplate = {
    tissemsilt: {
        khemisti: ["badr", "el_darb"],
        aion: ["baraka", "centre"]
    },
    chlef: {
        chlef: ["shetia", "salam"],
        blad: ["shara", "lanex"]
    }
};
exports.WILAYAS = Object.keys(countryTemplate);
const RNGSTR = "123456789";
const idGen = () => {
    let str = "";
    for (let i = 0; i < 16; i++)
        str = `${str}${rndFromArr(RNGSTR.split(''))}`;
    return str;
};
const getWilaya = (name) => {
    return countryTemplate[name];
};
exports.getWilaya = getWilaya;
const getCity = (wil) => {
    return wil.cities;
};
exports.getCity = getCity;
const getArea = (city) => city.areas;
exports.getArea = getArea;
