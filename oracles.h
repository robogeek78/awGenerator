#include <vector>
#include <array>

//---------------------------------------------------------------------------------------------------------------------
// OracleEntry structure (used in all oracles)
//---------------------------------------------------------------------------------------------------------------------
struct OracleEntry {
    int index;
    int minRoll;
    int maxRoll;
    std::string result;
};

struct OracleEntryND {
    int index;
    int minRoll;
    int maxRoll;
    std::string result;
};

struct biomeOracle {
    int PlanetType;
    int FeatureIndex;
    std::string biome;
};

std::vector<std::string> regionList = { "Terminus", "Outlands", "Expanse" };
std::vector<std::string> megastructureTechList = { "Type 1", "Type 1 & 2", "Type 1, 2, & 3" };
std::vector<std::string> megastructureChanceList = { "Small Chance", "Unlikely", "50/50", "Likely", "Almost Certain" };
std::vector<std::string> sectorSheetList = { "Simple", "Detailed" };
std::vector<std::string> sectorSheetSizeList = { "13 Hex","15 Hex","17 Hex","19 Hex","21 Hex" };

// AW page 21: STELLAR OBJECT
std::vector<OracleEntry> stellarObjectTable = {
    {0, 1, 5, "Neutron star surrounded by intense magnetic fields"},
    {1, 6, 7, "Unstable star showing signs of impending supernova"},
    {2, 8, 12, "Two stars in close orbit connected by fiery tendrils of energy"},
    {3, 13, 21, "Hypergiant star generating turbulent solar winds"},
    {4, 22, 26, "Blazing blue star"},
    {5, 27, 41, "Burning yellow star"},
    {6, 42, 42, "Artificial star constructed by a long-dead civilization"},
    {7, 43, 57, "Glowing orange star"},
    {8, 58, 72, "Smoldering red star"},
    {9, 73, 82, "Young star incubating in a molecular cloud"},
    {10, 83, 87, "Corrupted star radiating with unnatural light"},
    {11, 88, 97, "White dwarf shining with spectral light"},
    {12, 98, 100, "Black hole"}  // Fixed: now has four values
};

// AW page 26: STELLAR OBJECT HEAT MAPSTELLAR MAP
enum eOrbitHeatLevel_t {
    OrbitHeat_Searing = 0,
    OrbitHeat_Hot,
    OrbitHeat_Warm,
    OrbitHeat_Cool,
    OrbitHeat_Cold,
    OrbitHeat_Frigid
};

// AW page 26: STELLAR OBJECT HEAT MAPSTELLAR MAP
const std::vector<std::string> heatLevelStrings = {
    "Searing",
    "Hot",
    "Warm",
    "Cool",
    "Cold",
    "Frigid"
};

// AW page 26: STELLAR OBJECT HEAT MAPSTELLAR MAP
eOrbitHeatLevel_t heatMap[][numOfOrbits] = {
    { OrbitHeat_Searing, OrbitHeat_Searing, OrbitHeat_Searing, OrbitHeat_Searing, OrbitHeat_Hot,    OrbitHeat_Hot    }, // ST_NEUTRON
    { OrbitHeat_Searing, OrbitHeat_Searing, OrbitHeat_Searing, OrbitHeat_Searing, OrbitHeat_Hot,    OrbitHeat_Warm   }, // ST_SUPERNOVA
    { OrbitHeat_Searing, OrbitHeat_Searing, OrbitHeat_Searing, OrbitHeat_Hot,     OrbitHeat_Hot,    OrbitHeat_Warm   }, // ST_BINARY
    { OrbitHeat_Searing, OrbitHeat_Searing, OrbitHeat_Searing, OrbitHeat_Hot,     OrbitHeat_Warm,   OrbitHeat_Warm   }, // ST_HYPERGIANT
    { OrbitHeat_Searing, OrbitHeat_Searing, OrbitHeat_Hot,     OrbitHeat_Hot,     OrbitHeat_Warm,   OrbitHeat_Cool   }, // ST_BLUESTAR ("Blazing blue star")
    { OrbitHeat_Searing, OrbitHeat_Searing, OrbitHeat_Hot,     OrbitHeat_Warm,    OrbitHeat_Warm,   OrbitHeat_Cold   }, // ST_BURNING_YELLOW
    { OrbitHeat_Searing, OrbitHeat_Hot,     OrbitHeat_Warm,    OrbitHeat_Warm,    OrbitHeat_Cold,   OrbitHeat_Frigid }, // ST_ARTIFICIAL
    { OrbitHeat_Searing, OrbitHeat_Hot,     OrbitHeat_Warm,    OrbitHeat_Cool,    OrbitHeat_Cold,   OrbitHeat_Frigid }, // ST_GLOWING_ORANGE
    { OrbitHeat_Searing, OrbitHeat_Hot,     OrbitHeat_Cool,    OrbitHeat_Cool,    OrbitHeat_Cold,   OrbitHeat_Frigid }, // ST_SMOLDERING_RED
    { OrbitHeat_Searing, OrbitHeat_Hot,     OrbitHeat_Warm,    OrbitHeat_Cold,    OrbitHeat_Frigid, OrbitHeat_Frigid }, // ST_YOUNG
    { OrbitHeat_Searing, OrbitHeat_Hot,     OrbitHeat_Cool,    OrbitHeat_Cold,    OrbitHeat_Frigid, OrbitHeat_Frigid }, // ST_CORRUPTED
    { OrbitHeat_Hot,     OrbitHeat_Warm,    OrbitHeat_Cool,    OrbitHeat_Cold,    OrbitHeat_Frigid, OrbitHeat_Frigid }, // ST_WHITE_DWARF
    { OrbitHeat_Searing, OrbitHeat_Cool,    OrbitHeat_Frigid,  OrbitHeat_Frigid,  OrbitHeat_Frigid, OrbitHeat_Frigid }  // ST_BLACKHOLE
};

// AW page 27: PLANETARY CLASS BASED ON HEAT (PLANETS EXPANDED)
enum ePlanetType_t {
    PlanetType_Furnace = 0,
    PlanetType_Desert,
    PlanetType_Jungle,
    PlanetType_Vital,
    PlanetType_Ocean,
    PlanetType_Ice,
    PlanetType_Chemical,
    PlanetType_Jovian,
    PlanetType_Rocky,
    PlanetType_Tainted,
    PlanetType_Metallic,
    PlanetType_Crystalline,
    PlanetType_TidallyLocked,
    PlanetType_Karst,
    PlanetType_Grave,
    PlanetType_Shattered,
    PlanetType_Living,
    PlanetType_Anomalous,
    maxPlanetTypes
};

// AW page 27: PLANETARY CLASS BASED ON HEAT (PLANETS EXPANDED)
const std::vector<std::string> planetTypeStrings = {
    "Furnace World",
    "Desert World",
    "Jungle World",
    "Vital World",
    "Ocean World",
    "Ice World",
    "Chemical World",
    "Jovian World",
    "Rocky World",
    "Tainted World",
    "Metallic World",
    "Crystalline World",
    "TidallyLocked World",
    "Karst World",
    "Grave World",
    "Shattered World",
    "Living World",
    "Anomalous World"
};


// AW page 27: PLANETARY CLASS BASED ON HEAT (PLANETS EXPANDED)
std::array<std::vector<OracleEntryND>, 6> planetTypeOracles{ {
    // OrbitHeat_Searing
    std::vector<OracleEntryND>{
        { PlanetType_Furnace,       1, 40 },
        { PlanetType_Desert,        41, 57 },
        { PlanetType_Jovian,        58, 69 },
        { PlanetType_Rocky,         70, 77 },
        { PlanetType_Tainted,       78, 83 },
        { PlanetType_Metallic,      84, 87 },
        { PlanetType_Crystalline,   88, 89 },
        { PlanetType_TidallyLocked, 90, 91 },
        { PlanetType_Karst,         92, 93 },
        { PlanetType_Grave,         94, 96 },
        { PlanetType_Shattered,     97, 98 },
        { PlanetType_Living,        99, 99 },
        { PlanetType_Anomalous,     100, 100 }
    },
    // OrbitHeat_Hot
    std::vector<OracleEntryND>{
        { PlanetType_Furnace,       1, 17 },
        { PlanetType_Desert,        18, 47 },
        { PlanetType_Jungle,        48, 57 },
        { PlanetType_Jovian,        58, 69 },
        { PlanetType_Rocky,         70, 77 },
        { PlanetType_Tainted,       78, 83 },
        { PlanetType_Metallic,      84, 87 },
        { PlanetType_Crystalline,   88, 89 },
        { PlanetType_TidallyLocked, 90, 91 },
        { PlanetType_Karst,         92, 93 },
        { PlanetType_Grave,         94, 96 },
        { PlanetType_Shattered,     97, 98 },
        { PlanetType_Living,        99, 99 },
        { PlanetType_Anomalous,     100, 100 }
    },
    // OrbitHeat_Warm
    std::vector<OracleEntryND>{
        { PlanetType_Desert,        1, 8 },
        { PlanetType_Jungle,        9, 26 },
        { PlanetType_Vital,         27, 39 },
        { PlanetType_Ocean,         40, 57 },
        { PlanetType_Jovian,        58, 69 },
        { PlanetType_Rocky,         70, 77 },
        { PlanetType_Tainted,       78, 83 },
        { PlanetType_Metallic,      84, 87 },
        { PlanetType_Crystalline,   88, 89 },
        { PlanetType_TidallyLocked, 90, 91 },
        { PlanetType_Karst,         92, 93 },
        { PlanetType_Grave,         94, 96 },
        { PlanetType_Shattered,     97, 98 },
        { PlanetType_Living,        99, 99 },
        { PlanetType_Anomalous,     100, 100 }
    },
    // OrbitHeat_Cool
    std::vector<OracleEntryND>{
        { PlanetType_Desert,        1, 4 },
        { PlanetType_Jungle,        5, 18 },
        { PlanetType_Vital,         19, 31 },
        { PlanetType_Ocean,         32, 57 },
        { PlanetType_Jovian,        58, 69 },
        { PlanetType_Rocky,         70, 77 },
        { PlanetType_Tainted,       78, 83 },
        { PlanetType_Metallic,      84, 87 },
        { PlanetType_Crystalline,   88, 89 },
        { PlanetType_TidallyLocked, 90, 91 },
        { PlanetType_Karst,         92, 93 },
        { PlanetType_Grave,         94, 96 },
        { PlanetType_Shattered,     97, 98 },
        { PlanetType_Living,        99, 99 },
        { PlanetType_Anomalous,     100, 100 }
    },
    // OrbitHeat_Cold
    std::vector<OracleEntryND>{
        { PlanetType_Jungle,        1, 5 },
        { PlanetType_Ocean,         6, 20 },
        { PlanetType_Ice,           21, 52 },
        { PlanetType_Chemical,      53, 57 },
        { PlanetType_Jovian,        58, 69 },
        { PlanetType_Rocky,         70, 77 },
        { PlanetType_Tainted,       78, 83 },
        { PlanetType_Metallic,      84, 87 },
        { PlanetType_Crystalline,   88, 89 },
        { PlanetType_TidallyLocked, 90, 91 },
        { PlanetType_Karst,         92, 93 },
        { PlanetType_Grave,         94, 96 },
        { PlanetType_Shattered,     97, 98 },
        { PlanetType_Living,        99, 99 },
        { PlanetType_Anomalous,     100, 100 }
    },
    // OrbitHeat_Frigid
    std::vector<OracleEntryND>{
        { PlanetType_Ocean,         1, 5 },
        { PlanetType_Ice,           6, 47 },
        { PlanetType_Chemical,      48, 57 },
        { PlanetType_Jovian,        58, 69 },
        { PlanetType_Rocky,         70, 77 },
        { PlanetType_Tainted,       78, 83 },
        { PlanetType_Metallic,      84, 87 },
        { PlanetType_Crystalline,   88, 89 },
        { PlanetType_TidallyLocked, 90, 91 },
        { PlanetType_Karst,         92, 93 },
        { PlanetType_Grave,         94, 96 },
        { PlanetType_Shattered,     97, 98 },
        { PlanetType_Living,        99, 99 },
        { PlanetType_Anomalous,     100, 100 }
    }
} };

// AW page 40: PLANETARY ATTRIBUTES (Size)
std::vector<OracleEntry> planetSizeTable = {
    {0,  1,   3,   "Dwarf"},
    {1,  4,   13,  "Lesser"},
    {2,  14,  28,  "Small"},
    {3,  29,  49,  "Medium"},
    {4,  50,  64,  "Large"},
    {5,  65,  74,  "Huge"},
    {6,  75,  82,  "Giant"},
    {7,  83,  89,  "Enormous"},
    {8,  90,  94,  "Massive"},
    {9,  95,  97,  "Titanic"},
    {10, 98,  99,  "Colossal"},
    {11, 100, 100, "Vast"},
};

// AW page 40: PLANETARY ATTRIBUTES (Density)
std::vector<OracleEntry> planetDensityTable = {
    {0,  1,  10,  "Very Light"},
    {1,  11, 30,  "Light"},
    {2,  31, 70,  "Moderate"},
    {3,  71, 90,  "Heavy"},
    {4,  91, 100, "Very Heavy"},
};

// AW page 40: PLANETARY ATTRIBUTES (Gravity)
std::array<std::array<std::string, 5>, 12> planetGravityTable{ {
    { "Weak",   "Weak",   "Low",    "Low",    "Ideal" },
    { "Weak",   "Low",    "Low",    "Ideal",  "Ideal" },
    { "Low",    "Low",    "Ideal",  "Ideal",  "Ideal" },
    { "Low",    "Ideal",  "Ideal",  "Ideal",  "High" },
    { "Ideal",  "Ideal",  "Ideal",  "High",   "High" },
    { "Ideal",  "Ideal",  "High",   "High",   "High" },
    { "Ideal",  "High",   "High",   "High",   "High" },
    { "Ideal",  "High",   "High",   "High",   "Severe" },
    { "High",   "High",   "High",   "Severe", "Severe" },
    { "High",   "High",   "Severe", "Severe", "Severe" },
    { "High",   "Severe", "Severe", "Severe", "Severe" },
    { "Severe", "Severe", "Severe", "Severe", "Severe" }
} };

