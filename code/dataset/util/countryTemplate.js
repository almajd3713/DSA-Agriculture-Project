"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
let countryTemplateNoId = {
    "Adrar": {
        "Reggane": ["Hay Nasr", "Hay Zirara"],
        "In_Salah": ["Gara", "Tin Amara"]
    },
    "Chlef": {
        "Tenes": ["El Milia", "Beni Saf"],
        "El_marsa": ["Ras El Hadid", "Mers El Hadjadj"]
    },
    "Laghouat": {
        "Ain Madhi": ["Tadjmout", "Tadjrouna"],
        "Aflou": ["Sidi Bouzid", "Sebgag"]
    },
    "Oum El Bouaghi": {
        "Tagouft Seghira": ["Hai El Badr", "Hai Bouamama"],
        "Bir Kechba": ["Bir Sahli", "Draa Laghbar"]
    },
    "Batna": {
        "Timgad": ["Tassili n'Ajjer", "Koudiat Acerdoune"],
        "Arris": ["Tighanimine", "Tamza"]
    },
    "Bejaia": {
        "Tichy": ["Boulimat", "Tala Guilef"],
        "Akbou": ["Ighil Ali", "Chemini"]
    },
    "Biskra": {
        "Tolga": ["Sidi Okba", "El Kantara"],
        "Mchouneche": ["Ouled Djellal", "El Hadjira"]
    },
    "Bechar": {
        "Abadla": ["Timoudi", "El Ouata"],
        "Taghit": ["Brika", "Zaouia Fougania"]
    },
    "Blida": {
        "Boufarik": ["Sidi Moussa", "El Affroun"],
        "Oued_El_Alleug": ["Bir Mourad Rais", "Birkhadem"]
    },
    "Bouira": {
        "Lakhdaria": ["Ammal", "Bir Ghbalou"],
        "Mchedallah": ["Ath Mansour", "Aghbalou"]
    },
    "Tamanrasset": {
        "In_Guezzam": ["Talak"],
        "Tazrouk": ["Tit", "Idles"]
    },
    "Tebessa": {
        "Bir_El_Ater": ["El Ogla", "Morsott"],
        "El_Kouif": ["Negrine", "Bir Mokkadem"]
    },
    "Tlemcen": {
        "Maghnia": ["Hammam Boughrara", "Hennaya"],
        "Sebdou": ["Ouled Mimoun", "Remchi"]
    },
    "Tiaret": {
        "Mecheria": ["Aougrout", "Faidja"],
        "Ain_Deheb": ["Tiaret", "Meghila"]
    },
    "Tizi_Ouzou": {
        "Tigzirt": ["Tiza", "Ait-Said"],
        "Draa_Ben_Khedda": ["Mkira", "Idjeur"]
    },
    "Alger": {
        "Zeralda": ["Staoueli", "Rahmania"],
        "Bir Mourad Rais": ["Birkhadem", "R’raoua"]
    },
    "Djelfa": {
        "Ain El Ibil": ["Admit", "Mouadjebara"],
        "Messad": ["Deldoud", "Selmana"]
    },
    "Djilel": {
        "Chekfa": ["Borj T’har", "Sidi Abdelaziz"],
        "Taher": ["Chahna", "Ouadjana"]
    },
    "Setif": {
        "Ain Arnat": ["El Ouricia", "Mezloug"],
        "Bouandas": ["Ait Tizi", "Boussalem"]
    },
    "Saida": {
        "El Hassasna": ["Ain Sekhouna", "Sidi Boubekeur"],
        "Saida Province": ["Youb", "Ouled Brahim"]
    },
    "Skikda": {
        "Azzaba": ["Essebt", "El Ghedir"],
        "Tamales": ["Kerkera", "Bin El Ouiden"]
    },
    "Sidi Bel Abbes": {
        "Ain El Badr": ["Ouled Ali", "Zleifa"],
        "Telagh": ["Dhaya", "Teghalimet"]
    },
    "Annaba": {
        "Ain El Berda": ["Eulma", "Chorfa"],
        "Berrahal": ["Oued El Aneb", "Treat"]
    },
    Guelma: {
        "Ain Makhlouf": ["Ain Larbi", "Tamlouka"],
        "Houari Boumédienne": ["Ras El Agba", "Medjez Amar"]
    },
    "Constantine": {
        "El Khroub": ["Ouled Rahmoune", "Ain Smara"],
        "Ibn Ziad": ["Ibn Ziad", "Messaoud Boudjeriou"]
    },
    "Medea": {
        "Beni Slimane": ["Sidi Errabia", "Bouskene"],
        "Guelb El Kebir": ["Sedraia", "Bir Ben Laadeb"]
    },
    "Mostaganem": {
        "Achacha": ["Khadra", "Nekmaria"],
        "Sidi Ali": ["Tazgait", "Ouled Malah"]
    },
    "Msila": {
        "Ain El Melt": ["Bir Foda", "Ain Fares"],
        "Bou Saada": ["El Hamel", "Outline"]
    },
    "Mascara": {
        "Bouhanifia": ["Hacine", "Guittena"],
        "Sig": ["Chorfa", "Bou Henni"]
    },
    "Ouargla": {
        "Ain Beida": ["Chott", "Adjadja"],
        "N’Goussa": ["Frane", "Ouahda"]
    },
    "Oran": {
        "Ain turk ": ["Bousfer", " Elonsour"],
        "Erziou ": ["Elkerma", "Sidi ben yebka"]
    },
    "El Bayadh": {
        "Brezina ": ["Kraakda", " Ghassoul"],
        "Chellala ": ["el mehara", "Sidi Ameur"]
    },
    "Ilizi": {
        "djanet ": ["temdjert"],
        " Ain amenas ": ["bordj Omar driss", "Debbab"]
    },
    "Bordj Bou Arreridj": {
        "Bir Kasdali ": ["khelil", " Sidi embarek"],
        "Mansooura ": ["EL M'hir", "Haraza"]
    },
    Boumerdes: {
        "Ouled moussa": ["elhlaymiya", "elkouadria"],
        "Ouled hadadj": ["sbaate", "bartela"]
    },
    "El Tarf": {
        "El kala ": ["Souarekh", " Raml Souk ", "Al aioun"],
        "Bouteldja ": ["Lac des oiseaux", "Chefia"]
    },
    "Tindouf": {
        " Tindouf": ["elbyad", "Ain sefra"],
        "Oum el assel ": ["  Sidi mhamed", "Oued Zemoul"]
    },
    "Tissemsilt": {
        "Ammari ": ["Sidi Abed", " Maacem"],
        "khemisti ": ["khemisti", "layoune"]
    },
    "El Oued": {
        "EL MEGHAIER ": ["Douar el Maa", " el Nakhla"],
        "Taleb larbi ": [" el Hamria", "Ben guecha"]
    },
    "Khenchela": {
        " bouhmama ": ["Chelia", " M'Sara"],
        "Kais ": ["Kais", "Remila"]
    },
    "Souk Ahras": {
        "Heddada ": ["Khederra", " Ouled moumen"],
        "Taoura ": ["Drea", "Zaarouria"]
    },
    "Tipaza": {
        "Cherchell ": ["Sidi ghiles", " Sidi semiane"],
        "Hadjout ": ["Merrad", "Chaiba"]
    },
    "Mila": {
        "Rouached ": ["Tiberguent", " Minar zerraza"],
        " Teleghma ": ["ouled Seguen", "el Meshira"]
    },
    "Ain defla": {
        "Boumedfaa": ["Hoceinia", " ben allal "],
        "Hemmam righa ": ["Ain benian ", "Ain terki "]
    },
    "El Naâma": {
        "Mechria ": ["Ain ben Khelil", " El biod"],
        " Moghrar": ["Djeniene Bourezg", "Kasdir"]
    },
    "Ain Témouchent": {
        "El Amria": ["Bou Zedjar", "El Messaid"],
        "El Malah": ["Ouled Kihal", "Terga", "Chaabat El Ham"]
    },
    Ghardaia: {
        Bounoura: ["Bounoura", "El Atteuf"],
        "El Ménia": ["El Ménia", "Hassi Gara"]
    },
    Relizane: {
        "Ain Tarik": ["Ain Tarik", "Had Echkalla"],
        "El Matmar": ["Belassel Bouzegza", "Sidi Khettab", "Sidi M'hamed Benaouda"],
        Mendes: ["Oued Essalem", "Sidi Lazreg"],
    },
    Timimoun: {
        Timimoun: ["El Guesbah", "Féraoune"]
    },
    "Bordj Badji Mokhtar": {
        "Bordj Badji Mokhtar": ["Timiaouine"]
    },
    "Ouled Djellal": {
        "Ouled Djellal": ["Ech Chaiba", "Doucen"],
        "Sidi Khaled": ["Ouled Harkat", "Ouled Sassi"]
    },
    "Béni Abbès": {
        Kerzaz: ["Timoudi", "Beni Ikhlef"],
        "El Ouata": ["Aguedal", "El Beida"]
    },
    "Ain Salah": {
        "Ain Salah": ["El Barka", "Hinoune", "Sahla Tahtania"],
        "Ain Ghar": ["Ain Ghar"]
    },
    "Ain Guezzam": {
        "Tin Zaouatine": ["Tinzaouatene", "Taouandart"],
        "Ain Guezzam": ["Ain Ataye", "Garet Nous"]
    },
    Touggourt: {
        Mégarine: ["Mégarine", "Sidi Slimane"],
        Taibet: ["Benaceur", "M'Naguer"],
        Touggourt: ["Nezla", "Tebesbest", "Zaouia El Abidia"]
    },
    Djanet: {
        Djanet: ["Bordj El Houasse"]
    },
    "El M'Ghair": {
        "El M'Ghair": ["Oum Touyour", "Still"],
        Djamaâ: ["M'Rara", "Tendla"]
    },
    "El Menia": {
        "El Menia": ["Hassi Gara"],
        Mansourah: ["Mansourah", "Hassi Fehal"]
    },
};
let countryTemplate = {};
Object.keys(countryTemplateNoId).map((wilaya, i) => {
    countryTemplate[wilaya] = {
        id: i + 1,
        cities: countryTemplateNoId[wilaya]
    };
});
exports.default = countryTemplate;
