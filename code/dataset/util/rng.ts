
import type * as Types from "./types"
import countryTemplate from "./countryTemplate"

export const rndNum = (min: number, max: number) => min + Math.floor(Math.random() * (max - min + 1))
export const rndFromArr = <T>(arr: T[]) => {
  return arr[Math.floor(Math.random() * arr.length)]
}
export const shuffle = <T>(array: T[]) => {
  for (let i = array.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [array[i], array[j]] = [array[j], array[i]];
  }
  return array;
};


export const WILAYAS = Object.keys(countryTemplate)
// const RNGSTR = "123456789"
// const idGen = () => {
//   let str = ""
//   for(let i = 0; i < 16; i++) str = `${str}${rndFromArr<string>(RNGSTR.split(''))}`
//   return str
// }
export const getWilaya = (name: string) => {
  return countryTemplate[name]
}
export const getCity = (wil: Types.Wilaya) => {
  return wil.cities
}
export const getArea = (city: Types.City) => city.areas


const NAMES_MALES = [
  "abbad", "abbas", "abd", "abdus", "salam", "manaf", "rabbo", "abdel", "fattah", "nour", "abdi", "abdolreza", "abdu", "abdul", "ahad", "ali", "alim", "azim", "aziz", "baqi", "bari", "basir", "basit", "ghaffar", "ghani", "hadi", "hafiz", "hai", "hakim", "halim", "hamid", "haq", "hussein", "jabbar", "jalil", "jamil", "karim", "khaliq", "latif", "majid", "malik", "mannan", "monem", "muttalib", "qadir", "qayyum", "quddus", "rashid", "samad", "sattar", "wadud", "wahhab", "wahid", "zahir", "zahra", "abdullah", "abdur", "rab", "rahim", "raqib", "rauf", "razzaq", "sabur", "shakur", "abid", "abidin", "abo", "ab", "abu", "bakr", "hafs", "hamza", "nasir", "nasr", "adam", "adeel", "adeem", "adem", "aden", "adham", "adib", "adil", "adir", "adli", "adnan", "afif", "ahmad", "ahmed", "tijani", "ahsan", "akeem", "akif", "akram", "alaa", "aladdin", "naqi", "reza", "aman", "amanullah", "amer", "amin", "aminullah", "amir", "amjad", "ammar", "amr", "anas", "anis", "anisur", "rahman", "anjem", "anwar", "anwaruddin", "aqeel", "ari", "arif", "asad", "asadullah", "asem", "asghar", "ashraf", "asif", "asil", "islam", "ataullah", "atif", "atiq", "atiqullah", "awad", "ayad", "aymen", "ayub", "azem", "azeem", "azhar", "azimullah", "aziz", "azizullah", "azizur", "azmi", "azus", "badi", "badr", "bagher", "baha", "bahri", "baki", "bakir", "bara", "barkat", "barkatullah", "bashar", "bashir", "basri", "bilal", "bilel", "billah", "boualem", "boulos", "boutros", "brahim", "burhan", "caden", "chadli", "daniel", "dastgir", "daud", "dawoud", "dhikrullah", "ehsanullah", "ekram", "fadel", "fahd", "faheem", "fahmi", "fahri", "faisal", "faiz", "faizan", "faizullah", "fakhr", "fakhraddin", "fakhruddin", "faqir", "faraj", "farhat", "farid", "fariduddin", "faris", "farooq", "fasih", "fathallah", "fathi", "fatin", "fawaz", "fawzi", "fayez", "fazel", "fazl", "ur", "fazlallah", "fazli", "fazlul", "fikri", "fouzan", "fouad", "fuad", "furkan", "gaffar", "gamil", "ghanem", "ghassan", "ghiyath", "ghulam", "faruq", "mohiuddin", "gulzar", "habib", "habibullah", "hadem", "hadid", "hafeez", "hafizullah", "haitham", "hajj", "hajji", "hakam", "haldun", "hamdan", "hamdi", "hamidullah", "hani", "harbi", "hanif", "harun", "hashem", "hashim", "hasib", "hassan", "hassim", "hatem", "hayatullah", "haydar", "hazem", "hibat", "hichem", "hidayatullah", "hikmat", "hilmi", "hisham", "hossam", "hurairah", "husam", "ibrahim", "ibro", "idris", "ihab", "ihsan", "ikhtiyar", "ikramullah", "ikrimah", "ilyas", "imad", "imran", "imtiaz", "inaam", "inayatullah", "iqbal", "irfan", "isa", "ishak", "issam", "ishtiaq", "iskandar", "ismail", "ismat", "ismatullah", "izz", "izzat", "izzatullah","j'far", "jabal", "jaber", "jabir", "jabr", "jahid", "jalal", "jamal", "jameel", "jarrah", "jasem", "jawad", "jawdat", "jihad", "jubayr", "junayd", "jurj", "min","k'b", "kadeem", "kadir", "kadri", "kafeel", "kamal", "kamil", "karem", "kashif", "kazem", "khadem", "khair", "khakim", "khalfan", "khalid", "khalifah", "khalil","khalil-u-rehman", "khamis", "kulthum", "labib", "lalji", "luay", "lutfullah", "lutfur", "mahalati", "mahbubur", "mahdi", "mahfuz", "mahir", "mahmud", "mamdouh", "mansur", "manzur", "marwan", "mashallah", "masoud", "maytham", "mehdi", "melhem", "michel", "midhat", "mizanur", "moatassem", "moeen", "moemen", "mohammad", "taqi", "mohannad", "mohy", "moin", "moinuddin", "mojtaba", "moncef", "moneim","m'iz","mu'dh", "muammer", "mubarak", "muhammad", "muharrem", "muhibullah", "muhsin", "mukhtar", "mumtaz", "munib", "munif", "munir", "murad", "murtaza", "musa", "muslim", "mustafa", "muzaffar", "nabih", "nabil", "nadeem", "nader", "nadir", "nadur", "naguib", "nahyan", "naif", "naim", "naji", "najib", "najibullah", "najim", "najm", "naqibullah", "naseeb", "naseer", "nasim", "nasrallah", "nasri", "nasser", "nassif", "nasuh", "nawaf", "nawaz", "nowfal", "nazif", "nazim", "nazimuddin", "nazmi", "nihad", "nimatullah", "nizam","n'man", "numan", "nuh", "nur", "nuri", "nurullah", "nusrat", "omar", "osama", "othman", "qaid", "qamar", "qasim", "qasymbek", "qudratullah", "qusay", "qutb", "rabih", "raed", "rafiq", "rahmatullah", "rahmi", "rajab", "rajaei", "raji", "ramiz", "ramzan", "rakibul", "rakib", "ramzi", "rashad", "rasul", "rayan", "redouane", "riad", "riaz", "ridwan", "rifat", "rizqallah", "ruhi", "ruhullah", "rukn", "rushdi","s'd", "seif", "ilislam","s'id", "saud", "saad", "saadallah", "sabri", "sabah", "saddam", "sadik", "sadr", "safi", "safiullah", "sahir", "saif", "saifullah", "saifur", "sajid", "sajjad", "salah", "saleh", "salem", "salim", "salman", "samadu", "samee", "samer", "sami", "samir", "samirah", "samiullah", "sanaullah", "saqib", "sardar", "sarmad", "satam", "sayf", "sayyid", "shaban", "shad", "shafiq", "shafiqullah", "shahid", "shahrukh", "shakeel", "shakir", "shams", "shamsur", "sharaf", "sharifullah", "shawkat", "shawki", "shiraz", "shihab", "shujauddin", "shukri", "sidique", "sidqi", "sirajuddin", "suhail", "suleiman", "sultan", "shaheed", "taha", "taher", "tahmid", "tahsin", "talal", "talat", "talhah", "talib", "tarazi", "tariq", "tawfik", "tayeb", "tayfur", "tufail", "turki", "talin", "ubay", "ubayd", "uday", "uthman", "usama", "wadih", "wael", "wafi", "wahed", "wajdi", "wajid", "waleed", "waliullah", "wasim", "wazir", "wissem", "yacine", "yadollah", "yahya", "yakub", "yahir", "yasser", "yunus", "yusha", "yusuf", "zafar", "zafarullah", "zafer", "zahed", "zaid", "zaim", "zainal", "zakariya", "zaki", "zane", "zayn", "zeeshan", "ziad", "ziauddin", "ziaur", "zubayr"
]
const NAMES_FEMALES = [
  "abeer", "abiha", "adela", "afaf", "afreen", "aisha", "aliya", "alya", "amalia", "amina", "amira", "arwa", "ashraqat", "ashfa", "asma", "atikah", "aya", "azra", "aziza", "boutheina", "bushra", "besma", "chaima", "dalal", "dalia", "danielle", "dana", "dareen", "dina", "eliana", "esma", "eva", "farah", "farida", "fatima", "feyrouz", "fouz", "habiba", "hafsa", "hajra", "hala", "halima", "hamida", "hana", "hanifa", "havva", "hawa", "hayat", "hessa", "huda", "ibtisam", "ireen", "jamila", "jana", "jawahir", "jena", "jennifer", "jessica", "joelle", "joud", "jouri", "julia", "jumana", "kareena", "karima", "katya", "khadija", "khairunnisa", "khawlah", "lama", "lamia", "lana", "lara", "latifa", "layan", "leila", "lina", "lulwa", "madiha", "maha", "mahmuna", "mai", "malika", "maria", "marwa", "maryam", "maya", "maysoon", "melek", "melissa", "mila", "mira", "mirna", "mona", "munira", "nadia", "nadine", "nafisa", "nahla", "naila", "naima", "najat", "najma", "nalini", "nasrin", "natasha", "nathalie", "nawal", "nayla", "naziha", "nazira", "nehal", "nejla", "nermin", "nezha", "nina", "qistina", "rabia", "rahima", "rana", "rania", "rashida", "reem", "riffat", "rimas", "rita", "ruqayya", "saadia", "sabiha", "subiksha", "safaa", "safiya", "sahar", "saida", "saira", "sajida", "sakhra", "sakina", "salma", "samar", "samira", "samiya", "sandra", "sania", "sarah", "selma", "shahd", "shakira", "shatha", "sherine", "shumaila", "suha", "sumaya", "sonia", "soraida", "tahira", "tala", "tamara", "tanisha", "tanya", "tara", "taslima", "tina", "tuba", "umm", "wafaa", "waliya", "wajahat", "wajhat", "yamina", "yara", "yasmin", "zalayha", "zakiya", "zaynab", "zuhal", "zoraida", "amal", "chadi", "farrah", "laden", "nakia", "noor", "nair", "zain", "zia", "zial"
]