// AW page 40: PLANETARY ATTRIBUTES (Circumference)
std::array<std::array<int, 2>, 12> planetCircumferenceTable{ {
    { 5,   10  },
    { 11,  20  },
    { 21,  26  },
    { 27,  45  },
    { 46,  100 },
    { 101, 200 },
    { 201, 300 },
    { 301, 400 },
    { 401, 500 },
    { 501, 600 },
    { 601, 700 },
    { 701, 800 }
} };

// AW page 40: PLANETARY ATTRIBUTES (Orbital Feature)
std::vector<OracleEntry> orbitalFeatureTable = {
    {0, 1,  10,  "None"},
    {1, 11, 25,  "Ring System"},
    {2, 26, 75,  "Moon(s)"},
    {3, 76, 80,  "Dense Nebula Cloud"},
    {4, 81, 83,  "Fiery Energy Storm"},
    {5, 84, 85,  "Precursor Vault (orbital)"},
    {6, 86, 92,  "Descriptor + Focus"},
    {7, 93, 100, "Roll Twice"}
};

//AW page 40: PLANETARY ATTRIBUTES(Ring System)
std::vector<OracleEntry> ringSystemTable = {
    {0, 1,   25,  "Thin and barely visable Ring"},
    {1, 26,  80,  "Banded Ring of different shades"},
    {2, 81,  95,  "Lone ring of a single shade"},
    {3, 96,  99,  "Vast system of concentric rings"},
    {4, 100, 100, "Many rings at different angles"}
};

//AW page 42: Number of Moons
std::array<std::vector<OracleEntry>, 12> moonNumberTable{ {
    //"Dwarf"
    std::vector<OracleEntry>{
        { 0, 1,  75,  "One"},
        { 1, 76, 100, "Two"},
    },
    //"Lesser"
    std::vector<OracleEntry>{
        { 0, 1,  65,  "One"},
        { 1, 66, 95,  "Two"},
        { 2, 96, 100, "Three"},
    },
    //"Small"
    std::vector<OracleEntry>{
        { 0, 1,   50,  "One"},
        { 1, 51,  95,  "Two"},
        { 2, 96,  99,  "Three"},
        { 3, 100, 100, "Few"},
    },
    //"Medium"
    std::vector<OracleEntry>{
        { 0, 1,   40,  "One"},
        { 1, 41,  75,  "Two"},
        { 2, 76,  95,  "Three"},
        { 3, 96,  99,  "Few"},
        { 4, 100, 100, "Several"},
    },
    //"Large"
    std::vector<OracleEntry>{
        { 0, 1,  10,  "One"},
        { 1, 11, 30,  "Two"},
        { 2, 31, 60,  "Three"},
        { 3, 61, 85,  "Few"},
        { 4, 86, 100, "Several"},
    },
    //"Huge"
    std::vector<OracleEntry>{
        { 1, 1,  2,   "Two"},
        { 2, 3,  5,   "Three"},
        { 3, 6,  25,  "Few"},
        { 4, 26, 60,  "Several"},
        { 5, 61, 85,  "Many"},
        { 6, 86, 100, "Numerous"},
    },
    //"Giant"
    std::vector<OracleEntry>{
        { 2, 1,  3,   "Three"},
        { 3, 4,  13,  "Few"},
        { 4, 14, 28,  "Several"},
        { 5, 29, 58,  "Many"},
        { 6, 59, 95,  "Numerous"},
        { 7, 96, 100, "Abundant"},
    },
    //"Enormous"
    std::vector<OracleEntry>{
        { 3, 1,  2,   "Few"},
        { 4, 3,  5,   "Several"},
        { 5, 6,  10,  "Many"},
        { 6, 11, 30,  "Numerous"},
        { 7, 31, 90,  "Abundant"},
        { 8, 91, 100, "Plethora"},
    },
    //"Massive"
    std::vector<OracleEntry>{
        { 5, 1,  5,   "Many"},
        { 6, 6,  15,  "Numerous"},
        { 7, 16, 70,  "Abundant"},
        { 8, 71, 100, "Plethora"},
    },
    //"Titanic"
    std::vector<OracleEntry>{
        { 6, 1,  5,   "Numerous"},
        { 7, 6,  45,  "Abundant"},
        { 8, 46, 100, "Plethora"},
    },
    //"Colossal"
    std::vector<OracleEntry>{
        { 7, 1,  25,  "Abundant"},
        { 8, 26, 100, "Plethora"},
    },
    //"Vast"
    std::vector<OracleEntry>{
        { 7, 1,  10,  "Abundant"},
        { 8, 11, 100, "Plethora"},
    },
} };



std::array<std::array<int, 2>, 9> moonQuantity{ {
    { 1,   1   }, // one
    { 2,   2   }, // two
    { 3,   3   }, // three
    { 4,   9   }, // few
    { 10,  15  }, // several
    { 16,  26  }, // many
    { 27,  45  }, // numerous
    { 46,  100 }, // abundant
    { 101, 200 }, // plethora
} };

enum eAtmosphereType_t {
    AtmosphereType_None = 0,
    AtmosphereType_Toxic,
    AtmosphereType_Corrosive,
    AtmosphereType_Marginal,
    AtmosphereType_Breathable,
    AtmosphereType_Ideal,
    AtmosphereType_Other
};

//: Atmosphere
std::array<std::vector<OracleEntry>, 18> atmosphereTable{ {
    // PlanetType_Furnace ( PG52 )
    std::vector<OracleEntry>{
        { AtmosphereType_None,       1,  10,  "None"},
        { AtmosphereType_Toxic,      11, 50,  "Toxic"},
        { AtmosphereType_Corrosive,  51, 65,  "Corrosive"},
        { AtmosphereType_Marginal,   66, 90,  "Marginal"},
        { AtmosphereType_Breathable, 91, 100, "Breathable"},
    },
    // PlanetType_Desert ( PG50 )
    std::vector<OracleEntry>{
        { AtmosphereType_None,       1,  10,  "None"},
        { AtmosphereType_Toxic,      11, 25,  "Toxic"},
        { AtmosphereType_Corrosive,  26, 40,  "Corrosive"},
        { AtmosphereType_Marginal,   41, 70,  "Marginal"},
        { AtmosphereType_Breathable, 71, 95,  "Breathable"},
        { AtmosphereType_Ideal,      96, 100, "Ideal"},
    },
    // PlanetType_Jungle ( PG60 )
    std::vector<OracleEntry>{
        { AtmosphereType_Toxic,      1, 25,  "Toxic"},
        { AtmosphereType_Corrosive,  26, 30,  "Corrosive"},
        { AtmosphereType_Marginal,   31, 60,  "Marginal"},
        { AtmosphereType_Breathable, 61, 90,  "Breathable"},
        { AtmosphereType_Ideal,      91, 100, "Ideal"},
    },
    // PlanetType_Vital ( PG44 )
    std::vector<OracleEntry>{
        { AtmosphereType_None,       1,  10,  "None"},
        { AtmosphereType_Toxic,      11, 25,  "Toxic"},
        { AtmosphereType_Corrosive,  26, 40,  "Corrosive"},
        { AtmosphereType_Marginal,   41, 70,  "Marginal"},
        { AtmosphereType_Breathable, 71, 95,  "Breathable"},
        { AtmosphereType_Ideal,      96, 100, "Ideal"},
    },
    // PlanetType_Ocean ( PG70 )
    std::vector<OracleEntry>{
        { AtmosphereType_None,       1,  5,   "None"},
        { AtmosphereType_Toxic,      6,  20,  "Toxic"},
        { AtmosphereType_Corrosive,  21, 25,  "Corrosive"},
        { AtmosphereType_Marginal,   26, 60,  "Marginal"},
        { AtmosphereType_Breathable, 61, 90,  "Breathable"},
        { AtmosphereType_Ideal,      91, 100, "Ideal"},
    },
    // PlanetType_Ice ( PG56 )
    std::vector<OracleEntry>{
        { AtmosphereType_None,       1,  15,  "None"},
        { AtmosphereType_Toxic,      16, 35,  "Toxic"},
        { AtmosphereType_Corrosive,  36, 40,  "Corrosive"},
        { AtmosphereType_Marginal,   41, 70,  "Marginal"},
        { AtmosphereType_Breathable, 71, 95,  "Breathable"},
        { AtmosphereType_Ideal,      96, 100, "Ideal"},
    },
    // PlanetType_Chemical ( PG46 )
    std::vector<OracleEntry>{
        { AtmosphereType_Toxic,     1,  60,  "Toxic"},
        { AtmosphereType_Corrosive, 61, 95,  "Corrosive"},
        { AtmosphereType_Marginal,  96, 100, "Marginal"},
    },
    // PlanetType_Jovian ( PG58 )
    std::vector<OracleEntry>{
        { AtmosphereType_Toxic,      1,  50,  "Toxic"},
        { AtmosphereType_Corrosive,  51, 65,  "Corrosive"},
        { AtmosphereType_Marginal,   66, 85,  "Marginal"},
        { AtmosphereType_Breathable, 86, 100, "Breathable"},
    },
    // PlanetType_Rocky ( PG72 )
    std::vector<OracleEntry>{
        { AtmosphereType_None,       1,  65,  "None"},
        { AtmosphereType_Toxic,      66, 80,  "Toxic"},
        { AtmosphereType_Corrosive,  81, 85,  "Corrosive"},
        { AtmosphereType_Marginal,   86, 95,  "Marginal"},
        { AtmosphereType_Breathable, 96, 100, "Breathable"},
    },
    // PlanetType_Tainted ( PG76 )
    std::vector<OracleEntry>{
        { AtmosphereType_Toxic,      1, 65,   "Toxic"},
        { AtmosphereType_Corrosive,  66, 85,  "Corrosive"},
        { AtmosphereType_Marginal,   86, 95,  "Marginal"},
        { AtmosphereType_Breathable, 96, 100, "Breathable"},
    },
    // PlanetType_Metallic ( PG68 )
    std::vector<OracleEntry>{
        { AtmosphereType_None,       1,  65,  "None"},
        { AtmosphereType_Toxic,      66, 85,  "Toxic"},
        { AtmosphereType_Corrosive,  86, 95,  "Corrosive"},
        { AtmosphereType_Marginal,   96, 98,  "Marginal"},
        { AtmosphereType_Breathable, 99, 100, "Breathable"},
    },
    // PlanetType_Crystalline ( PG48 )
    std::vector<OracleEntry>{
        { AtmosphereType_None,       1,  65,  "None"},
        { AtmosphereType_Toxic,      66, 85,  "Toxic"},
        { AtmosphereType_Corrosive,  86, 95,  "Corrosive"},
        { AtmosphereType_Marginal,   96, 98,  "Marginal"},
        { AtmosphereType_Breathable, 99, 100, "Breathable"},
    },
    // PlanetType_TidallyLocked ( PG79 sort of) 
    std::vector<OracleEntry>{
        { AtmosphereType_Other,      1,  100,  "TidallyLocked Dark/Light/rings"},
    },
    // PlanetType_Karst ( PG63, sort of )
    std::vector<OracleEntry>{
        { AtmosphereType_Other,      1,  100,  "Karst Surface/Underground"},
    },
    // PlanetType_Grave ( PG54 )
    std::vector<OracleEntry>{
        { AtmosphereType_Toxic,      1,  50,  "Toxic"},
        { AtmosphereType_Corrosive,  51, 65,  "Corrosive"},
        { AtmosphereType_Marginal,   66, 85,  "Marginal"},
        { AtmosphereType_Breathable, 86, 100, "Breathable"},
    },
    // PlanetType_Shattered ( PG74 )
    std::vector<OracleEntry>{
        { AtmosphereType_None,       1,  93,   "None"},
        { AtmosphereType_Toxic,      94, 95,   "Toxic"},
        { AtmosphereType_Corrosive,  96, 97,   "Corrosive"},
        { AtmosphereType_Marginal,   98, 99,   "Marginal"},
        { AtmosphereType_Breathable, 100, 100, "Breathable"},
    },
    // PlanetType_Living ( PG64 )
    std::vector<OracleEntry>{
        { AtmosphereType_Toxic,      1,   70,  "Toxic"},
        { AtmosphereType_Corrosive,  71,  88,  "Corrosive"},
        { AtmosphereType_Marginal,   89,  99,  "Marginal"},
        { AtmosphereType_Breathable, 100, 100, "Breathable"},
    },
    // PlanetType_Anomalous ( PG44 )
    std::vector<OracleEntry>{
        { AtmosphereType_None,       1,  10,  "None"},
        { AtmosphereType_Toxic,      11, 25,  "Toxic"},
        { AtmosphereType_Corrosive,  26, 40,  "Corrosive"},
        { AtmosphereType_Marginal,   41, 70,  "Marginal"},
        { AtmosphereType_Breathable, 71, 95,  "Breathable"},
        { AtmosphereType_Ideal,      96, 100, "Ideal"},
    },
} };

enum eLifeType_t {
    LifeType_None = 0,
    LifeType_Extinct,
    LifeType_Scarce,
    LifeType_Diverse,
    LifeType_Bountiful,
    LifeType_Overrun,
    LifeType_Other
};

//: Life
std::array<std::vector<OracleEntry>, 18> LifeTable{ {
        // PlanetType_Furnace ( PG52 )
std::vector<OracleEntry>{
    { LifeType_None,      1,  35,  "None"},
    { LifeType_Extinct,   36, 60,  "Extinct"},
    { LifeType_Scarce,    61, 85,  "Scarce"},
    { LifeType_Diverse,   86, 95,  "Diverse"},
    { LifeType_Bountiful, 96, 98,  "Bountiful"},
    { LifeType_Overrun,   99, 100, "Overrun"},
},
// PlanetType_Desert ( PG50 )
std::vector<OracleEntry>{
    { LifeType_None,      1,  20,  "None"},
    { LifeType_Extinct,   21, 40,  "Extinct"},
    { LifeType_Scarce,    41, 70,  "Scarce"},
    { LifeType_Diverse,   71, 90,  "Diverse"},
    { LifeType_Bountiful, 91, 97,  "Bountiful"},
    { LifeType_Overrun,   98, 100, "Overrun"},
},
// PlanetType_Jungle ( PG60 )
std::vector<OracleEntry>{
    { LifeType_Scarce,    1, 5,    "Scarce"},
    { LifeType_Diverse,   6, 35,   "Diverse"},
    { LifeType_Bountiful, 36, 75,  "Bountiful"},
    { LifeType_Overrun,   76, 100, "Overrun"},
},
// PlanetType_Vital ( PG80 )
std::vector<OracleEntry>{
    { LifeType_Scarce,    1, 10,   "Scarce"},
    { LifeType_Diverse,   11, 45,  "Diverse"},
    { LifeType_Bountiful, 46, 85,  "Bountiful"},
    { LifeType_Overrun,   86, 100, "Overrun"},
},
// PlanetType_Ocean ( PG70 )
std::vector<OracleEntry>{
    { LifeType_None,      1,  5,   "None"},
    { LifeType_Extinct,   6,  15,  "Extinct"},
    { LifeType_Scarce,    16, 30,  "Scarce"},
    { LifeType_Diverse,   31, 60,  "Diverse"},
    { LifeType_Bountiful, 61, 90,  "Bountiful"},
    { LifeType_Overrun,   91, 100, "Overrun"},
},
// PlanetType_Ice ( PG56 )
std::vector<OracleEntry>{
    { LifeType_None,      1,  20,  "None"},
    { LifeType_Extinct,   21, 40,  "Extinct"},
    { LifeType_Scarce,    41, 70,  "Scarce"},
    { LifeType_Diverse,   71, 90,  "Diverse"},
    { LifeType_Bountiful, 91, 97,  "Bountiful"},
    { LifeType_Overrun,   98, 100, "Overrun"},
},
// PlanetType_Chemical ( PG46 )
std::vector<OracleEntry>{
    { LifeType_None,      1,  25,  "None"},
    { LifeType_Extinct,   26, 75,  "Extinct"},
    { LifeType_Scarce,    76, 95,  "Scarce"},
    { LifeType_Diverse,   96, 100, "Diverse"},
},
// PlanetType_Jovian ( PG58 )
std::vector<OracleEntry>{
    { LifeType_None,      1,  50,  "None"},
    { LifeType_Extinct,   51, 55,  "Extinct"},
    { LifeType_Scarce,    56, 75,  "Scarce"},
    { LifeType_Diverse,   76, 90,  "Diverse"},
    { LifeType_Bountiful, 91, 97,  "Bountiful"},
    { LifeType_Overrun,   98, 100, "Overrun"},
},
// PlanetType_Rocky ( PG72 )
std::vector<OracleEntry>{
    { LifeType_None,      1,  65,  "None"},
    { LifeType_Extinct,   66, 80,  "Extinct"},
    { LifeType_Scarce,    81, 90,  "Scarce"},
    { LifeType_Diverse,   91, 95,  "Diverse"},
    { LifeType_Bountiful, 96, 98,  "Bountiful"},
    { LifeType_Overrun,   99, 100, "Overrun"},
},
// PlanetType_Tainted ( PG76 )
std::vector<OracleEntry>{
    { LifeType_Scarce,    1, 10,   "Scarce"},
    { LifeType_Diverse,   11, 35,  "Diverse"},
    { LifeType_Bountiful, 36, 65,  "Bountiful"},
    { LifeType_Overrun,   66, 100, "Overrun"},
},
// PlanetType_Metallic ( PG68 )
std::vector<OracleEntry>{
    { LifeType_None,      1,  80,  "None"},
    { LifeType_Extinct,   81, 90,  "Extinct" },
    { LifeType_Scarce,    91, 95,  "Scarce" },
    { LifeType_Diverse,   96, 98,  "Diverse" },
    { LifeType_Bountiful, 99, 100, "Bountiful" },
},
// PlanetType_Crystalline ( PG48 )
std::vector<OracleEntry>{
    { LifeType_None,      1,  80,  "None"},
    { LifeType_Extinct,   81, 90,  "Extinct" },
    { LifeType_Scarce,    91, 95,  "Scarce" },
    { LifeType_Diverse,   96, 98,  "Diverse" },
    { LifeType_Bountiful, 99, 100, "Bountiful" },
},
// PlanetType_TidallyLocked ( PG79 sort of) 
std::vector<OracleEntry>{
    { LifeType_Other,     1,  100, "TidallyLocked Dark/Light/rings"},
},
// PlanetType_Karst ( PG63, sort of )
std::vector<OracleEntry>{
    { LifeType_Other,     1,  100, "Karst Surface/Underground"},
},
// PlanetType_Grave ( PG54 )
std::vector<OracleEntry>{
    { LifeType_None,      1,  25,  "None"},
    { LifeType_Extinct,   26, 75,  "Extinct" },
    { LifeType_Scarce,    76, 95,  "Scarce" },
    { LifeType_Diverse,   95, 100, "Diverse" },
},
// PlanetType_Shattered ( PG74 )
std::vector<OracleEntry>{
    { LifeType_None, 1, 25, "None"},
    { LifeType_Extinct,   26, 75,  "Extinct" },
    { LifeType_Scarce,    76, 95,  "Scarce" },
    { LifeType_Diverse,   95, 100, "Diverse" },
},
// PlanetType_Living ( PG64 )
std::vector<OracleEntry>{
    { LifeType_Scarce, 1, 5, "Scarce"},
    { LifeType_Diverse,   6, 20,  "Diverse" },
    { LifeType_Bountiful, 21, 75,  "Bountiful" },
    { LifeType_Overrun,   76, 100, "Overrun" },
},
// PlanetType_Anomalous ( PG44 )
std::vector<OracleEntry>{
    { LifeType_None,      1,  20,  "None"},
    { LifeType_Extinct,   21, 40,  "Extinct" },
    { LifeType_Scarce,    41, 70,  "Scarce" },
    { LifeType_Diverse,   71, 90,  "Diverse" },
    { LifeType_Bountiful, 91, 97,  "Bountiful" },
    { LifeType_Overrun,   98, 100, "Overrun" },
},
} };

std::array<std::array<std::vector<OracleEntryND>,3>, 18> biomeDiversityTable{ {
    {{
            // PlanetType_Furnace ( PG52 )
            std::vector<OracleEntryND>{
                { 1, 1,  75},
                { 2, 76, 90},
                { 3, 91, 100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  20},
                { 2, 21, 50},
                { 3, 51, 100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  10},
                { 2, 11, 25},
                { 3, 26, 100},
            },
    }},
    {{
    // PlanetType_Desert ( PG50 )
            std::vector<OracleEntryND>{
                { 1, 1,  45},
                { 2, 46, 75},
                { 3, 76, 90},
                { 4, 91, 98},
                { 5, 99, 100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  10},
                { 2, 11, 25},
                { 3, 26, 45},
                { 4, 46, 70},
                { 5, 71, 100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  2},
                { 2, 3,  10}, 
                { 3, 11, 25},
                { 4, 26, 55},
                { 5, 56, 100},
            },
    }},
    {{
    // PlanetType_Jungle ( PG60 )
            std::vector<OracleEntryND>{
                { 1, 1,  45},
                { 2, 46, 75},
                { 3, 76, 90},
                { 4, 91, 98},
                { 5, 99, 100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  10},
                { 2, 11, 25},
                { 3, 26, 45},
                { 4, 46, 70},
                { 5, 71, 100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  2},
                { 2, 3,  10},
                { 3, 11, 25},
                { 4, 26, 55},
                { 5, 56, 100},
            },
    }},
    {{
    // PlanetType_Vital ( PG80 )
            std::vector<OracleEntryND>{
                { 3, 1,  10},
                { 4, 11,  25},
                { 5, 26, 50},
                { 6, 51, 85},
                { 7, 86, 95},
                { 8, 96, 100},
            },
            std::vector<OracleEntryND>{
                { 4, 1,  10},
                { 5, 11, 25},
                { 6, 26, 65},
                { 7, 66, 90},
                { 8, 91, 100},
            },
            std::vector<OracleEntryND>{
                { 5, 3,  10},
                { 6, 11, 55},
                { 7, 56, 85},
                { 8, 86, 100},
            },
    }},
    {{
    // PlanetType_Ocean ( PG70 )
            std::vector<OracleEntryND>{
                { 1, 1,  45},
                { 2, 46, 75},
                { 3, 76, 90},
                { 4, 91, 98},
                { 5, 99, 100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  10},
                { 2, 11, 25},
                { 3, 26, 45},
                { 4, 46, 70},
                { 5, 71, 100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  2},
                { 2, 3,  10},
                { 3, 11, 25},
                { 4, 26, 55},
                { 5, 56, 100},
            },
    }},
    {{
    // PlanetType_Ice ( PG56 )
            std::vector<OracleEntryND>{
                { 1, 1,  45},
                { 2, 46, 75},
                { 3, 76, 90},
                { 4, 91, 98},
                { 5, 99, 100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  10},
                { 2, 11, 25},
                { 3, 26, 45},
                { 4, 46, 70},
                { 5, 71, 100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  2},
                { 2, 3,  10},
                { 3, 11, 25},
                { 4, 26, 55},
                { 5, 56, 100},
            },
    }},
    {{
    // PlanetType_Chemical ( PG46 )
            std::vector<OracleEntryND>{
                { 1, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  100},
            },
    } },
    { {
    // PlanetType_Jovian ( PG58 )
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
    } },
    { {
    // PlanetType_Rocky ( PG72 )
            std::vector<OracleEntryND>{
                { 1, 1,  75},
                { 2, 76, 95},
                { 3, 96, 100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  25},
                { 2, 26, 75},
                { 3, 76, 100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  15},
                { 2, 16, 50},
                { 3, 51, 100},
            },
    } },
    { {
    // PlanetType_Tainted ( PG76 )
            std::vector<OracleEntryND>{
                { 1, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 1, 1,  100},
            },
    } },
    { {
    // PlanetType_Metallic ( PG68 )
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
    } },
    { {
    // PlanetType_Crystalline ( PG48 )
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
    } },
    { {
    // PlanetType_TidallyLocked ( PG79 sort of) 
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
    } },
    { {
    // PlanetType_Karst ( PG63, sort of )
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
    } },
    { {
    // PlanetType_Grave ( PG54 )
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
    } },
    { {
    // PlanetType_Shattered ( PG74 )
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
    } },
    { {
    // PlanetType_Living ( PG64 )
            std::vector<OracleEntryND>{
                { 2, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 2, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 2, 1,  100},
            },
    } },
    { {
    // PlanetType_Anomalous ( PG44 )
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
            std::vector<OracleEntryND>{
                { 0, 1,  100},
            },
    } },
} };

//: Biome Order
std::array<std::vector<int>, 18> BiomesOrderTable{ {
        // PlanetType_Furnace ( PG52 )
        std::vector<int>{0,1,2},
        // PlanetType_Desert ( PG50 )
        std::vector<int>{0,1,2,3,4,5,6,7},
        // PlanetType_Jungle ( PG60 )
        std::vector<int>{0,1,2,3,4,5,6,7},
        // PlanetType_Vital ( PG80 )
        std::vector<int>{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38}, 
        // PlanetType_Ocean ( PG70 )
        std::vector<int>{0,1,2,3,4,5},
        // PlanetType_Ice ( PG56 )
        std::vector<int>{0,1,2,3,4,5,6,7},
        // PlanetType_Chemical ( PG46 )
        std::vector<int>{0,1,2,3,4,5},
        // PlanetType_Jovian ( PG58 )
        std::vector<int>{},
        // PlanetType_Rocky ( PG72 )
        std::vector<int>{0,1,2,3,4},
        // PlanetType_Tainted ( PG76 )
        std::vector<int>{0,1,2},
        // PlanetType_Metallic ( PG68 )
        std::vector<int>{},
        // PlanetType_Crystalline ( PG48 )
        std::vector<int>{},
        // PlanetType_TidallyLocked ( PG79 sort of) 
        std::vector<int>{},
        // PlanetType_Karst ( PG63, sort of )
        std::vector<int>{},
        // PlanetType_Grave ( PG54 )
        std::vector<int>{},
        // PlanetType_Shattered ( PG74 )
        std::vector<int>{},
        // PlanetType_Living ( PG64 )
        std::vector<int>{0,1},
        // PlanetType_Anomalous ( PG44 )
        std::vector<int>{},
} };