const NAMES_LAST = [
  "Abadi", "Abboud", "Almasi", "Amari", "Antar", "Antoun", "Arian", "Asfour", "Asghar", "Asker", "Aswad", "Atiyeh", "Attia", "Awad", "Baba", "Bahar", "Basara", "Baz", "Bishara", "Bitar", "Botros", "Boulos", "Boutros", "Cham", "Dagher", "Daher", "Deeb", "Essa", "Fakhoury", "Ganem", "Ganim", "Gerges", "Ghannam", "Guirguis", "Hadad", "Haddad", "Haik", "Hajjar", "Hakimi", "Halabi", "Hanania", "Handal", "Harb", "Isa", "Issa", "Kalb", "Kanaan", "Kassab", "Kassis", "Kattan", "Khouri", "Khoury", "Kouri", "Koury", "Maalouf", "Maloof", "Malouf", "Maroun", "Masih", "Mifsud", "Mikhail", "Moghadam", "Morcos", "Nader", "Nahas", "Naifeh", "Najjar", "Naser", "Nassar", "Nazari", "Pagination", "Quraishi", "Qureshi", "Rahal", "Rahal", "Sabbag", "Sabbagh", "Safar", "Said", "Salib", "Saliba", "Samaha", "Sarraf", "Sayegh", "Seif", "Shadid", "Shalhoub", "Shammas", "Shamon", "Shamoon", "Shamoun", "Sleiman", "Tahan", "Tannous", "Toma", "Totah", "Touma", "Tuma", "Wasem", "Zogby"
]

export const getName = (): {name: string, gender: Types.Gender} => {
  let genderNum = rndNum(0, 20);
  let gender = genderNum < 4 ? 1 : 0;
  let name = `${gender  ? rndFromArr(NAMES_FEMALES) : rndFromArr(NAMES_MALES)} ${rndFromArr(NAMES_LAST)}`
  return {gender, name}
}