std::array<std::vector<biomeOracle>, 18> BiomesTable{ {
        // PlanetType_Furnace ( PG52 )
        std::vector<biomeOracle>{
            {PlanetType_Furnace, 0, "Ash"},
            {PlanetType_Furnace, 1, "Hothouse"},
            {PlanetType_Furnace, 2, "Volcanic" },
        },
        // PlanetType_Desert ( PG50 )
        std::vector<biomeOracle>{
            {PlanetType_Desert, 0, "Badlands"},
            {PlanetType_Desert, 1, "Dune"},
            {PlanetType_Desert, 2, "Mesa" },
            {PlanetType_Desert, 3, "Oasis"},
            {PlanetType_Desert, 4, "Salt Flat"},
            {PlanetType_Desert, 5, "Semi-arid" },
            {PlanetType_Desert, 6, "Steppe"},
            {PlanetType_Desert, 7, "Veld"},
        },
        // PlanetType_Jungle ( PG60 )
        std::vector<biomeOracle>{
            {PlanetType_Jungle, 0, "Bioluminescent"},
            {PlanetType_Jungle, 1, "Cenote"},
            {PlanetType_Jungle, 2, "Forest" },
            {PlanetType_Jungle, 3, "Megaflora"},
            {PlanetType_Jungle, 4, "Petrified Forest"},
            {PlanetType_Jungle, 5, "Rainforest" },
            {PlanetType_Jungle, 6, "Swamp"},
            {PlanetType_Jungle, 7, "Tepui"},
        },
        // PlanetType_Vital ( PG80 )
            std::vector<biomeOracle>{
            {PlanetType_Desert, 0, "Badlands"},
            {PlanetType_Desert, 1, "Dune"},
            {PlanetType_Desert, 2, "Mesa" },
            {PlanetType_Desert, 3, "Oasis"},
            {PlanetType_Desert, 4, "Salt Flat"},
            {PlanetType_Desert, 5, "Semi-arid" },
            {PlanetType_Desert, 6, "Steppe"},
            {PlanetType_Furnace, 0, "Ash"},
            {PlanetType_Furnace, 2, "Volcanic" },
            {PlanetType_Ice, 0, "Cryoflora"},
            {PlanetType_Ice, 1, "Frigid"},
            {PlanetType_Ice, 2, "Geothermal" },
            {PlanetType_Ice, 3, "Glacial"},
            {PlanetType_Ice, 4, "Glaciovolcanic"},
            {PlanetType_Ice, 5, "Iceberg" },
            {PlanetType_Ice, 6, "Snow"},
            {PlanetType_Ice, 7, "Subglacial"},
            {PlanetType_Jungle, 2, "Forest" },
            {PlanetType_Jungle, 3, "Megaflora"},
            {PlanetType_Jungle, 4, "Petrified Forest"},
            {PlanetType_Jungle, 5, "Rainforest" },
            {PlanetType_Jungle, 6, "Swamp"},
            {PlanetType_Jungle, 7, "Tepui"},
            {PlanetType_Ocean, 0, "Archipelago"},
            {PlanetType_Ocean, 1, "Atoll"},
            {PlanetType_Ocean, 2, "Crag" },
            {PlanetType_Ocean, 3, "Hycean"},
            {PlanetType_Ocean, 4, "Mangrove"},
            {PlanetType_Ocean, 5, "Reef" },
            {PlanetType_Rocky, 1, "Basalt"},
            {PlanetType_Rocky, 3, "Bog"},
            {PlanetType_Rocky, 4, "Mud"},
            {PlanetType_Tainted, 0, "Hive"},
            {PlanetType_Tainted, 1, "Mutagenic"},
            {PlanetType_Tainted, 2, "Mycelium" },
            {PlanetType_Vital, 0, "Grassland"},
            {PlanetType_Vital, 1, "Jungle"},
            {PlanetType_Vital, 2, "Savanna"},
            {PlanetType_Vital, 3, "Taiga" },
        },
        
        // PlanetType_Ocean ( PG70 )
        std::vector<biomeOracle>{
            {PlanetType_Ocean, 0, "Archipelago"},
            {PlanetType_Ocean, 1, "Atoll"},
            {PlanetType_Ocean, 2, "Crag" },
            {PlanetType_Ocean, 3, "Hycean"},
            {PlanetType_Ocean, 4, "Mangrove"},
            {PlanetType_Ocean, 5, "Reef" },
        },
        // PlanetType_Ice ( PG56 )
        std::vector<biomeOracle>{
            {PlanetType_Ice, 0, "Cryoflora"},
            {PlanetType_Ice, 1, "Frigid"},
            {PlanetType_Ice, 2, "Geothermal" },
            {PlanetType_Ice, 3, "Glacial"},
            {PlanetType_Ice, 4, "Glaciovolcanic"},
            {PlanetType_Ice, 5, "Iceberg" },
            {PlanetType_Ice, 6, "Snow"},
            {PlanetType_Ice, 7, "Subglacial"},
        },
        // PlanetType_Chemical ( PG46 )
            std::vector<biomeOracle>{
            {PlanetType_Chemical, 0, "Acid"},
            {PlanetType_Chemical, 1, "Ammonia"},
            {PlanetType_Chemical, 2, "Ethane" },
            {PlanetType_Chemical, 3, "Hydrocarbon"},
            {PlanetType_Chemical, 4, "Methane"},
            {PlanetType_Chemical, 5, "Sulfur" },
        },

        // PlanetType_Jovian ( PG58 )
        std::vector<biomeOracle>{},
        // PlanetType_Rocky ( PG72 )
        std::vector<biomeOracle>{
            {PlanetType_Rocky, 0, "Aeolian"},
            {PlanetType_Rocky, 1, "Basalt"},
            {PlanetType_Rocky, 2, "Bleak" },
            {PlanetType_Rocky, 3, "Bog"},
            {PlanetType_Rocky, 4, "Mud"},
        },

        // PlanetType_Tainted ( PG76 )
        std::vector<biomeOracle>{
            {PlanetType_Tainted, 0, "Hive"},
            {PlanetType_Tainted, 1, "Mutagenic"},
            {PlanetType_Tainted, 2, "Mycelium" },
        },
        // PlanetType_Metallic ( PG68 )
        std::vector<biomeOracle>{},
        // PlanetType_Crystalline ( PG48 )
        std::vector<biomeOracle>{},
        // PlanetType_TidallyLocked ( PG79 sort of) 
        std::vector<biomeOracle>{},
        // PlanetType_Karst ( PG63, sort of )
        std::vector<biomeOracle>{},
        // PlanetType_Grave ( PG54 )
        std::vector<biomeOracle>{},
        // PlanetType_Shattered ( PG74 )
        std::vector<biomeOracle>{},
        // PlanetType_Living ( PG64 )
        std::vector<biomeOracle>{
            {PlanetType_Living, 0, "Epidermis"},
            { PlanetType_Living, 1, "Periosteum"},
        },
        // PlanetType_Anomalous ( PG44 )
        std::vector<biomeOracle>{},
} };

std::array<std::vector<std::vector<OracleEntry>>, 18> BiomeFeatureTable{ {
    {
        { //{PlanetType_Furnace, 0, "Ash"},
            {0, 1, 7, "Ashen dunes"},
            {1, 8, 14, "Blackened and scorched rock faces"},
            {2, 15, 21, "Blinding ashstorms"},
            {3, 22, 28, "Carbonized flora"},
            {4, 29, 35, "Dormant volcanoes or calderas"},
            {5, 36, 42, "Expanses of partially solidified magma"},
            {6, 43, 49, "Extensive volcanic fissures"},
            {7, 50, 56, "Frequent and heavy ash fall"},
            {8, 57, 63, "Glowing windborne embers"},
            {9, 64, 70, "Howling and powerful winds"},
            {10, 71, 77, "Lightning-wracked ash clouds"},
            {11, 78, 84, "Raging whirls of fire"},
            {12, 85, 91, "Thick layers of enveloping ash"},
            {13, 92, 100, "Transition into a new >Biome"},
        },
        { //{PlanetType_Furnace, 1, "Hothouse"},
            {0, 1, 7, "Frigid cave systems"},
            {1, 8, 14, "Crumbling or slowly melting surfaces"},
            {2, 15, 21, "Distorting heat-haze"},
            {3, 22, 28, "Fields of pockmarked boulders"},
            {4, 29, 35, "Forests of geothermal vents"},
            {5, 36, 42, "Molten metal or acid rainfall"},
            {6, 43, 49, "Mountains capped with metallic snow"},
            {7, 50, 56, "Searing winds"},
            {8, 57, 63, "Severely weathered cliffs or mountains"},
            {9, 64, 70, "Sheltered chasms or canyons"},
            {10, 71, 77, "Silica or metal storms"},
            {11, 78, 84, "Steaming mudflats"},
            {12, 85, 91, "Unusually colored clouds or sky"},
            {13, 92, 100, "Transition into a new >Biome"},
        },
        { //{PlanetType_Furnace, 1, "Hothouse"},
            {0, 1, 7, "Billowing sulfur vents"},
            {1, 8, 14, "Blazing firestorms"},
            {2, 15, 21, "Enormous lava deltas"},
            {3, 22, 28, "Glowing rivers of lava"},
            {4, 29, 35, "Intricate volcanic rock formations"},
            {5, 36, 42, "Magma seas"},
            {6, 43, 49, "Massive supervolcanoes"},
            {7, 50, 56, "Plains of volcanic glass"},
            {8, 57, 63, "Pools of liquid metal"},
            {9, 64, 70, "Rocky islands adrift on magma"},
            {10, 71, 77, "Smoldering calderas"},
            {11, 78, 84, "Steaming sulfuric lakes or pools"},
            {12, 85, 91, "Violent pyroclastic flows or surges"},
            {13, 92, 100, "Transition into a new >Biome"},

        },
    },

    {
        { //{PlanetType_Desert, 0, "Badlands"},
            {0, 1, 11, "Chaotic whirlwinds"},
            {1, 12, 22, "Distinct rock stratification"},
            {2, 23, 33, "Dry riverbeds"},
            {3, 34, 44, "Eroded mountain ranges"},
            {4, 45, 55, "Fields of brittle shrubs"},
            {5, 56, 66, "Slowly flowing streams"},
            {6, 67, 77, "Timeworn cliffside caves"},
            {7, 78, 88, "Vast concave valleys"},
            {8, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Desert, 1, "Dune"},
            {11, 1, 11, "Buried mountain peaks"},
            {12, 12, 22, "Enormous shifting dunes"},
            {13, 23, 33, "Fleeting springs emerging from the sands"},
            {0, 34, 44, "Landscape-altering flashfloods"},
            {0, 45, 55, "Sands roiling or rippling with static electricity"},
            {0, 56, 66, "Secluded patches of lush vegetation"},
            {0, 67, 77, "Symmetrical dune formations"},
            {0, 78, 88, "Windborne metallic or glimmering sand"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Desert, 2, "Mesa" },
            {0, 1, 11, "Ferocious river rapids"},
            {0, 12, 22, "Huge shrubs and grasses line the river banks"},
            {0, 23, 33, "Intricate networks of carved canyons"},
            {0, 34, 44, "Plateaus bristling with vegetation"},
            {0, 45, 55, "Precariously fragile stone columns"},
            {0, 56, 66, "Secluded grottos"},
            {0, 67, 77, "Slowly collapsing or eroding rock faces"},
            {0, 78, 88, "Vast mesas with tumbling waterfalls"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Desert, 3, "Oasis"},
            {0, 1, 11, "Colossal freshwater pools, lakes or rivers"},
            {0, 12, 22, "Devastating floodwaters"},
            {0, 23, 33, "Drifting fog or mist"},
            {0, 34, 44, "Expansive and partially flooded caves"},
            {0, 45, 55, "Frequent rainfall turns the terrain to mud"},
            {0, 56, 66, "Lush and incredibly dense vegetation"},
            {0, 67, 77, "Sprawling river deltas"},
            {0, 78, 88, "Strong and cool breezes"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Desert, 4, "Salt Flat"},
            {0, 1, 11, "Cavernous sinkholes or chasms"},
            {0, 12, 22, "Distorting and unending heat wave"},
            {0, 23, 33, "Dry and cracked seabeds"},
            {0, 34, 44, "Salt carried by harsh and dry winds"},
            {0, 45, 55, "Large crystal formations"},
            {0, 56, 66, "Monolithic pillars of condensed salt"},
            {0, 67, 77, "Petrified coral reefs or forests"},
            {0, 78, 88, "Pools of briny water"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Desert, 5, "Semi-arid" },
            {0, 1, 11, "Canyons spanned by natural stone bridges"},
            {0, 12, 22, "Caves and grottos littering canyon walls"},
            {0, 23, 33, "Narrow outcrops through steep-sided ravine"},
            {0, 34, 44, "Steep gorges surround abyssal rivers"},
            {0, 45, 55, "Subsurface tunnel or cave networks"},
            {0, 56, 66, "Ubiquitous vegetation concentrated around rivers"},
            {0, 67, 77, "Violent electrical storms"},
            {0, 78, 88, "Whistling winds"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Desert, 6, "Steppe"},
            {0, 1, 11, "Enormous stone arches"},
            {0, 12, 22, "Fleeting rainstorms and flash floods"},
            {0, 23, 33, "Flooded grottos"},
            {0, 34, 44, "Labyrinthine and sloped wind-carved spires"},
            {0, 45, 55, "Powerful howling winds"},
            {0, 56, 66, "Vast shrublands obscure the desert"},
            {0, 67, 77, "Water pools expose aquifers or springs"},
            {0, 78, 88, "Waterways rapidly alter the terrain"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Desert, 7, "Veld"},
            {0, 1, 11, "Colossal remnants of dead or petrified groves"},
            {0, 12, 22, "Dry lakebeds"},
            {0, 23, 33, "Enormous isolated mountain"},
            {0, 34, 44, "Gentle or light breezes"},
            {0, 45, 55, "Large pockets of dense grasses and hardy trees"},
            {0, 56, 66, "Parched riverbeds"},
            {0, 67, 77, "Small lagoons or streams"},
            {0, 78, 88, "Sporadic curtains of rainfall"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
    },

    {
        { //{PlanetType_Jungle, 0, "Bioluminescent"},
            {2, 1, 11, "Color-shifting vegetation"},
            {3, 12, 22, "Eerily glowing underbrush"},
            {4, 23, 33, "Phosphorescent flowers"},
            {5, 34, 44, "Huge leaves or petals"},
            {6, 45, 55, "Cloud-breaching mountains capped with flora"},
            {7, 56, 66, "Fields of iridescent moss or lichen"},
            {8, 67, 77, "Mobile forests tracking sunlight"},
            {9, 78, 88, "Shimmering fogs"},
            {10, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Desert, 1, "Dune"},
            {13, 1, 11, "Bioluminescent flora"},
            {0, 12, 22, "Cascading waterfalls"},
            {0, 23, 33, "Colossal cavern networks"},
            {0, 34, 44, "Flooded caves"},
            {0, 45, 55, "Huge stalagmites, stalactites or columns"},
            {0, 56, 66, "Low-lying fogs"},
            {0, 67, 77, "Plunging sinkholes"},
            {0, 78, 88, "Underground seas and lakes"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Jungle, 2, "Forest" },
            {0, 1, 11, "Dense barbed thickets"},
            {0, 12, 22, "Fragrant trees and grasses"},
            {0, 23, 33, "Frequent drizzles"},
            {0, 34, 44, "Rolling hills enveloped by forests"},
            {0, 45, 55, "Scarred clearings"},
            {0, 56, 66, "Segmented tree crowns"},
            {0, 67, 77, "Thick underbrush of ferns and shrubs"},
            {0, 78, 88, "Vibrant flowering glades"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Jungle, 3, "Megaflora"},
            {0, 1, 11, "Canopy-enveloping fog"},
            {0, 12, 22, "Cloud-breaching trees"},
            {0, 23, 33, "Enormous toppled trees"},
            {0, 34, 44, "Expansive rivers or pools"},
            {0, 45, 55, "Extensive exposed root systems"},
            {0, 56, 66, "Immense hollow trunks"},
            {0, 67, 77, "Sky-bridges formed by intertwined branches"},
            {0, 78, 88, "Unbroken canopy"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Jungle, 4, "Petrified Forest"},
            {0, 1, 11, "Ancient river beds"},
            {0, 12, 22, "Boulder fields formed by collapsed trees"},
            {0, 23, 33, "Crumbling megaflora form hills or mountains"},
            {0, 34, 44, "Dense expanses of column-like trunks"},
            {0, 45, 55, "Eerily still winds"},
            {0, 56, 66, "Flora enveloping crystal formations"},
            {0, 67, 77, "Sparse groves of enduring flora"},
            {0, 78, 88, "Vivid mineral coloration"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Jungle, 5, "Rainforest" },
            {0, 1, 11, "Dense and low-lying mist"},
            {0, 12, 22, "Distinctly segregated tree canopies"},
            {0, 23, 33, "Grottos obscured by dangling vines"},
            {0, 34, 44, "Monstrous monsoons"},
            {0, 45, 55, "Oppressive heat waves"},
            {0, 56, 66, "Powerful rivers"},
            {0, 67, 77, "Thick impasses of hanging vines"},
            {0, 78, 88, "Whispering winds"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Jungle, 6, "Swamp"},
            {0, 1, 11, "Bubbling ooze pools"},
            {0, 12, 22, "Enormous lilypads"},
            {0, 23, 33, "Fetid mists"},
            {0, 34, 44, "Foul mire expanses"},
            {0, 45, 55, "Murky flooded sinkholes"},
            {0, 56, 66, "Roiling toxic miasma"},
            {0, 67, 77, "Sinking quagmires"},
            {0, 78, 88, "Small islets amidst the waters"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Jungle, 7, "Tepui"},
            {0, 1, 11, "Deep river gorges"},
            {0, 12, 22, "Fog or mist cascades from the mountain tops"},
            {0, 23, 33, "Massive canyons or caves"},
            {0, 34, 44, "Megalithic plateaus"},
            {0, 45, 55, "Stretches of grassy plains"},
            {0, 56, 66, "Surging rivers"},
            {0, 67, 77, "Towering waterfalls"},
            {0, 78, 88, "Columns wreathed in flora"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
    },

    {
        { //{PlanetType_Vital, 0, "Grassland"},
            {2, 1, 11, "Fern or shrub thickets"},
            {3, 12, 22, "Frequent rainfall"},
            {4, 23, 33, "Isolated mountains or cavemouths"},
            {5, 34, 44, "Meandering streams or rivers"},
            {6, 45, 55, "Regions of obfuscating grasses"},
            {7, 56, 66, "Small groves of trees"},
            {8, 67, 77, "Still or misty lakes"},
            {9, 78, 88, "Vividly colored flowers"},
            {10, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Vital, 1, "Jungle"},
            {13, 1, 11, "Concealed caves or sinkholes"},
            {0, 12, 22, "Enormous canopy-breaching trees"},
            {0, 23, 33, "Impasses of vines and underbrush"},
            {0, 34, 44, "Impenetrable, opaque canopy"},
            {0, 45, 55, "Mountains engulfed by flora"},
            {0, 56, 66, "Powerful rivers or waterfalls"},
            {0, 67, 77, "Rocky, moss-covered clearings"},
            {0, 78, 88, "Secluded streams or pools"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Vital, 2, "Savanna"},
            {0, 1, 11, "Dense clusters of trees"},
            {0, 12, 22, "Enormous and remote mountains"},
            {0, 23, 33, "Expanses of sand and desiccated shrubs"},
            {0, 34, 44, "Green and fertile regions"},
            {0, 45, 55, "Lakes enclosed by dense vegetation"},
            {0, 56, 66, "Parched or overflowing rivers"},
            {0, 67, 77, "Powerful monsoons"},
            {0, 78, 88, "Remnants of dead or petrified trees"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Vital, 3, "Taiga" },
            {0, 1, 11, "Deep snowpack"},
            {0, 12, 22, "Expanse of snow-covered trees"},
            {0, 23, 33, "Frosted or snowy clearings"},
            {0, 34, 44, "Glittering snowfall"},
            {0, 45, 55, "Icy or frozen waterways"},
            {0, 56, 66, "Rocky hills covered by hardy flora"},
            {0, 67, 77, "Shrouded crevasses or caves"},
            {0, 78, 88, "Snow-capped mountain range"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
    },

    {
        { //{PlanetType_Ocean, 0, "Archipelago"},
            {2, 1, 9, "Eerily glowing subsurface volcanoes"},
            {3, 10, 18, "Emerging or active volcanoes"},
            {4, 19, 27, "Enormous pillars of volcanic rock"},
            {5, 28, 36, "Isolated mountains or gorges"},
            {6, 37, 45, "Partially flooded sea caves"},
            {7, 46, 54, "Picturesque beaches"},
            {8, 55, 63, "Plant laden islets"},
            {9, 64, 72, "Pools of bubbling lava"},
            {10, 73, 81, "Recurring rainstorms"},
            {11, 82, 90, "Sandbar bridges"},
            {12, 91, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Ocean, 1, "Atoll"},
            {0, 1, 9, "Abyssal deep water basins"},
            {0, 10, 18, "Complex reef systems"},
            {0, 19, 27, "Crystalline waters"},
            {0, 28, 36, "Enormous sand or pebble beaches"},
            {0, 37, 45, "Fierce undertows"},
            {0, 46, 54, "Numerous concentric atolls"},
            {0, 55, 63, "Sand dunes laden with hardy grasses"},
            {0, 64, 72, "Scattered verdant groves"},
            {0, 73, 81, "Shallow sandy plains"},
            {0, 82, 90, "Sprawling rocky shingles"},
            {0, 91, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Ocean, 2, "Crag" },
            {0, 1, 9, "Deep tidal pools"},
            {0, 10, 18, "Isolated patches of lush vegetation"},
            {0, 19, 27, "Powerful geysers"},
            {0, 28, 36, "Powerful howling winds"},
            {0, 37, 45, "Precipitous mountain ranges"},
            {0, 46, 54, "Razor-sharp coastal rock formations"},
            {0, 55, 63, "Sheltered coves"},
            {0, 64, 72, "Towering rock arches"},
            {0, 73, 81, "Violent currents"},
            {0, 82, 90, "Wave-wracked jagged cliffs"},
            {0, 91, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Ocean, 3, "Hycean"},
            {0, 1, 9, "Current-bound maelstroms"},
            {0, 10, 18, "Enormous fog banks"},
            {0, 19, 27, "Expanses of floating oceanic plants and debris"},
            {0, 28, 36, "Floating forests"},
            {0, 37, 45, "Regions of opaque waters"},
            {0, 46, 54, "Roaming icebergs or islets"},
            {0, 55, 63, "Shallow-water plains"},
            {0, 64, 72, "Titanic waves"},
            {0, 73, 81, "Turbulent winds and choppy seas"},
            {0, 82, 90, "Windborne waterspouts"},
            {0, 91, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Ocean, 4, "Mangrove"},
            {0, 1, 9, "Cascading waterfalls"},
            {0, 10, 18, "Continual tidal flooding"},
            {0, 19, 27, "Dense swampy underbrush"},
            {0, 28, 36, "Labyrinthine mangrove thickets"},
            {0, 37, 45, "Monolithic plateau-capped mountains"},
            {0, 46, 54, "Roiling and pervasive mists"},
            {0, 55, 63, "Saltmarsh sloughs"},
            {0, 64, 72, "Tiny islets surrounded by immense mangroves"},
            {0, 73, 81, "Unrelenting heatwaves"},
            {0, 82, 90, "Vast deposits of congealing mud"},
            {0, 91, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Ocean, 5, "Reef" },
            {0, 1, 9, "Desiccated and crumbling terrain"},
            {0, 10, 18, "Enormous algae blooms"},
            {0, 19, 27, "Harsh, salt-laden winds"},
            {0, 28, 36, "Intricate networks of tunnels"},
            {0, 37, 45, "Prodigious island-like sponges"},
            {0, 46, 54, "Salt-dusted surfaces"},
            {0, 55, 63, "Shoals enveloped with bioluminescent plants"},
            {0, 64, 72, "Thick and briny coastal waters"},
            {0, 73, 81, "Towering spires or mountains of coral"},
            {0, 82, 90, "Vast corals forming an island chain"},
            {0, 91, 100, "Transition into a new >Biome"},

        },
    },

    {
        { //{PlanetType_Ice, 0, "Cryoflora"},
            {2, 1, 11, "Clusters of monolithic crystals"},
            {3, 12, 22, "Glistening spires covered in vine-like growths"},
            {4, 23, 33, "Huge flora sprawling across mountainsides"},
            {5, 34, 44, "Rocky outcrops sheltering hardy grasses"},
            {6, 45, 55, "Towering groves"},
            {7, 56, 66, "Undulating clouds of mist"},
            {8, 67, 77, "Vast subsurface liquid seas"},
            {9, 78, 88, "Vibrant plants emerging from frozen water pools"},
            {10, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Ice, 1, "Frigid"},
            {13, 1, 11, "Acute howling winds"},
            {0, 12, 22, "Boulder fields covered in ice"},
            {0, 23, 33, "Cracked rocky plains"},
            {0, 34, 44, "Craggy or crumbling mountainsides"},
            {0, 45, 55, "Frosted and misty pools"},
            {0, 56, 66, "Frosted caves"},
            {0, 67, 77, "Jagged mountain ranges"},
            {0, 78, 88, "Streams littered with broken ice"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Ice, 2, "Geothermal" },
            {0, 1, 11, "Bubbling lakes expelling steam"},
            {0, 12, 22, "Distorting heat haze"},
            {0, 23, 33, "Fissures erupting with smoke or gas"},
            {0, 34, 44, "Isolated geysers billowing steam"},
            {0, 45, 55, "Pools surrounded by hardy grasses and ferns"},
            {0, 56, 66, "Rocky moss-covered islands amid icy wastes"},
            {0, 67, 77, "Showers of hailstones or sleet"},
            {0, 78, 88, "Steaming hot springs"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Ice, 3, "Glacial"},
            {0, 1, 11, "Exalted icy fjords"},
            {0, 12, 22, "Frozen lakes connected by frigid waterfalls"},
            {0, 23, 33, "Frozen oceans"},
            {0, 34, 44, "Hidden crevasses"},
            {0, 45, 55, "Imposing walls or columns of ice"},
            {0, 56, 66, "Perpetual heavy snowfall"},
            {0, 67, 77, "Raging cold winds"},
            {0, 78, 88, "Windborne glittering ice crystals"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Ice, 4, "Glaciovolcanic"},
            {0, 1, 11, "Actively forming mountain ranges"},
            {0, 12, 22, "Bubbling magma pools"},
            {0, 23, 33, "Enormous roiling magma"},
            {0, 34, 44, "Foreboding calderas"},
            {0, 45, 55, "Networks of subsurface lava"},
            {0, 56, 66, "Rivers of meltwater"},
            {0, 67, 77, "Supersized ice volcanoes"},
            {0, 78, 88, "Volcanoes billowing smoke"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Ice, 5, "Iceberg" },
            {0, 1, 11, "Abyssally deep oceans"},
            {0, 12, 22, "Briny underwater rivers and currents"},
            {0, 23, 33, "Colonies of saltwater kelp thrives"},
            {0, 34, 44, "Fleeting hurricanes"},
            {0, 45, 55, "Powerful storms and surging winds"},
            {0, 56, 66, "Roaming packs of enormous icebergs"},
            {0, 67, 77, "Rocky glacial islands"},
            {0, 78, 88, "Shattered plains of pack ice"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Ice, 6, "Snow"},
            {0, 1, 11, "Drifting thick fog"},
            {0, 12, 22, "Enormous snowcapped mountain"},
            {0, 23, 33, "Lowlands filled with small pools of water"},
            {0, 34, 44, "Massive snow drifts"},
            {0, 45, 55, "Shifting snow dunes"},
            {0, 56, 66, "Snow-covered mountain range"},
            {0, 67, 77, "Snow-topped boreal woods"},
            {0, 78, 88, "Windswept smooth glaciers"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Ice, 7, "Subglacial"},
            {0, 1, 11, "Abyssal ice fissures reveals ocean"},
            {0, 12, 22, "Cavernous subsurface tunnel networks"},
            {0, 23, 33, "Colossal ice caves"},
            {0, 34, 44, "Extensive crevasses sheltering thin lakes"},
            {0, 45, 55, "Pockets of gas or liquid encased in ice"},
            {0, 56, 66, "Sky-breaching geysers"},
            {0, 67, 77, "Tidal heating cracks surface"},
            {0, 78, 88, "Titanic ice canyons"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
    },

    {
        { //{PlanetType_Chemical, 0, "Acid"},
            {2, 1, 10, "Abraded and crumbling stone spires"},
            {3, 11, 20, "Densely pockmarked rocky plains"},
            {4, 21, 30, "Fizzing caustic rivers"},
            {5, 31, 40, "Heavily dissolved and eroded mountains"},
            {6, 41, 50, "Intensely corrosive rainfall"},
            {7, 51, 60, "Mordant or blistering winds"},
            {8, 61, 70, "Mountains eroded by acidic snow"},
            {9, 71, 80, "Pools of dissolved metal"},
            {10, 81, 90, "Vapor effusing seas or lakes"},
            {11, 91, 100, "Volatile bubbling pools"},

        },
        {  //{PlanetType_Chemical, 1, "Ammonia"},
            {0, 1, 10, "Abyssal ice fissures"},
            {0, 11, 20, "Colossal tunnel networks"},
            {0, 21, 30, "Frigid seas roamed by colossal icebergs"},
            {0, 31, 40, "Frosted plains of gravel or stone"},
            {0, 41, 50, "Geothermally heated pools"},
            {0, 51, 60, "Imposing walls or columns of ice"},
            {0, 61, 70, "Powerful storms and surging winds"},
            {0, 71, 80, "Rocky plateaus bordered by icy plains"},
            {0, 81, 90, "Shattered plains of packed ice"},
            {0, 91, 100, "Sky-breaching geysers"},

        },
        { //{PlanetType_Chemical, 2, "Ethane" },
            {0, 1, 10, "Expanses of floating silt or mud"},
            {0, 11, 20, "Iridescent surface"},
            {0, 21, 30, "Opaque gaseous fog banks"},
            {0, 31, 40, "Powerful thunderstorms"},
            {0, 41, 50, "Raging hurricanes"},
            {0, 51, 60, "Roaming ethanolic spots"},
            {0, 61, 70, "Roaming icebergs or islets"},
            {0, 71, 80, "Shallow subsurface plains"},
            {0, 81, 90, "Titanic waves"},
            {0, 91, 100, "Turbulent winds and choppy seas"},

        },
        { //{PlanetType_Chemical, 3, "Hydrocarbon"},
            {0, 1, 10, "Blustering winds"},
            {0, 11, 20, "Cavernous sinkholes or fissures"},
            {0, 21, 30, "Enormous mountain ranges"},
            {0, 31, 40, "Fields of imposing rocky spires"},
            {0, 41, 50, "Flatlands littered with ice"},
            {0, 51, 60, "Frequent and heavy rainfall"},
            {0, 61, 70, "Rivers littered with broken ice"},
            {0, 71, 80, "Streams spanning cracked rocky plains"},
            {0, 81, 90, "Valleys carved megalithic glaciers"},
            {0, 91, 100, "Vast misty lakes"},

        },
        { //{PlanetType_Chemical, 4, "Methane"},
            {0, 1, 10, "Enormous stone arches"},
            {0, 11, 20, "Frosted sandy plains"},
            {0, 21, 30, "Glistening snow-crowned dunes"},
            {0, 31, 40, "Glittering rivers or streams"},
            {0, 41, 50, "Huge shimmering pools"},
            {0, 51, 60, "Icy lakes rimmed by gravel shores"},
            {0, 61, 70, "Intricate networks of canyons"},
            {0, 71, 80, "Looming rocky plateaus"},
            {0, 81, 90, "Stratified methanofalls"},
            {0, 91, 100, "Towering snowcapped mountains"},

        },
        { //{PlanetType_Chemical, 5, "Sulfur" },
            {0, 1, 10, "Colorful geothermal springs"},
            {0, 11, 20, "Dense forests of volcanic vents"},
            {0, 21, 30, "Eroded and vibrantly colored shores"},
            {0, 31, 40, "Massive supervolcanoes"},
            {0, 41, 50, "Networks of flooded lava tubes"},
            {0, 51, 60, "Plains of solidified volcanic rock"},
            {0, 61, 70, "Powerfully corrosive pools or lakes"},
            {0, 71, 80, "Scalding geysers"},
            {0, 81, 90, "Sky-breaching plumes of volcanic gases"},
            {0, 91, 100, "Submerged and bubbling calderas"},

        },
    },
    
    { {} }, // PlanetType_Jovian ( PG58 )

    {
        { //{PlanetType_Rocky, 0, "Aeolian"},
            {2, 1, 8, "Barren plateaus atop towering stone arches"},
            {3, 9, 16, "Canyon walls heavily perforated by caves"},
            {4, 17, 24, "Chasms connected by slot canyons or gorges"},
            {5, 25, 32, "Giant bridge-like stone formations"},
            {6, 33, 40, "Hurricane-like winds"},
            {7, 41, 48, "Rock faces lined by ore veins"},
            {8, 49, 56, "Shallow frozen or liquid oceans"},
            {9, 57, 64, "Sheltered lakes encircled by vegetation"},
            {10, 65, 72, "Towering rocky spires"},
            {11, 73, 80, "Wind-twisted rock formations"},
            {12, 81, 88, "Wind-wracked slopes or cliff faces"},
            {13, 89, 100, "Transition into a new >Biome"},

        },
        {  //{PlanetType_Rocky, 1, "Basalt"},
            {0, 1, 8, "Billowing winds carrying disturbed ash"},
            {0, 9, 16, "Enormous pillars of volcanic rock or obsidian"},
            {0, 17, 24, "Glowing sinkholes"},
            {0, 25, 32, "Isolated blooms of flora"},
            {0, 33, 40, "Isolated volcanoes billowing smoke and ash"},
            {0, 41, 48, "Labyrinthine networks of lava tubes"},
            {0, 49, 56, "Obsidian glass riverbeds"},
            {0, 57, 64, "Rubble-strewn lava fields"},
            {0, 65, 72, "Steam-heated caves"},
            {0, 73, 80, "Subsurface magma flows"},
            {0, 81, 88, "Thick layers of enveloping ash"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Rocky, 2, "Bleak" },
            {0, 1, 8, "Abyssal chasms or rifts"},
            {0, 9, 16, "Barren plains"},
            {0, 17, 24, "Blinding dust storms"},
            {0, 25, 32, "Blustering dust devils"},
            {0, 33, 40, "Cavernous sinkholes or fissures"},
            {0, 41, 48, "Fields of imposing rocky spires"},
            {0, 49, 56, "Flatlands scarred by impact craters"},
            {0, 57, 64, "Massive dust dunes"},
            {0, 65, 72, "Plains strewn with enormous boulders"},
            {0, 73, 80, "Visible tectonic plate boundaries"},
            {0, 81, 88, "Wastelands of rocky rubble"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Rocky, 3, "Bog"},
            {0, 1, 8, "Enormous obscuring grasses or reeds"},
            {0, 9, 16, "Expanses of swallowing sludge"},
            {0, 17, 24, "Flooded chasms or canyons"},
            {0, 25, 32, "Incessant rainfall"},
            {0, 33, 40, "Large and motionless lakes"},
            {0, 41, 48, "Rocky outcrops enveloped by moss or grass"},
            {0, 49, 56, "Small groves surrounded by murky pools"},
            {0, 57, 64, "Sprawling unmarred grasslands"},
            {0, 65, 72, "Submerged and preserved remains"},
            {0, 73, 80, "Thick and unmoving fogs"},
            {0, 81, 88, "Undulating mists"},
            {0, 89, 100, "Transition into a new >Biome"},

        },
        { //{PlanetType_Rocky, 4, "Mud"},
            {0, 1, 8, "Bubbling and grimy geothermal springs"},
            {0, 9, 16, "Flooded or submerged caves"},
            {0, 17, 24, "Geysers erupting mud or water"},
            {0, 25, 32, "Massive extinct calderas"},
            {0, 33, 40, "Meandering mudflows"},
            {0, 41, 48, "Murky seas or lakes"},
            {0, 49, 56, "Partially submerged skeletal remains"},
            {0, 57, 64, "Plains of dry and cracked mud"},
            {0, 65, 72, "Rocky outcrops bordered by mudflats"},
            {0, 73, 80, "Steam clouds rising from sodden terrain"},
            {0, 81, 88, "Violent flashfloods or rainfall"},
            {0, 89, 100, "Transition into a new >Biome"},
            {0, 81, 90, "Sky-breaching plumes of volcanic gases"},
            {0, 91, 100, "Submerged and bubbling calderas"},

        },
    },

    {
        { //{PlanetType_Tainted, 0, "Hive"},
            {2, 1, 8, "Crudely-hewn tunnels and caverns"},
            {3, 9, 15, "Enormous parched wastes"},
            {4, 16, 22, "Expanses of putrefying flora"},
            {5, 23, 29, "Isolated or secluded groves"},
            {6, 30, 37, "Mountains pockmarked by caves"},
            {7, 38, 45, "Pools of liquefied organic matter"},
            {8, 46, 53, "Scabrous, infected terrain"},
            {9, 54, 61, "Sinkholes coated with gelatinous fluid"},
            {10, 62, 69, "Sky-breaching chitinous growths"},
            {11, 70, 77, "Sludge-filled river networks"},
            {12, 78, 85, "Terrain marred by fleshy pustules"},
            {13, 86, 93, "Toxic seas"},
            {0, 94, 100, "Viscous, necrotizing lakes"},

        },
        { //{PlanetType_Tainted, 1, "Mutagenic"},
            {0, 1, 8, "Corrosive, low-lying fog"},
            {0, 9, 16, "Deep, crystal-lined canyons"},
            {0, 17, 23, "Eerily glowing mountains"},
            {0, 24, 31, "Exposed, radiant veins of ore"},
            {0, 32, 38, "Fogs of materializing smoke-like trails"},
            {0, 39, 46, "Irradiated seas or lakes"},
            {0, 47, 53, "Luminescent, rocky spires"},
            {0, 54, 61, "Mutated flora"},
            {0, 62, 69, "Radiation-emitting bulbous growths"},
            {0, 70, 76, "Radioluminescent forests"},
            {0, 77, 84, "Sweeping, debris-laden rivers"},
            {0, 85, 92, "Twinkling clouds of radioactive particles"},
            {0, 93, 100, "Vast, windswept plains"},

        },
        { //{PlanetType_Tainted, 2, "Mycelium" },
            {0, 1, 8, "Colossal, free-floating spores"},
            {0, 9, 15, "Eerily desolate clearings"},
            {0, 16, 23, "Expansive fungal plains"},
            {0, 24, 31, "Fungal forests"},
            {0, 32, 38, "Fungal jungles with unbroken canopies"},
            {0, 39, 46, "Fungus-encrusted caves"},
            {0, 47, 53, "Mountains coated with frill-like fungi"},
            {0, 54, 61, "Murky seas pockmarked by fungal stalks"},
            {0, 62, 68, "Networks of tendrilous roots or vines"},
            {0, 69, 76, "Overgrown remains of ancient flora"},
            {0, 77, 84, "Sky-breaching fungi"},
            {0, 85, 92, "Spore clouds"},
            {0, 93, 100, "Virulent fungal infestations"},

        },
    },

    { {} }, // PlanetType_Metallic ( PG68 )

    { {} }, // PlanetType_Crystalline ( PG48 )

    { {} }, // PlanetType_TidallyLocked ( PG79 sort of) 

    { {} }, // PlanetType_Karst ( PG63, sort of )

    { {} }, // PlanetType_Grave ( PG54 )

    { {} }, // PlanetType_Shattered ( PG74 )

    {
        { //{PlanetType_Living, 0, "Hive"},
            {0, 1, 9, "Barren expanses of muscle and skin"},
            {1, 10, 15, "Breathing orifices"},
            {2, 16, 21, "Excess of dead cells"},
            {3, 22, 28, "Forests of keratinous protrusions"},
            {4, 29, 36, "Forests of towering hairs"},
            {5, 37, 41, "Great, fetid excretion orifice"},
            {6, 42, 47, "High concentration of pheromones"},
            {7, 48, 54, "Hill-like bulbous growths or pustules"},
            {8, 55, 61, "Large cluster of pimples"},
            {9, 62, 63, "Mounds of scales"},
            {10, 64, 70, "Pools of perspiration or sweat"},
            {11, 71, 77, "Sluggish tentacles or tendrils"},
            {12, 78, 82, "Swamp of fetid excretions"},
            {13, 83, 90, "Valley of scar tissue"},
            {0, 91, 100, "Transition into the periosteum biome"},

        },
        { //{PlanetType_Living, 1, "Mutagenic"},
            {0, 1, 7, "Abysmal, glistening orifices"},
            {0, 8, 15, "Bone-like thickets"},
            {0, 16, 23, "Broad, weeping wounds"},
            {0, 24, 29, "Caustic geysers"},
            {0, 30, 38, "Curtains or blankets of connective tissue"},
            {0, 39, 42, "Enormous strands of sinew"},
            {0, 43, 45, "Groves of exposed nerve fibers"},
            {0, 46, 50, "Mineralized tissue"},
            {0, 51, 59, "Mountainous protruding bones"},
            {0, 60, 61, "Neuron-like trees"},
            {0, 62, 67, "Pulsating veins or arteries"},
            {0, 68, 76, "Undulating, distended mounds"},
            {0, 77, 84, "Vividly colored, exposed flesh"},
            {0, 85, 90, "Yawning caves or fissures"},
            {0, 91, 100, "Transition into the epidermis biome"},

        },
    },

    { {} }, // PlanetType_Anomalous ( PG44 )

} };


std::array<std::vector<OracleEntry>, 18> SurfaceFeatureTable{ {
        // PlanetType_Furnace ( PG52 )
std::vector<OracleEntry>{
    {0, 1, 9, "Catastrophic earthquakes"},
    {1, 10, 18, "Dry and barren ocean basins"},
    {2, 19, 27, "Erratic electromagnetic fields"},
    {3, 28, 36, "Fiery world-spanning chasms"},
    {4, 37, 45, "Lava tunnel networks"},
    {5, 46, 54, "Masses of scorched bones"},
    {6, 55, 63, "Once-verdant terrain"},
    {7, 64, 72, "Powerful lava geysers"},
    {8, 73, 81, "Roiling clouds of superheated gas"},
    {9, 82, 90, "Towering mountain ranges"},
    {10, 91, 100, "World-spanning fissures"},

},
// PlanetType_Desert ( PG50 )
std::vector<OracleEntry>{
    {0, 1, 16, "Engulfing sandstorms"},
    {1, 17, 33, "Extensive cacti forest"},
    {2, 34, 50, "Scorched glass plains"},
    {3, 51, 66, "Severe temperature fluctuations"},
    {4, 67, 83, "Sprawling skeletal remains"},
    {5, 84, 100, "Vibrant terrain colors"},

},
// PlanetType_Jungle ( PG60 )
std::vector<OracleEntry>{
    {0, 1, 16, "Inland seas"},
    {1, 17, 33, "Persistent cloud cover"},
    {2, 34, 50, "Torrential rainstorms"},
    {3, 51, 66, "Trees intertwined in symbiosis"},
    {4, 67, 83, "Unusual vegetation color"},
    {5, 84, 100, "Violent electrical storms"},

},
// PlanetType_Vital ( PG80 )
std::vector<OracleEntry>{
    {0, 1, 6, "Background radiation"},
    {1, 7, 13, "Chaotically juxtaposed biomes"},
    {2, 14, 20, "Creature boneyards"},
    {3, 21, 26, "Creature lairs or watering holes"},
    {4, 27, 33, "Crystalline formations"},
    {5, 34, 40, "Fierce electrical storms"},
    {6, 41, 46, "Floating terrain"},
    {7, 47, 53, "Frequent seismic activity"},
    {8, 54, 60, "Magnetic disturbances"},
    {9, 61, 66, "Scarred or excavated terrain"},
    {10, 67, 73, "Signs of an engineered biosphere"},
    {10, 74, 80, "Sudden weather fluctuations"},
    {10, 81, 86, "Towering geological formations"},
    {10, 87, 93, "Vibrantly colored landscapes"},
    {10, 94, 100, "Vivid auroras"},

},
// PlanetType_Ocean ( PG70 )
std::vector<OracleEntry>{
    {0, 1, 12, "Brilliantly reflective waters"},
    {1, 13, 25, "Ceaseless rainfall"},
    {2, 26, 37, "Glaring electrical storms"},
    {3, 38, 50, "Global hurricanes"},
    {4, 51, 62, "Luminescent seas"},
    {5, 63, 75, "Ocean-spanning whirlpools"},
    {6, 76, 87, "Unusually colored terrain or waters"},
    {7, 88, 100, "Visible oceanic currents"},

},
// PlanetType_Ice ( PG56 )
std::vector<OracleEntry>{
    {0, 1, 16, "Blinding snow storms"},
    {1, 17, 33, "Craters surrounded by shattered ice"},
    {2, 34, 50, "Preserved carcasses"},
    {3, 51, 66, "Solid ice fields"},
    {4, 67, 83, "Vibrant auroras"},
    {5, 84, 100, "Vibrantly colored ice"},

},
// PlanetType_Chemical ( PG46 )
std::vector<OracleEntry>{
    {0, 1, 12, "Caustic or toxic mists"},
    {1, 13, 25, "Distorting vaporous haze"},
    {2, 26, 37, "Unusually colored clouds or sky"},
    {3, 38, 50, "Light absorbing clouds"},
    {4, 51, 62, "Chemical snowfall or blizzards"},
    {5, 63, 75, "Fields of eroded craters"},
    {6, 76, 87, "Colossal ice caves"},
    {7, 88, 100, "Corroded or preserved carcasses"},

},
// PlanetType_Jovian ( PG58 )
std::vector<OracleEntry>{
    {0, 1, 4, "Cascading cloudfalls "},
    {1, 5, 8, "Ceaseless atmospheric escape "},
    {2, 9, 12, "Clouds of metal particles "},
    {3, 13, 16, "Crystalline rains "},
    {4, 17, 20, "Expansive zones of odd gravity "},
    {5, 21, 24, "Floating glaciers "},
    {6, 25, 28, "Floating islands "},
    {7, 29, 32, "Floating, solidified clouds "},
    {8, 33, 36, "Layer of suspended liquid"},
    {9, 37, 40, "Matter visibly transitioning"},
    {10, 41, 44, "Metallic rains"},
    {11, 45, 48, "Monochromatic atmosphere"},
    {12, 49, 52, "Perpetual superstorm"},
    {13, 53, 56, "Pockets of explosive gases"},
    {0, 57, 61, "Powerful vortexes"},
    {0, 62, 65, "Radiation fields"},
    {0, 66, 70, "Severe electrical storms"},
    {0, 71, 74, "Storm-swept rocky debris"},
    {0, 75, 79, "Torrential rain"},
    {0, 80, 83, "Towering thunderheads"},
    {0, 84, 87, "Unusual atmospheric colors"},
    {0, 88, 91, "Vibrant, cloud-piercing auroras"},
    {0, 92, 96, "Violent turbulence"},
    {0, 97, 100, "Zones of localized atmosphere"},

},
// PlanetType_Rocky ( PG72 )
std::vector<OracleEntry>{
    {0, 1, 11, "Craggy outcrops"},
    {1, 12, 22, "Glassy impact craters"},
    {2, 23, 33, "Jagged mountains"},
    {3, 34, 44, "Massive impact crater"},
    {4, 45, 55, "Rugged and rocky flatlands"},
    {5, 56, 66, "Swirling, low-lying gasses"},
    {6, 67, 77, "Towering plateaus"},
    {7, 78, 88, "Unusual terrain coloration"},
    {8, 89, 100, "Weathered rocky monoliths"},

},
// PlanetType_Tainted ( PG76 )
std::vector<OracleEntry>{
    {0, 1, 9, "Caustic gas storms"},
    { 1, 10, 18, "Layers of fast-growing lichen" },
    { 2, 19, 27, "Moldering bones" },
    { 3, 28, 36, "Poisonous gas vents" },
    { 4, 37, 45, "Powerful thunderstorms" },
    { 5, 46, 54, "Sheltered and isolated caves" },
    { 6, 55, 63, "Stagnant cloud cover" },
    { 7, 64, 72, "Thick, murky atmosphere" },
    { 8, 73, 81, "Toxic rain" },
    { 9, 82, 90, "Unusual, pervasive haze" },
    { 10, 91, 100, "Vibrant terrain coloration" },

},
// PlanetType_Metallic ( PG68 )
std::vector<OracleEntry>{
    {0, 1, 4, "Cracked or molten craters "},
    { 1, 5, 8, "Enormous angular columns " },
    { 2, 9, 12, "Eroded etchplains " },
    { 3, 13, 16, "Erratic magnetic abnormalities " },
    { 4, 17, 20, "Expansive veins of alloys " },
    { 5, 21, 24, "Fractured, crumbling cliffs " },
    { 6, 25, 28, "Hill-like ore deposits " },
    { 7, 29, 32, "Mirror-like terrain " },
    { 8, 33, 36, "Ore-strewn wastes" },
    { 9, 37, 40, "Polished valleys" },
    { 10, 41, 44, "Polychromatic mesas" },
    { 11, 45, 48, "Pools of molten metal" },
    { 12, 49, 52, "Razor-edged spires" },
    { 13, 53, 56, "Rigid, arch-like formations" },
    { 0, 57, 61, "Ruinous lightning storms" },
    { 0, 62, 65, "Rusted or patinated mountains" },
    { 0, 66, 70, "Sky-breaching metallic crystals" },
    { 0, 71, 74, "Smooth, echoing chasms" },
    { 0, 75, 79, "Smoothed plains" },
    { 0, 80, 83, "Solidified rivers of metal" },
    { 0, 84, 87, "Storms of metallic shards" },
    { 0, 88, 91, "Tarnished mountain ranges" },
    { 0, 92, 96, "Tunnels blanketed by ore" },
    { 0, 97, 100, "Vast stratified canyons" },

},
// PlanetType_Crystalline ( PG48 )
std::vector<OracleEntry>{
    {0, 1, 4, "Angular, arch-like formations"},
    {1, 5, 8, "Canyons linked by polygonal bridges"},
    {2, 9, 12, "Crystalline-rubble wastes"},
    {3, 13, 16, "Densely gem-encrusted caves"},
    {4, 17, 20, "Faceted hills or mounds"},
    {5, 21, 24, "Fields of grass-like crystals"},
    {6, 25, 28, "Geometric sinkholes or chasms"},
    {7, 29, 32, "Glittering columns"},
    {8, 33, 36, "Glossy valleys"},
    {9, 37, 40, "Intensely refracted light-rays"},
    {10, 41, 44, "Iridescent mountain ranges"},
    {11, 45, 48, "Polychromatic plains"},
    {12, 49, 52, "Polycrystalline mesas"},
    {13, 53, 56, "Pools of molten crystal"},
    {0, 57, 61, "Razor-edged spires"},
    {0, 62, 65, "Reverberating thunderstorms"},
    {0, 66, 70, "Shattered impact craters"},
    {0, 71, 74, "Shimmering mountains"},
    {0, 75, 79, "Sky-breaching crystals"},
    {0, 80, 83, "Splintered etchplains"},
    {0, 84, 87, "Sweeping crystalline rains"},
    {0, 88, 91, "Symmetrical landscapes"},
    {0, 92, 96, "Translucent cliffs"},
    {0, 97, 100, "Twinkling dust storms"},

},
// PlanetType_TidallyLocked ( PG79 sort of) 
std::vector<OracleEntry>{
    { LifeType_Other,     1,  100, "TidallyLocked Dark/Light/rings"},
},
// PlanetType_Karst ( PG63, sort of )
std::vector<OracleEntry>{
    { LifeType_Other,     1,  100, "Karst Surface/Underground"},
},
// PlanetType_Grave ( PG54 )
std::vector<OracleEntry>{
    {0, 1, 4, "Acid pools "},
    { 1, 5, 8, "Ash dunes " },
    { 2, 9, 12, "Cataclysmic earthquakes " },
    { 3, 13, 16, "Corrosive rains " },
    { 4, 17, 20, "Cratered landscape " },
    { 5, 21, 24, "Dead forests " },
    { 6, 25, 28, "Dry seabeds " },
    { 7, 29, 32, "Dust-choked atmosphere " },
    { 8, 33, 36, "Crashed orbital stations" },
    { 9, 37, 40, "Fetid mudflats" },
    { 10, 41, 44, "Frozen hydrosphere" },
    { 11, 45, 48, "Irradiated atmosphere" },
    { 12, 49, 53, "Mass graves" },
    { 13, 54, 57, "Moldering bones" },
    { 0, 58, 62, "Noxious fog" },
    { 0, 63, 66, "Perpetual cloud cover" },
    { 0, 67, 70, "Radioactive hotspots" },
    { 0, 71, 75, "Ravaged cities" },
    { 0, 76, 79, "Scarred battlefields" },
    { 0, 80, 83, "Ship graveyards" },
    { 0, 84, 87, "Sky-breaching ruins" },
    { 0, 88, 91, "Supervolcano caldera" },
    { 0, 92, 96, "Vast wastelands" },
    { 0, 97, 100, "Whispers of the dead" },

},
// PlanetType_Shattered ( PG74 )
std::vector<OracleEntry>{
    {0, 1, 4, "Barren ocean basin "},
    { 1, 5, 8, "Broken cities " },
    { 2, 9, 13, "Broken, crumbling mountains " },
    { 3, 14, 18, "Colliding fragments " },
    { 4, 19, 23, "Cracked or shattered plains " },
    { 5, 24, 27, "Disastrous earthquakes " },
    { 6, 28, 31, "Drifting volumes of liquid " },
    { 7, 32, 35, "Energy storms " },
    { 8, 36, 39, "Enormous sinkholes" },
    { 9, 40, 43, "Exposed caverns" },
    { 10, 44, 47, "Fierce shockwaves" },
    { 11, 48, 51, "Fluctuating gravity" },
    { 12, 52, 55, "Geomagnetic storms" },
    { 13, 56, 59, "Magnetic disturbances" },
    { 0, 60, 64, "Molten fissures or canyons" },
    { 0, 65, 68, "Phantom visions of the past" },
    { 0, 69, 72, "Plethoras of impact craters" },
    { 0, 73, 76, "Pocket atmosphere" },
    { 0, 77, 80, "Residual energy storms" },
    { 0, 81, 84, "Revealed crystal or ore deposits" },
    { 0, 85, 88, "Swirling, corrosive gases" },
    { 0, 89, 92, "Unstable and fracturing terrain" },
    { 0, 93, 96, "Venting magma" },
    { 0, 97, 100, ">Preserved biome" },

},
// PlanetType_Living ( PG64 )
std::vector<OracleEntry>{
    {0, 1, 9, "Active alimentary cavity "},
    { 1, 10, 18, "Bizarre sensory organ " },
    { 2, 19, 27, "Cluster of nasal cavities " },
    { 3, 28, 36, "Colony of parasitic lifeforms " },
    { 4, 37, 45, "Corrosive or toxic rain" },
    { 5, 46, 54, "Distinctive flesh coloration" },
    { 6, 55, 63, "Gland producing substance" },
    { 7, 64, 72, "Regions of necrotic flesh" },
    { 8, 73, 81, "Rolling fogs of miasma" },
    { 9, 82, 90, "Slowly moving landscape" },
    { 10, 91, 100, "Vents expelling waste gases" },

},
// PlanetType_Anomalous ( PG44 )
std::vector<OracleEntry>{
    { 0, 1, 4, "Backward flowing waterways "},
    { 1, 5, 8, "Enormous hovering islands " },
    { 2, 9, 12, "Floating luminous rings " },
    { 3, 13, 16, "Forests of foreboding monoliths " },
    { 4, 17, 20, "Fractal cliffs or canyons " },
    { 5, 21, 24, "Geometric tunnels networks" },
    { 6, 25, 28, "Gravitational abnormalities " },
    { 7, 29, 32, "Higher-dimensional landscape " },
    { 8, 33, 36, "Howling portals " },
    { 9, 37, 40, "Impossible geometries " },
    { 10, 41, 44, "Inverted mountains " },
    { 11, 45, 48, "Iridescent sky or terrain " },
    { 12, 49, 52, "Oceans of exotic matter" },
    { 13, 53, 56, "Oscillating hills or valleys " },
    { 0, 57, 60, "Perfectly smooth plains " },
    { 0, 61, 64, "Rapidly evolving landscape " },
    { 0, 65, 68, "Roaming spectral visages" },
    { 0, 69, 72, "Symmetrically aligned flora" },
    { 0, 73, 76, "Teleporting or phasing landscape" },
    { 0, 77, 80, "Temporal fluctuations" },
    { 0, 81, 84, "Thick waterlike clouds" },
    { 0, 85, 88, "Vast floating oceans or seas" },
    { 0, 89, 92, "Whispering mists" },
    { 0, 93, 100, ">Extraplanetary Biome" },

},
} };

std::vector<std::string> settlementsList = { "None", "Orbital", "Ground Based", "Multiple", "Multiple In Conflict" };

std::array<std::array<std::vector<OracleEntryND>, 3>, 18> SettlementsTable{ {
{{
    // PlanetType_Furnace ( PG52 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  60},
        { 1, 61,  75},
        { 2, 76,  87},
        { 3, 88,  96},
        { 4, 97,  100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  85},
        { 1, 86,  92},
        { 2, 93,  97},
        { 3, 98,  99},
        { 4, 100, 100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  95},
        { 1, 96,  98},
        { 2, 99,  100},
    },

}},
{{
// PlanetType_Desert ( PG50 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  50},
        { 1, 51,  60},
        { 2, 61,  80},
        { 3, 81,  92},
        { 4, 93,  100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  75},
        { 1, 76,  83},
        { 2, 84,  95},
        { 3, 96,  98},
        { 4, 99,  100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  90},
        { 1, 91,  96},
        { 2, 97,  100},
    },

}},
{{
// PlanetType_Jungle ( PG60 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  40},
        { 1, 41,  55},
        { 2, 56,  80},
        { 3, 81,  92},
        { 4, 93,  100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  65},
        { 1, 66,  75},
        { 2, 76,  92},
        { 3, 93,  97},
        { 4, 98,  100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  85},
        { 1, 86,  90},
        { 2, 91,  97},
        { 3, 98,  99},
        { 4, 100,  100},
    },

}},
{{
// PlanetType_Vital ( PG80 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  20},
        { 1, 21, 30},
        { 2, 31, 70},
        { 3, 71, 90},
        { 4, 91, 100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  50},
        { 1, 51, 55},
        { 2, 56, 85},
        { 3, 86, 95},
        { 4, 96, 100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  80},
        { 1, 81, 83},
        { 2, 56, 85},
        { 3, 86, 95},
        { 4, 96, 100},
    },
}},
{{
// PlanetType_Ocean ( PG70 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  40},
        { 1, 41,  55},
        { 2, 56,  80},
        { 3, 81,  92},
        { 4, 93,  100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  65},
        { 1, 66,  75},
        { 2, 86,  92},
        { 3, 93,  97},
        { 4, 98,  100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  85},
        { 1, 86,  90},
        { 2, 91,  97},
        { 3, 98,  99},
        { 4, 100,  100},
    },

}},
{{
// PlanetType_Ice ( PG56 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  50},
        { 1, 51,  60},
        { 2, 61,  80},
        { 3, 81,  92},
        { 4, 93,  100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  75},
        { 1, 76,  83},
        { 2, 84,  95},
        { 3, 96,  98},
        { 4, 99,  100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  90},
        { 1, 91,  96},
        { 2, 97,  100},
    },

} },
{{
// PlanetType_Chemical ( PG46 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  80},
        { 1, 81,  90},
        { 2, 91,  95},
        { 3, 96,  98},
        { 4, 99,  100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  90},
        { 1, 91,  97},
        { 2, 98,  100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  95},
        { 1, 96,  98},
        { 2, 99,  100},
    },

} },
{ {
// PlanetType_Jovian ( PG58 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  50},
        { 1, 51,  70},
        { 2, 71,  85},
        { 3, 86,  95},
        { 4, 96,  100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  75},
        { 1, 76,  87},
        { 2, 88,  95},
        { 3, 96,  98},
        { 4, 99,  100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  90},
        { 1, 91,  96},
        { 2, 97,  100},
    },

} },
{ {
// PlanetType_Rocky ( PG72 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  50},
        { 1, 51, 70},
        { 2, 71, 85},
        { 3, 86, 95},
        { 4, 96, 100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  75},
        { 1, 76, 87},
        { 2, 88, 95},
        { 3, 96, 98},
        { 4, 99, 100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  80},
        { 1, 81, 83},
        { 2, 56, 85},
        { 3, 86, 95},
        { 4, 96, 100},
    },
} },
{ {
// PlanetType_Tainted ( PG76 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  80},
        { 1, 81, 90},
        { 2, 91, 95},
        { 3, 96, 98},
        { 4, 99, 100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  90},
        { 1, 91, 97},
        { 2, 98, 100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  95},
        { 1, 96, 98},
        { 2, 99, 100},
    },
} },
{ {
// PlanetType_Metallic ( PG68 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  50},
        { 1, 51,  70},
        { 2, 71,  85},
        { 3, 86,  95},
        { 4, 96,  100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  75},
        { 1, 76,  87},
        { 2, 88,  95},
        { 3, 96,  98},
        { 4, 99,  100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  90},
        { 1, 91,  96},
        { 2, 97,  100},
    },

} },
{ {
// PlanetType_Crystalline ( PG48 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  50},
        { 1, 51,  70},
        { 2, 71,  85},
        { 3, 86,  95},
        { 4, 96,  100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  75},
        { 1, 76,  87},
        { 2, 88,  95},
        { 3, 96,  98},
        { 4, 99,  100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  90},
        { 1, 91,  96},
        { 2, 97,  100},
    },

} },
{ {
// PlanetType_TidallyLocked ( PG79 sort of) 
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  20},
        { 1, 21, 30},
        { 2, 31, 70},
        { 3, 71, 90},
        { 4, 91, 100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  50},
        { 1, 51, 55},
        { 2, 56, 85},
        { 3, 86, 95},
        { 4, 96, 100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  80},
        { 1, 81, 83},
        { 2, 56, 85},
        { 3, 86, 95},
        { 4, 96, 100},
    },
} },
{ {
// PlanetType_Karst ( PG63, sort of )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  20},
        { 1, 21, 30},
        { 2, 31, 70},
        { 3, 71, 90},
        { 4, 91, 100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  50},
        { 1, 51, 55},
        { 2, 56, 85},
        { 3, 86, 95},
        { 4, 96, 100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  80},
        { 1, 81, 83},
        { 2, 56, 85},
        { 3, 86, 95},
        { 4, 96, 100},
    },
} },
{ {
// PlanetType_Grave ( PG54 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  80},
        { 1, 81,  90},
        { 2, 91,  95},
        { 3, 96,  98},
        { 4, 99,  100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  90},
        { 1, 91,  97},
        { 2, 98,  100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  95},
        { 1, 96,  98},
        { 2, 99,  100},
    },

} },
{ {
// PlanetType_Shattered ( PG74 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  70},
        { 1, 71, 90},
        { 2, 91, 95},
        { 3, 96, 98},
        { 4, 99, 100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,   85},
        { 1, 86,  96},
        { 2, 97,  99},
        { 3, 100, 100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  95},
        { 1, 96, 99},
        { 2, 100, 100},
    },
} },
{ {
// PlanetType_Living ( PG64 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  85},
        { 1, 86,  95},
        { 2, 96,  100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  95},
        { 1, 96,  100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  99},
        { 1, 100,  100},
    },

} },
{ {
// PlanetType_Anomalous ( PG44 )
    std::vector<OracleEntryND>{ //Terminus
        { 0, 1,  50},
        { 1, 51,  60},
        { 2, 61,  80},
        { 3, 81,  92},
        { 4, 93,  100},
    },
    std::vector<OracleEntryND>{ //Outlands
        { 0, 1,  75},
        { 1, 76,  83},
        { 2, 84,  95},
        { 3, 96,  98},
        { 4, 99,  100},
    },
    std::vector<OracleEntryND>{ //Expanse
        { 0, 1,  90},
        { 1, 91,  96},
        { 2, 97,  100},
    },

} },
} };


std::array<std::vector<OracleEntry>, 3> megastructureTable{ {
        //"Level 1"
        std::vector<OracleEntry>{
            { 0, 1,  10,  "Unidentified Megastructure (Unknown) [Planetary or sub]"},
            { 1, 11,  16,  "Aegisphere (Military) [Planetary]"},
            { 2, 17,  22,  "Asteroid Processor (Mining) [Subplanetary]"},
            { 3, 23,  28,  "Atmosphere Harvester (Mining) [Subplanetary]"},
            { 4, 29,  34,  "Defense Nexus (Military) [Subplanetary]"},
            { 5, 35,  40,  "Ecopoiesis Array (Terraforming) [Subplanetary]"},
            { 6, 41,  47,  "Ecumenopolis (Residence) [Planetary]"},
            { 7, 48,  53,  "Equatorial Shipyard (Industry) [Planetary]"},
            { 8, 54,  59,  "Ferrothermal Engine (Terraforming) [Subplanetary]"},
            { 9, 60,  65,  "Geothermal Stabilizer (Terraforming) [Subplanetary]"},
            { 10, 66,  73,  "McKendree Cylinder (Residence) [Subplanetary]"},
            { 11, 74,  79,  "Nezzarine Garden (Agriculture) [Planetary]"},
            { 12, 80,  85,  "Quarry World (Mining) [Planetary]"},
            { 13, 86,  87,  "Sentinel Belt (Military) [System]"},
            { 14, 88,  94,  "Standford Torus (Residence) [Subplanetary]"},
            { 15, 95,  100,  "Terravore (Mining) [Subplanetary]"},

        },
    //"Level 1 & 2"
    std::vector<OracleEntry>{
            { 0, 1,  10,  "Unidentified Megastructure (Unknown) [Planetary or sub]"},
            { 1, 11,  13,  "Aegisphere (Military) [Planetary]"},
            { 2, 14,  16,  "Asteroid Processor (Mining) [Subplanetary]"},
            { 3, 17,  19,  "Atmosphere Harvester (Mining) [Subplanetary]"},
            { 4, 20,  22,  "Defense Nexus (Military) [Subplanetary]"},
            { 5, 23,  25,  "Ecopoiesis Array (Terraforming) [Subplanetary]"},
            { 6, 26,  30,  "Ecumenopolis (Residence) [Planetary]"},
            { 7, 31,  33,  "Equatorial Shipyard (Industry) [Planetary]"},
            { 8, 34,  36,  "Ferrothermal Engine (Terraforming) [Subplanetary]"},
            { 9, 37,  39,  "Geothermal Stabilizer (Terraforming) [Subplanetary]"},
            { 10, 40,  45,  "McKendree Cylinder (Residence) [Subplanetary]"},
            { 11, 46,  48,  "Nezzarine Garden (Agriculture) [Planetary]"},
            { 12, 49,  51,  "Quarry World (Mining) [Planetary]"},
            { 13, 52,  53,  "Sentinel Belt (Military) [System]"},
            { 14, 54,  58,  "Standford Torus (Residence) [Subplanetary]"},
            { 15, 59,  61,  "Terravore (Mining) [Subplanetary]"},
            { 16, 62,  66,  "Bishop Ring (Residence) [Planetary]"},
            { 17, 67,  69,  "Behemoth Assembler (Industry) [Planetary]"},
            { 18, 70,  73,  "Discworld (Residence) [Planetary]"},
            { 19, 74,  76,  "Ecosphere (Research) [Planetary]"},
            { 20, 77,  82,  "Habitat Cluster (Residence) [Planetary]"},
            { 21, 83,  85,  "Jupiter Brain (Research) [Planetary]"},
            { 22, 86,  88,  "Kintsugi World (Cultural) [Planetary]"},
            { 23, 89,  91,  "Lunar Speculorefractor (Terraforming) [Planetary]"},
            { 24, 92,  94,  "Planetcraft (Mixed) [Planetary]"},
            { 25, 95,  97,  "Sentry Array (Military) [Planetary]"},
            { 26, 98,  100,  "Terraformer Hub (Terraforming) [Planetary]"},

    },
    //"Level 1, 2, & 3"
    std::vector<OracleEntry>{
            { 0, 1,  10,  "Unidentified Megastructure (Unknown) [Planetary or sub]"},
            { 1, 11,  12,  "Aegisphere (Military) [Planetary]"},
            { 2, 13,  14,  "Asteroid Processor (Mining) [Subplanetary]"},
            { 3, 15,  16,  "Atmosphere Harvester (Mining) [Subplanetary]"},
            { 4, 17,  18,  "Defense Nexus (Military) [Subplanetary]"},
            { 5, 19,  20,  "Ecopoiesis Array (Terraforming) [Subplanetary]"},
            { 6, 21,  23,  "Ecumenopolis (Residence) [Planetary]"},
            { 7, 24,  25,  "Equatorial Shipyard (Industry) [Planetary]"},
            { 8, 26,  27,  "Ferrothermal Engine (Terraforming) [Subplanetary]"},
            { 9, 28,  29,  "Geothermal Stabilizer (Terraforming) [Subplanetary]"},
            { 10, 30,  33,  "McKendree Cylinder (Residence) [Subplanetary]"},
            { 11, 34,  35,  "Nezzarine Garden (Agriculture) [Planetary]"},
            { 12, 36,  37,  "Quarry World (Mining) [Planetary]"},
            { 13, 38,  39,  "Sentinel Belt (Military) [System]"},
            { 14, 40,  42,  "Standford Torus (Residence) [Subplanetary]"},
            { 15, 43,  44,  "Terravore (Mining) [Subplanetary]"},
            { 16, 45,  46,  "Bishop Ring (Residence) [Planetary]"},
            { 17, 47,  48,  "Behemoth Assembler (Industry) [Planetary]"},
            { 18, 49,  50,  "Discworld (Residence) [Planetary]"},
            { 19, 51,  52,  "Ecosphere (Research) [Planetary]"},
            { 20, 53,  56,  "Habitat Cluster (Residence) [Planetary]"},
            { 21, 57,  58,  "Jupiter Brain (Research) [Planetary]"},
            { 22, 59,  60,  "Kintsugi World (Cultural) [Planetary]"},
            { 23, 61,  62,  "Lunar Speculorefractor (Terraforming) [Planetary]"},
            { 24, 63,  64,  "Planetcraft (Mixed) [Planetary]"},
            { 25, 65,  66,  "Sentry Array (Military) [Planetary]"},
            { 26, 67,  68,  "Terraformer Hub (Terraforming) [Planetary]"},
            { 27, 69,  70,  "Accretion Macrocollector (Mining) [Stellar]"},
            { 28, 71,  72,  "Alderson Disk (Residence) [System]"},
            { 29, 73,  74,  "Dyson Object (Industry) [Stellar]"},
            { 30, 75,  76,  "Fusion Suppressor (Terraforming) [Stellar]"},
            { 31, 77,  78,  "Helio-obliterator (Military) [Stellar]"},
            { 32, 79,  80,  "Hyperstructural Shipyard (Industry) [Stellar]"},
            { 33, 81,  82,  "Kugelblitz Silo (Industry) [Stellar]"},
            { 34, 83,  84,  "Matrioshka Brain (Research) [Stellar]"},
            { 35, 85,  86,  "Nicoll-dyson Array (Military) [Stellar]"},
            { 36, 87,  88,  "Penrose Sphere (Industry / Military) [Stellar]"},
            { 37, 89,  90,  "Star Lifter (Mining) [Stellar]"},
            { 38, 91,  92,  "Stellar Compressor (Terraforming) [Stellar]"},
            { 39, 93,  94,  "Stellar Engine (Transportation) [Stellar]"},
            { 40, 95,  96,  "Stellar Hyperforge (Industry) [Stellar]"},
            { 41, 97,  98,  "Stellar Ringworld (Residence) [System]"},
            { 42, 99,  100,  "System-forge (Industry) [System]"},

    },
} };